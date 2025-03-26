/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:29:02 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/26 15:51:14 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

static void	handle_heredoc_in_child(t_command *cmd)
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
}

static void	handle_cat_special_case(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "cat") == 0)
	{
		if (cmd->args[1] == NULL && isatty(STDIN_FILENO))
			close(STDIN_FILENO);
	}
}

void	child_execute(int i, int prev_fd, int pipe_fd[2],
	t_exec_context *ctx)
{
	t_command	*cmd;
	char		*cmd_path;

	cmd = &ctx->pipeline->commands[i];
	setup_child_io(i, prev_fd, pipe_fd, ctx);
	handle_heredoc_in_child(cmd);
	handle_cat_special_case(cmd);
	if (apply_command_redirections(cmd) == -1)
		exit(EXIT_FAILURE);
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin_in_child(ctx->shell, cmd, ctx->env);
		exit(0);
	}
	cmd_path = get_command_path(cmd->args[0], ctx->env);
	if (cmd_path == NULL)
	{
		perror("command not found");
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd->args, ctx->env);
	perror("execve");
	exit(EXIT_FAILURE);
}
