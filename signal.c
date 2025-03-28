/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:16:58 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/28 13:57:19 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "signal.h"

static int	g_last_exit_status = 0;

int	get_last_exit_status(void)
{
    return (g_last_exit_status);
}

void	set_last_exit_status(int status)
{
    g_last_exit_status = status;
}

void	handle_sigint(int sig)
{
	(void)sig;
	set_last_exit_status(130);
	rl_set_prompt("\001\033[0;32m\002minishell> \001\033[0m\002");
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	check_signal(int *shlvl)
{
	if (*shlvl <= 1)
		setup_signal();
	else
		signal(SIGINT, SIG_DFL);
}

