/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:55 by axbaudri          #+#    #+#             */
/*   Updated: 2024/12/13 18:33:34 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"

typedef struct s_shell
{
	char	*path;
	char	*folder_path;
	char	**splitted_path;
	char	**words;
	char	*echo;
}	t_shell;

int		calculate_total_size(int size, char **strs, char *sep);
int		count_strings(char **strs);
int		count_words(const char *str);
void	execute_command(char **argv, char **envp, t_shell *shell);
char	*find_path_line(char **envp);
char	*first_word(char *str);
void	free_2d_array(char **strs);
void	free_terminal(t_shell *shell);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin2(int size, char **strs, char *sep);
char	*ft_strndup(const char *src, unsigned int n);
char	*get_folder_path(char **envp);
char	**get_lines(char **envp);
t_shell	*init_shell(int argc, char **argv, char **envp);
char	*save_text(int fd);
void	write_env(char **envp);

#endif
