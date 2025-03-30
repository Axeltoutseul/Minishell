/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:07:10 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/30 17:59:11 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_vars(t_shell *shell)
{
	free_2d_array(shell->env);
	shell->env = get_env_lines(shell->env_lines);
	free(shell->path);
	free(shell->home_path);
	free(shell->old_pwd);
	free(shell->pwd);
	free_2d_array(shell->splitted_path);
	shell->path = get_path_value(shell->env, "PATH");
	shell->home_path = get_path_value(shell->env, "HOME");
	shell->old_pwd = get_path_value(shell->env, "OLDPWD");
	shell->pwd = get_path_value(shell->env, "PWD");
	shell->splitted_path = split_path(shell->path);
}

static void	check_home_path(t_shell *shell)
{
	if (shell->home_path == NULL)
		ft_printf("bash: cd : HOME not set\n");
	else
	{
		if (chdir(shell->home_path) != 0)
			ft_printf("cd: no such file or directory: %s\n", shell->home_path);
		free(shell->pwd);
		shell->pwd = ft_strdup(shell->home_path);
	}
}

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
			check_home_path(shell);
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
			free(temp->line);
			temp->line = ft_strjoin("OLDPWD", "=");
			temp->line = join_and_free(temp->line, shell->old_pwd);
		}
		else if (ft_strcmp(temp->name, "PWD") == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(shell->pwd);
			free(temp->line);
			temp->line = ft_strjoin("PWD", "=");
			temp->line = join_and_free(temp->line, shell->pwd);
		}
		temp = temp->next;
	}
}
