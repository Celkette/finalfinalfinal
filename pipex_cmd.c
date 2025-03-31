#include "pipex.h"

static void concat_args(char **cmd_args, int index_i, int index_j) 
{
    size_t  len_i;
    size_t  len_j;
    char    *temp;

    len_i = strlen(cmd_args[index_i]);
    len_j = strlen(cmd_args[index_j]);
    temp = malloc(len_i + len_j + 2);
    if (!temp)
        pipex_error_i("malloc failed in concat_args", -1);
    ft_strlcpy(temp, cmd_args[index_i], len_i + 1);
    ft_strlcat(temp, " ", len_i + 2);
    ft_strlcat(temp, cmd_args[index_j], len_i + len_j + 2);
    free(cmd_args[index_i]);
    cmd_args[index_i] = temp;
}

static void remove_arg(char **cmd_args, int index_to_remove) 
{
    int k = index_to_remove;
    while (cmd_args[k] != NULL) 
	{
        cmd_args[k] = cmd_args[k + 1];
        k++;
    }
}

static void remove_quotes(char *arg) 
{
    size_t len = strlen(arg);
    if (len >= 2 && arg[0] == '\'' && arg[len - 1] == '\'') 
	{
        ft_memmove(arg, arg + 1, len - 2);
        arg[len - 2] = '\0';
    }
}

static void handle_quotes(char **cmd_args, int *i, int *j, int *in_quotes)//* pour pouvoir modifier les valeur dans get_cmd_arg
{
    *in_quotes = 1;
    *j = *i + 1;

    while (cmd_args[*j] != NULL && (*in_quotes || cmd_args[*j][strlen(cmd_args[*j]) - 1] != '\''))
    {
        concat_args(cmd_args, *i, *j);
        remove_arg(cmd_args, *j);
        if (cmd_args[*i][strlen(cmd_args[*i]) - 1] == '\'')
            *in_quotes = 0;
    }
}

char    **get_cmd_arg(char *cmd)
{
    char    **cmd_args;
    int     i;
    int     j;
    int     in_quotes;

    cmd_args = NULL;
    cmd_args = pipex_ft_split(cmd, ' ');
    if (cmd_args == NULL)
        pipex_error_i("cmd_args = ft_split failed (in get_cmd_arg)", -1);
    i = 0;
    while (cmd_args[i] != NULL)
    {
        if (cmd_args[i][0] == '\'' && cmd_args[i][strlen(cmd_args[i]) - 1] != '\'')
            handle_quotes(cmd_args, &i, &j, &in_quotes);
		remove_quotes(cmd_args[i]);
        i++;
    }
    return (cmd_args);
}