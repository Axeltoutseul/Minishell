/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_instance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:40:20 by qacjl             #+#    #+#             */
/*   Updated: 2025/04/01 01:35:49 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_shell	*g_shell_instance = NULL;

void	set_shell_instance(t_shell *shell)
{
	g_shell_instance = shell;
}

t_shell	*get_shell_instance(void)
{
	return (g_shell_instance);
}
