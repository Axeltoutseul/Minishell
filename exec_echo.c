/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:05:39 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/21 12:13:57 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_prompt *prompt)
{
	int	i;

	i = 1;
	if (ft_strcmp(prompt->strs[1], "-n") == 0)
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
