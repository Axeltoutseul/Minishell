/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:07:10 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/27 20:45:10 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_shell *shell, t_prompt *prompt)
{
	char	buffer[PATH_MAX];

	if (prompt->nb_args == 2 && chdir(prompt->strs[1]) != 0)
		ft_printf("cd: no such file or directory: %s\n", prompt->strs[1]);
	else if (prompt->nb_args > 2)
		ft_printf("cd: string not in pwd: %s\n", prompt->strs[1]);
	else
	{
		if (prompt->nb_args == 1)
			chdir(shell->home_path);
		if (ft_strcmp(shell->old_pwd, shell->pwd) != 0)
		{
			free(shell->old_pwd);
			shell->old_pwd = ft_strdup(shell->pwd);
		}
		getcwd(buffer, PATH_MAX);
		free(shell->pwd);
		shell->pwd = ft_strdup(buffer);
	}
	update_paths(shell, &shell->env_lines);
	update_paths(shell, &shell->export_lines);
}

void	update_paths(t_shell *shell, t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->name, "OLDPWD") == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(shell->old_pwd);
		}
		else if (ft_strcmp(temp->name, "PWD") == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(shell->pwd);
		}
		temp = temp->next;
	}
}
