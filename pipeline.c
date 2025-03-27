/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:16:43 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/27 18:24:27 by axbaudri         ###   ########.fr       */
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

int	handle_fork_and_update(int i, int prev_fd, int pipe_fd[2],
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
		child_execute(ctx, i, prev_fd, pipe_fd);
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

static t_exec_context	init_ctx(t_shell *shell, t_pipeline *pipeline,
							char **env)
{
	t_exec_context	ctx;

	ctx.pipeline = pipeline;
	ctx.env = env;
	ctx.cmd_count = pipeline->count;
	ctx.shell = shell;
	return (ctx);
}

static void	handle_single_cat(t_pipeline *pipeline, char **env)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		path = get_command_path(pipeline->commands[0].args[0], env);
		if (path == NULL)
		{
			perror("cat not found");
			exit(EXIT_FAILURE);
		}
		execve(path, pipeline->commands[0].args, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}

void	execute_pipeline(t_shell *shell, t_pipeline *pipeline, char **env)
{
	int				i;
	int				prev_fd;
	int				pipe_fd[2];
	t_exec_context	ctx;

	i = 0;
	prev_fd = -1;
	ctx = init_ctx(shell, pipeline, env);
	if (pipeline->count == 1
		&& !pipeline->commands[0].redirections
		&& !ft_strcmp(pipeline->commands[0].args[0], "cat"))
	{
		handle_single_cat(pipeline, env);
		return ;
	}
	while (i < ctx.cmd_count)
	{
		create_pipe_block(i, ctx.cmd_count, pipe_fd);
		prev_fd = handle_fork_and_update(i, prev_fd, pipe_fd, &ctx);
		i++;
	}
	if (prev_fd != -1)
		close(prev_fd);
}
