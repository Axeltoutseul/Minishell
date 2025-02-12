/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:09:19 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/12 19:50:23 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->path = find_path_line(envp);
	shell->old_pwd = get_pwd(envp);
	shell->pwd = get_pwd(envp);
	shell->splitted_path = ft_split(shell->path, ':');
	shell->shlvl = get_shell_level(envp);
	copy_env(shell, envp);
	shell->export = get_lines_export(envp);
	sort_strings(shell->export, count_strings(envp));
	copy_export(shell);
	shell->var_names = get_var_names(envp);
	return (shell);
}

// echo "salut commment ca" va mon "amis"

/*
	char **cmd;

	cmd[0] = echo;
	cmd[0] = salut comment ca;
	cmd[0] = va;
	cmd[0] = mon;
	cmd[0] = amis;
*/

t_prompt	*init_prompt(const char *buffer)
{
	t_prompt	*prompt;

	prompt = (t_prompt *)malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	prompt->cmd_line = ft_strdup(buffer);
	prompt->strs = ft_split(buffer, ' ');
	return (prompt);
}
