# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 13:47:59 by axbaudri          #+#    #+#              #
#    Updated: 2025/02/14 18:42:55 by axbaudri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

RM = rm -f

SRCS = check_command_line.c \
	exec_echo.c \
	exec_export.c \
	exec_unset.c \
	free_terminal.c \
	get_env_paths.c \
	handle_paths.c \
	handle_strings.c \
	history.c \
	minishell.c \
	new_terminal.c \
	parse_command_line.c \
	pipex.c \
	read_content.c \
	replace.c \
	signal.c \
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
