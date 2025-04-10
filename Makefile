# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 13:47:59 by axbaudri          #+#    #+#              #
#    Updated: 2025/04/01 14:56:13 by quenalla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

RM = rm -f

SRCS =	adv_redirection.c \
		adv_tokeniser1.c \
		adv_tokeniser2.c \
		adv_tokeniser3.c \
		build_new_tokens.c \
		check_words.c \
		exec_echo.c \
		exec_export.c \
		exec_unset.c \
		free_terminal.c \
		get_env_paths.c \
		get_env_paths2.c \
		getpid_setenv.c \
		handle_dollar.c \
		handle_dollar2.c \
		handle_paths.c \
		handle_strings.c \
		heredoc.c \
		history.c \
		main.c \
		manage_env_list.c \
		minishell.c \
		new_terminal.c \
		parse_prompt.c \
		parser1.c \
		parser2.c \
		parser3.c \
		pipe_handling.c \
		pipeline.c \
		pipeline2.c \
		pipeline3.c \
		read_content.c \
		redirect_file.c \
		redirect_file2.c \
		shell_instance.c \
		signal.c \
		split_pipeline.c \
		string_utils.c \
		write_content.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) libft/libft.a -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft/

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C libft/

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
