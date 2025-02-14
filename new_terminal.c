/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:09:19 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/14 16:01:18 by axbaudri         ###   ########.fr       */
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
	shell->splitted_path = split_path(envp);
	shell->shlvl = get_shell_level(envp);
	shell->env_lines = NULL;
	copy_env(&shell->env_lines, envp);
	shell->export = get_lines_export(envp);
	sort_strings(shell->export, count_strings(envp));
	copy_export(shell);
	shell->var_names = get_var_names(envp);
	shell->vars = NULL;
	copy_env(&shell->vars, shell->var_names);
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

void	copy_env(t_list **lst, char **envp)
{
	t_list	*new;
	int		i;

	i = 0;
	while (envp[i])
	{
		new = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back(lst, new);
		i++;
	}
}

void	copy_export(t_shell *shell)
{
	t_list	*new;
	int		i;

	shell->export_lines = NULL;
	i = 0;
	while (shell->export[i + 1])
	{
		new = ft_lstnew(ft_strdup(shell->export[i]));
		ft_lstadd_back(&shell->export_lines, new);
		i++;
	}
}
