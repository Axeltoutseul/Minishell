/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:16:43 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/27 09:53:54 by qacjl            ###   ########.fr       */
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

static void	execute_builtin_in_child(t_shell *shell, t_command *cmd, char **env)
{
	t_env	*temp;

	(void)env;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		exec_echo_builtin(cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		if (cmd->args[1] == NULL)
			write_export(shell->export_lines);
	}
	else if (ft_strcmp(cmd->args[0], "env") == 0)
	{
		temp = shell->env_lines;
		while (temp)
		{
			if (temp->value)
				ft_printf("%s=%s\n", temp->name, temp->value);
			temp = temp->next;
		}
	}
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_printf("cd: modification de l'environnement impossible dans un pipeline\n");
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_printf("%s\n", shell->pwd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_printf("unset: modification de l'environnement impossible dans un pipeline\n");
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(cmd->args[0], "history") == 0)
		display_history(shell);
	else
		ft_printf("Builtin %s non supporté en pipeline\n", cmd->args[0]);
}

static void	child_execute(int i, int prev_fd, int pipe_fd[2], t_exec_context *ctx)
{
	t_command	*cmd;
	char		*cmd_path;
	int			hd_fd;

	cmd = &ctx->pipeline->commands[i];
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
	if (ft_strcmp(cmd->args[0], "cat") == 0 && cmd->args[1] == NULL && isatty(STDIN_FILENO))
		close(STDIN_FILENO);
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

static t_exec_context	init_ctx(t_shell *shell, t_pipeline *pipeline, char **env)
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
