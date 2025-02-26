/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:16:13 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/26 20:54:00 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# include "libft/libft.h"

typedef struct s_prompt
{
	char	*cmd_line;
	char	*echo;
	char	**strs;
}	t_prompt;

typedef struct s_token
{
	char			*arg;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

char		*cpy_word(char *str, int *i);
void		display_echo(t_prompt *prompt);
void		free_prompt(t_prompt *prompt);
t_prompt	*init_prompt(const char *buffer);
int			is_redirect(char c);
void		parse_command_line(char *line);
char		**parse_echo(t_prompt *prompt);
void		tokenizer(char *prompt, t_token **lst);
int			valid_arg(char *name, char *arg);
int			valid_prompt(char *cmd_line);
int			valid_value(char *s);

#endif
