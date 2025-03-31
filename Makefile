
PROG	= pipex
PROG_B  = pipex_bonus


SRCS 	= pipex.c pipex_utils_1.c pipex_utils_2.c pipex_check.c pipex_cmd.c pipex_path.c pipex_split.c
OBJS 	= ${SRCS:.c=.o}
MAIN	= pipex.c 

SRCS_B	= pipex_bonus.c pipex_bonus_util.c pipex_utils_1.c pipex_utils_2.c pipex_check.c pipex_cmd.c pipex_path.c pipex_split.c
OBJS_B	= ${SRCS_B:.c=.o}
MAIN_B	= pipex_bonus.c

HEADER	= -Iincludes

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g -MMD -MP


%.o : %.c
		${CC} ${CFLAGS} ${HEADER} -c $< -o $@

all: 		${PROG}
${PROG}:	${OBJS}
					echo "\033[36m\n"
					make  -C ./libft
					echo "\nLibft Compiled!"
					echo "\033[35m"
					make  -C ./ft_printf
					echo "ft_printf Compiled!\n\e[0m"
					$(CC) ${OBJS} -L./libft -lft -L./ft_printf -lftprintf -o ${PROG}
					echo "\033[36mLibft Compiled!\e[0m"
					echo "\033[35mft_printf Compiled!\e[0m"
					echo "\033[32mPipex Compiled!\n\e[0m"

bonus:		${PROG_B}

${PROG_B}:	${OBJS_B}
					echo "\033[36m\n"
					make  -C ./libft
					echo "\nLibft Compiled!"
					echo "\033[35m"
					make  -C ./ft_printf
					echo "ft_printf Compiled!\n\e[0m"
					$(CC) ${OBJS_B} -L./libft -lft -L./ft_printf -lftprintf -o ${PROG_B}
					echo "\033[36mLibft Compiled!\e[0m"
					echo "\033[35mft_printf Compiled!\e[0m"
					echo "\033[32mPipex Compiled!\n\e[0m"

clean:
					make clean -C ./libft
					make fclean -C ./ft_printf
					rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					make fclean -C ./libft
					make fclean -C ./ft_printf
					rm -f ${PROG}
					rm -f ${PROG_B}

re:			fclean all

re_bonus:	fclean bonus

.PHONY: all clean fclean re re_bonus bonus party
