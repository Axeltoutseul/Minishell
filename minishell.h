/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:55 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/10 14:01:47 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include "libft/libft.h"

typedef struct s_shell
{
	int		shlvl;
	char	*path;
	char	*pwd;
	char	*old_pwd;
	char	**splitted_path;
	char	**env;
	char	**export;
	char	**var_names;
}	t_shell;

typedef struct s_prompt
{
	char	*cmd_line;
	char	*echo;
	char	**strs;
}	t_prompt;

int			calculate_size_for_replace(const char *str, char *a, char *b);
int			calculate_total_size(int size, char **strs, char *sep);
int			check_path_validity(char *cmd);
char		*copy_line_with_quotes(char *src);
int			count_occurrences(const char *cmd_line, int to_find);
int			count_occurrences2(const char *str, char *to_find);
int			count_quotes(const char *cmd_line);
int			count_strings(char **strs);
int			count_words(const char *str);
void		display_echo(t_prompt *prompt);
void		exec_cd(t_shell *shell, t_prompt *prompt);
char		*exec_echo(char *cmd_line, char **strs);
void		exec_unset(t_shell *shell, t_prompt *prompt);
int			existing_command(char **paths, char *cmd);
void		execute_command(t_shell *shell, t_prompt *prompt);
char		*find_path_line(char **envp);
char		*find_third_word(const char *cmd_line);
char		*first_word(char *str);
void		free_2d_array(char **strs);
void		free_prompt(t_prompt *prompt);
void		free_terminal(t_shell *shell);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin2(int size, char **strs, char *sep);
char		*ft_strndup(const char *src, size_t n);
void		ft_swap(char **s1, char **s2);
char		**get_lines_export(char **envp);
char		**get_lines(char **envp);
char		*get_pwd(char **envp);
int			get_shell_level(char **envp);
char		**get_var_names(char **envp);
t_shell		*init_shell(char **envp);
char		*join_strings(char **strs);
char		**parse_echo(t_prompt *prompt);
t_prompt	*parse_prompt(const char *buffer);
char		*replace(const char *str, char *a, char *b);
void		remove_line(t_shell *shell, char *var);
char		*save_text(int fd);
void		sort_strings(char **envp, int size);
void		update_paths(t_shell *shell, char **envp);
void		write_env(char **envp, t_prompt *prompt);

#endif
