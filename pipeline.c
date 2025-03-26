/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:16:43 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/26 15:34:46 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_pipe_block(int i, int cmd_count, int pipe_fd[2])
{
	if (i < cmd_count - 1)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
}

static int	handle_fork_and_update(int i, int prev_fd, int pipe_fd[2],
			t_exec_context *ctx)
{
	pid_t	pid;
	int		new_prev_fd;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_execute(i, prev_fd, pipe_fd, ctx);
	if (prev_fd != -1)
		close(prev_fd);
	if (i < ctx->cmd_count - 1)
	{
		new_prev_fd = pipe_fd[0];
		close(pipe_fd[1]);
	}
	else
		new_prev_fd = -1;
	waitpid(pid, NULL, 0);
	return (new_prev_fd);
}

void	execute_pipeline(t_shell *shell, t_pipeline *pipeline, char **env)
{
	int				i;
	int				prev_fd;
	int				pipe_fd[2];
	t_exec_context	ctx;

	i = 0;
	prev_fd = -1;
	ctx.pipeline = pipeline;
	ctx.env = env;
	ctx.cmd_count = pipeline->count;
	ctx.shell = shell;
	while (i < ctx.cmd_count)
	{
		create_pipe_block(i, ctx.cmd_count, pipe_fd);
		prev_fd = handle_fork_and_update(i, prev_fd, pipe_fd, &ctx);
		i++;
	}
	if (prev_fd != -1)
		close(prev_fd);
}
