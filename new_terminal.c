/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:09:19 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/22 13:26:51 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->path = get_path_value(envp, "PATH=");
	shell->home_path = get_path_value(envp, "HOME=");
	shell->old_pwd = get_path_value(envp, "PWD=");
	shell->pwd = get_path_value(envp, "PWD=");
	shell->splitted_path = split_path(envp);
	shell->shlvl = get_shell_level(envp);
	shell->env = get_lines(envp);
	shell->env_lines = NULL;
	copy_env(&shell->env_lines, envp);
	shell->export_lines = NULL;
	copy_export(&shell->export_lines, envp);
	shell->history = NULL;
	return (shell);
}

t_prompt	*init_prompt(const char *buffer)
{
	t_prompt	*prompt;
	char		*expanded;

	prompt = malloc(sizeof(t_prompt));
	if (prompt == NULL)
		return (NULL);
	expanded = expand_variables(buffer);
	prompt->cmd_line = ft_strdup(expanded);
	prompt->cmds = split_pipeline(prompt->cmd_line);
	prompt->strs = advanced_tokenize(expanded);
	prompt->nb_args = count_strings(prompt->strs);
	free(expanded);
	return (prompt);
}

void	copy_env(t_env **env, char **envp)
{
	t_env	*new;
	int		i;

	i = 0;
	while (envp[i])
	{
		new = new_line(envp[i]);
		add_env_line(env, new);
		i++;
	}
}

void	copy_export(t_env **export, char **envp)
{
	t_env	*new;
	int		i;

	sort_strings(envp, count_strings(envp));
	i = 0;
	while (envp[i])
	{
		if (!(envp[i][0] == '_' && envp[i][1] == '='))
		{
			new = new_line(envp[i]);
			add_env_line(export, new);
		}
		i++;
	}
}
