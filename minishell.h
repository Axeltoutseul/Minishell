/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:55 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/31 16:46:15 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_shell
{
	char	*cmd_line;
	char	*path;
	char	*folder_path;
	char	*echo;
	char	**splitted_path;
	char	**export;
}	t_shell;

int     calculate_size_for_replace(const char *str, char *a, char *b);
int		calculate_total_size(int size, char **strs, char *sep);
int		count_occurrences(const char *cmd_line, int to_find);
int     count_occurrences2(const char *str, char *to_find);
int		count_quotes(const char *cmd_line);
int		count_strings(char **strs);
int		count_words(const char *str);
char	*exec_echo(char *cmd_line, char **strs);
void	execute_command(char **argv, char **envp, t_shell *shell);
char	*find_path_line(char **envp);
char	*first_word(char *str);
void	free_2d_array(char **strs);
void	free_terminal(t_shell *shell);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin2(int size, char **strs, char *sep);
char	*ft_strndup(const char *src, unsigned int n);
void	ft_swap(char **s1, char **s2);
char	*get_folder_path(char **envp);
char	**get_lines(char **envp);
t_shell	*init_shell(int argc, char **argv, char **envp);
char    *replace(const char *str, char *a, char *b);
char	*save_text(int fd);
void	sort_strings(char **envp, int size);
void	write_env(char **envp);
void	write_sorted_strings(char **strs);

#endif
