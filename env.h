/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:44:49 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/26 20:06:57 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

void		add_env_line(t_env **env, t_env *new);
void		copy_env(t_env **env, char **envp);
void		copy_export(t_env **export, char **envp);
int			env_size(t_env *env);
char		*find_path_line(char **envp);
void		free_env_lines(t_env *env);
char		**get_lines_export(char **envp);
char		**get_lines(char **envp);
char		*get_name(char *dest, char *src);
char		*get_pwd(char **envp);
int			get_shell_level(char **envp);
int			is_in_list(t_env *env, char *var_name);
t_env		*new_line(char *env_line);
void		remove_line(t_env **lst, char *arg);
void		sort_strings(char **envp, int size);
char		**split_path(char **envp);
void		update_line(char *arg, t_env **env);
void		write_env(t_env *env);
void		write_export(t_env *env);

#endif
