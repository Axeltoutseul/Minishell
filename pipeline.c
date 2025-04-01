/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:16:43 by qacjl             #+#    #+#             */
/*   Updated: 2025/04/01 01:53:55 by qacjl            ###   ########.fr       */
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

/*static void	handle_single_cat(t_pipeline *pipeline, char **env)
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
}*/

static pid_t	run_pipeline_command(t_exec_context *ctx, int i, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;

	create_pipe_block(i, ctx->cmd_count, pipe_fd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_execute(ctx, i, *prev_fd, pipe_fd);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < ctx->cmd_count - 1)
	{
		*prev_fd = pipe_fd[0];
		close(pipe_fd[1]);
	}
	else
		*prev_fd = -1;
	return (pid);
}

void	execute_pipeline(t_shell *shell, t_pipeline *pipeline, char **env)
{
	int				i;
	int				prev_fd;
	t_exec_context	ctx;
	pid_t			last_pid;

	i = 0;
	prev_fd = -1;
	ctx = init_ctx(shell, pipeline, env);
	while (i < ctx.cmd_count)
	{
		last_pid = run_pipeline_command(&ctx, i, &prev_fd);
		i++;
	}
	if (prev_fd != -1)
		close(prev_fd);
	waitpid(last_pid, &shell->exit_status, 0);
	if (WIFEXITED(shell->exit_status))
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	else if (WIFSIGNALED(shell->exit_status))
		shell->exit_status = 128 + WTERMSIG(shell->exit_status);
}
