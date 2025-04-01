/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:05:14 by qacjl             #+#    #+#             */
/*   Updated: 2025/04/01 02:00:26 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_io(int i, int prev_fd, int pipe_fd[2],
		t_exec_context *ctx)
{
	if (i != 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i < ctx->cmd_count - 1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

/*static void	handle_heredoc_and_cat(t_command *cmd)
{
	int	hd_fd;

	if (cmd->heredoc_fd != -1)
	{
		hd_fd = cmd->heredoc_fd;
		if (dup2(hd_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			exit(EXIT_FAILURE);
		}
		close(hd_fd);
	}
}*/

static void	run_external_command(t_exec_context *ctx, t_command *cmd)
{
	char	*path;

	path = get_command_path(cmd->args[0], ctx->env);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", cmd->args[0]);
		ctx->shell->exit_status = 127;
		exit(127);
	}
	if (execve(path, cmd->args, ctx->env) == -1)
	{
		perror("minishell");
		ctx->shell->exit_status = 126;
		exit(126);
	}
	free(path);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	handle_child_command(t_exec_context *ctx, t_command *cmd)
{
	if (apply_command_redirections(cmd) == -1)
		exit(EXIT_FAILURE);
	if (cmd->args[0] == NULL || cmd->args[0][0] == '\0')
		exit(0);
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin_in_child(ctx->shell, cmd, ctx->env);
		exit(0);
	}
	run_external_command(ctx, cmd);
}

void	child_execute(t_exec_context *ctx, int i, int prev_fd, int pipe_fd[2])
{
	t_command	*cmd;

	cmd = &ctx->pipeline->commands[i];
	setup_child_io(i, prev_fd, pipe_fd, ctx);
	if (cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			exit(EXIT_FAILURE);
		}
		close(cmd->heredoc_fd);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_child_command(ctx, cmd);
}
