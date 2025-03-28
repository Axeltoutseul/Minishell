/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:05:39 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/28 14:34:24 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_prompt *prompt)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (prompt->strs[i] && is_valid_n_option(prompt->strs[i]))
	{
		newline = 0;
		i++;
	}
	while (prompt->strs[i])
	{
		ft_printf("%s", prompt->strs[i]);
		if (prompt->strs[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
}

void	exec_echo_builtin(t_command *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->args[i] && is_valid_n_option(cmd->args[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
}
