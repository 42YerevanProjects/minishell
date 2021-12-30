NAME = minishell
SRCS = srcs/main.c srcs/signal.c srcs/parse_and_execute.c srcs/parse/extract_token.c \
	   srcs/parse/get_tokens.c srcs/env/ft_getenv.c srcs/env/ft_is_valid_identifier.c \
	   srcs/env/ft_separate_identifier.c srcs/parse/ft_append_token.c srcs/parse/parse_commands.c \
	   srcs/parse/extract_argument.c srcs/parse/check_pipe.c \
	   utils/shlvl.c utils/init.c utils/ft_token_num.c utils/ft_isspace.c utils/ft_minishell_error.c \
	   utils/ft_abs.c utils/ft_matrixlen.c utils/cleanup.c utils/ft_count_commands.c utils/ft_args_size.c \
	   utils/ft_array_copy.c
 
OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror

Include = -lreadline

RM = rm -rf



all: ${NAME}
${NAME}:${OBJS}
	@echo "\n"
	@echo "\033[0;32mCompiling minishell..."
	@${MAKE} -C ./libft/
	@${CC} ${CFLAGS} ${OBJS} ${Include} ./libft/libft.a -o ${NAME} 	
	@echo "\n\033[0;32mDone !"

clean:
	@echo "\033[0;31mCleaning libft..."
	@${MAKE} clean -C ./libft/
	@echo "\nRemoving binaries..."
	@${RM} ${OBJS}
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C ./libft/
	@echo "\nDeleting objects..."
	@${RM} ${OBJS}
	@echo "\nDeleting executable..."
	@${RM} ${NAME}
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re
