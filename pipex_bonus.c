/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-rouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:19:50 by cle-rouz          #+#    #+#             */
/*   Updated: 2025/03/27 14:32:28 by cle-rouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "pipex.h"


/*static void wait_all_commands_executions(int nb_cmd)
{
    int i;
    int status;

	i = 0;
    status = 0;
    while (i < nb_cmd)
    {
        if (wait(&status) == -1)
            pipex_error_i("wait(&status) failed", 1);
		i++;
	}
}*/
static void	wait_all_commands_executions(void)
{
	pid_t	wpid;
	int		status;

	wpid = 1;
	status = 0;
	while (wpid > 0)
	{
		wpid = wait(&status);
	}
}

static void first_child_bonus(char **argv, char **envp, int *fd)
{
    int fd_in;
    int cmd_arg ;

	cmd_arg = 2;
    if (check_if_heredoc(argv[1]) == 0)
        cmd_arg = 3;
    fd_in = pipex_creat_open_fd_in(argv);
    close(fd[0]);
    if (dup2(fd_in, STDIN_FILENO) == -1)
        pipex_error_i("dup2 failed (first_child_bonus)", 1);
    close(fd_in);
    if (dup2(fd[1], STDOUT_FILENO) == -1)
        pipex_error_i("dup2 failed (first_child_bonus)", 1); 
    close(fd[1]);
    execute_cmd(argv, envp, cmd_arg);
    pipex_error_i("execute_cmd failed (first_child_bonus)", 1);
}

// Fonction pour les enfants du milieu dans la version bonus (avec 4 arguments)
static void middle_child_bonus(char **argv, char **envp, int *cmd_i, int pipe_in)
{
    close(cmd_i[1]);
    if (dup2(pipe_in, STDIN_FILENO) == -1)
        pipex_error_i("dup2 failed (middle_child_bonus)", 1);
    close(pipe_in);
    if (dup2(cmd_i[2], STDOUT_FILENO) == -1)
        pipex_error_i("dup2 failed (middle_child_bonus)", 1);
    close(cmd_i[2]);
    execute_cmd(argv, envp, cmd_i[0]);
    pipex_error_i("execute_cmd failed (middle_child_bonus)", 1);
}

// Fonction pour le dernier enfant dans la version bonus
static void last_child_bonus(int argc, char **argv, char **envp, int pipe_in)
{
    int fd_out;
    int cmd_arg;

    cmd_arg = argc - 2;
   
    fd_out = pipex_creat_open_fd_out(argc, argv);
    if (dup2(pipe_in, STDIN_FILENO) == -1)
        pipex_error_i("dup2 failed (last_child_bonus)", 1);
    close(pipe_in);
    if (dup2(fd_out, STDOUT_FILENO) == -1)
        pipex_error_i("dup2 failed (last_child_bonus)", 1);
    close(fd_out);
    execute_cmd(argv, envp, cmd_arg);
    pipex_error_i("execute_cmd failed (last_child_bonus)", 1);
}

static int manage_first_child_bonus(char **argv, char **envp, int *pipe_in)
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
        pipex_error_i("La création du pipe a échoué (premier enfant)", -1);
    pid = fork();
    if (pid == -1)
        pipex_error_i("La création du premier enfant a échoué", -1);
    if (pid == 0)
        first_child_bonus(argv, envp, fd);
    close(fd[1]);
    *pipe_in = fd[0];
    return (0);
    // Le processus parent récupère la sortie standard de l'enfant en lisant depuis le pipe
    // via le descripteur de fichier stocké dans *pipe_in.
}

static int manage_middle_child_bonus(char **argv, char **envp, int i, int *pipe_in)
{
    int fd[2];
    pid_t pid;
    int i_fd[3];

    i_fd[0] = i;
    if (pipe(fd) == -1)
        pipex_error_i("La création du pipe a échoué (middle child)", -1);
    pid = fork();
    if (pid == -1)
        pipex_error_i("La création d'un enfant du milieu a échoué", -1);
    if (pid == 0)
    {
        i_fd[1] = fd[0];
        i_fd[2] = fd[1];
        middle_child_bonus(argv, envp, i_fd, *pipe_in);
    }
    close(fd[1]);
    close(*pipe_in); // Fermer l'ancienne extrémité de lecture
    *pipe_in = fd[0];
    return (0); // Pas d'erreur
}

static int manage_last_child_bonus(int argc, char **argv, char **envp, int *pipe_in)
{
    pid_t pid;

        pid = fork();
        if (pid == -1)
            pipex_error_i("La création du dernier enfant a échoué", -1);
        if (pid == 0)
            last_child_bonus(argc, argv, envp, *pipe_in);
        close(*pipe_in);
        return (0);
}

static void parent_bonus(int argc, char **argv, char **envp)
{
    int i;//index de argv[]
    int pipe_in;//descripteur de fichier pour la lecture
    int cmd_start_i;//index de argv[] où commencent les commandes
    int child_nb;//nb enfants

	pipe_in = -1;
    cmd_start_i = 2;
    if (check_if_heredoc(argv[1]) == 0)
    {
        cmd_start_i = 3;
        child_nb =cmd_start_i -2;
    }
    child_nb = argc - 1 - cmd_start_i;
    i = cmd_start_i;
    manage_first_child_bonus(argv, envp, &pipe_in);
    i++;
    child_nb++;
    while (i < argc - 2)
    {
        manage_middle_child_bonus(argv, envp, i, &pipe_in);
        i++;
        child_nb++;
    }
    manage_last_child_bonus(argc, argv, envp, &pipe_in);
//wait_all_commands_executions(child_nb);
   
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
    close(STDERR_FILENO);
    wait_all_commands_executions();
}

int main(int argc, char **argv, char **envp)
{
    if (argc >= 5)
    {
    begin_check(argc, argv, envp);
    parent_bonus(argc, argv, envp);
    }
    else
        pipex_error_i("\033[31m Mauvais nombre d'arguments\n\e[0m", -1);
    return (0);
}