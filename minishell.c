/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:52 by axbaudri          #+#    #+#             */
/*   Updated: 2025/04/01 01:24:09 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_shell *shell, t_prompt *prompt)
{
	(void)prompt;
	ft_printf("%s\n", shell->pwd);
}

void	exec_exit(t_shell *shell, t_prompt *prompt)
{
	free_prompt(prompt);
	free_terminal(shell);
	write(2, "exit\n", 5);
	exit(1);
}

void	builtin_exit(t_shell *shell, t_prompt *prompt)
{
	if (ft_strcmp(prompt->strs[0], "echo") == 0)
		shell->exit_status = 0;
	else if (ft_strcmp(prompt->strs[0], "export") == 0)
		shell->exit_status = 0;
	else if (ft_strcmp(prompt->strs[0], "env") == 0)
		shell->exit_status = 0;
	else if (ft_strcmp(prompt->strs[0], "cd") == 0)
		shell->exit_status = 0;
	else if (ft_strcmp(prompt->strs[0], "pwd") == 0)
		shell->exit_status = 0;
	else if (ft_strcmp(prompt->strs[0], "unset") == 0)
		shell->exit_status = 0;
}

void	execute_builtin(t_shell *shell, t_prompt *prompt)
{
	builtin_exit(shell, prompt);
	if (ft_strcmp(prompt->strs[0], "echo") == 0)
		exec_echo(prompt);
	else if (ft_strcmp(prompt->strs[0], "export") == 0)
		exec_export(shell, prompt);
	else if (ft_strcmp(prompt->strs[0], "env") == 0)
		write_env(prompt, shell->env_lines);
	else if (ft_strcmp(prompt->strs[0], "cd") == 0)
		exec_cd(shell, prompt);
	else if (ft_strcmp(prompt->strs[0], "pwd") == 0)
		exec_pwd(shell, prompt);
	else if (ft_strcmp(prompt->strs[0], "unset") == 0)
		exec_unset(shell, prompt);
	else if (ft_strcmp(prompt->strs[0], "exit") == 0)
		exec_exit(shell, prompt);
}
