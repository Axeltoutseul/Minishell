/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:05:39 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/27 09:51:19 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_prompt *prompt)
{
	int	i;

	i = 1;
	if (prompt->strs[i] && ft_strcmp(prompt->strs[i], "-n") == 0)
		i++;
	while (prompt->strs[i])
	{
		if (ft_strcmp(prompt->strs[i], ">") == 0
			|| ft_strcmp(prompt->strs[i], ">>") == 0)
			break ;
		if (ft_strcmp(prompt->strs[i], "|") == 0)
			break ;
		ft_printf("%s", prompt->strs[i]);
		if (prompt->strs[i + 1] && ft_strcmp(prompt->strs[i + 1], ">") != 0
			&& ft_strcmp(prompt->strs[i + 1], ">>") != 0)
			ft_printf(" ");
		i++;
	}
	if (!(prompt->strs[1] && ft_strcmp(prompt->strs[1], "-n") == 0))
		ft_printf("\n");
}

void	exec_echo_builtin(t_command *cmd)
{
	int	i;

	i = 1;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
		i++;
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i = i + 1;
	}
	if (!(cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 0))
		ft_printf("\n");
}
