/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:02:36 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/31 16:56:10 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_env_builtin(t_shell *shell)
{
	t_env	*temp;

	temp = shell->env_lines;
	while (temp)
	{
		if (temp->value)
			ft_printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

static void	process_builtin(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		exec_echo_builtin(cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		if (cmd->args[1] == NULL)
			write_export(shell->export_lines);
	}
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		execute_env_builtin(shell);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_printf("cd: modification de l'env impossible dans un pipe\n");
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_printf("%s\n", shell->pwd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_printf("unset: modification de l'env impossible dans un pipe\n");
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(cmd->args[0], "history") == 0)
		display_history(shell);
	else
		ft_printf("Builtin %s non supporté en pipeline\n", cmd->args[0]);
}

void	execute_builtin_in_child(t_shell *shell, t_command *cmd, char **env)
{
	(void)env;
	process_builtin(shell, cmd);
}
