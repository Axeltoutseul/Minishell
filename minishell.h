/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:55 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/04 12:21:20 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_shell
{
	char	*path;
	char	*folder_path;
	char	*echo;
	char	**splitted_path;
	char	**env;
	char	**export;
}	t_shell;

typedef struct s_prompt
{
	char	*cmd_line;
	char	**strs;
}	t_prompt;

int			calculate_size_for_replace(const char *str, char *a, char *b);
int			calculate_total_size(int size, char **strs, char *sep);
int			check_path_validity(char *cmd);
int			count_occurrences(const char *cmd_line, int to_find);
int			count_occurrences2(const char *str, char *to_find);
int			count_quotes(const char *cmd_line);
int			count_strings(char **strs);
int			count_words(const char *str);
char		*exec_echo(char *cmd_line, char **strs);
int			existing_command(char **paths, char *cmd);
void		execute_command(t_shell *shell, t_prompt *prompt);
char		*find_path_line(char **envp);
char		*first_word(char *str);
void		free_2d_array(char **strs);
void		free_prompt(t_prompt *prompt);
void		free_terminal(t_shell *shell);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin2(int size, char **strs, char *sep);
char		*ft_strndup(const char *src, unsigned int n);
void		ft_swap(char **s1, char **s2);
char		*get_folder_path(char **envp);
char		**get_lines(char **envp);
t_shell		*init_shell(char **envp);
t_prompt	*parse_prompt(const char *buffer);
char		*replace(const char *str, char *a, char *b);
char		*save_text(int fd);
void		sort_strings(char **envp, int size);
void		write_env(char **envp, t_prompt *prompt);
void		write_sorted_strings(char **strs);

#endif
