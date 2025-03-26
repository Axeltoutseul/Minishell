/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:33:02 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/26 15:46:38 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	handle_echo_export(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
	{
		exec_echo_builtin(cmd);
		return ;
	}
	if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		if (cmd->args[1] == NULL)
			write_export(shell->export_lines);
		return ;
	}
}

static void	handle_env_cd(t_shell *shell, t_command *cmd)
{
	t_env	*temp;

	if (ft_strcmp(cmd->args[0], "env") == 0)
	{
		temp = shell->env_lines;
		while (temp)
		{
			if (temp->value)
				ft_printf("%s=%s\n", temp->name, temp->value);
			temp = temp->next;
		}
		return ;
	}
	if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		ft_printf("cd: modification de l'environnement impossible dans un pipeline\n");
		return ;
	}
}

static void	handle_pwd_unset_exit_history(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
	{
		ft_printf("%s\n", shell->pwd);
		return ;
	}
	if (ft_strcmp(cmd->args[0], "unset") == 0)
	{
		ft_printf("unset: modification de l'environnement impossible dans un pipeline\n");
		return ;
	}
	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		exit(0);
		return ;
	}
	if (ft_strcmp(cmd->args[0], "history") == 0)
	{
		display_history(shell);
		return ;
	}
}

void	execute_builtin_in_child(t_shell *shell, t_command *cmd, char **env)
{
	(void) env;
	if (ft_strcmp(cmd->args[0], "echo") == 0
		|| ft_strcmp(cmd->args[0], "export") == 0)
	{
		handle_echo_export(shell, cmd);
		return ;
	}
	if (ft_strcmp(cmd->args[0], "env") == 0
		|| ft_strcmp(cmd->args[0], "cd") == 0)
	{
		handle_env_cd(shell, cmd);
		return ;
	}
	if (ft_strcmp(cmd->args[0], "pwd") == 0
		|| ft_strcmp(cmd->args[0], "unset") == 0
		|| ft_strcmp(cmd->args[0], "exit") == 0
		|| ft_strcmp(cmd->args[0], "history") == 0)
	{
		handle_pwd_unset_exit_history(shell, cmd);
		return ;
	}
	ft_printf("Builtin %s non supporté en pipeline\n", cmd->args[0]);
}
