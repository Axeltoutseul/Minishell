/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:16:43 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/21 12:47:33 by axbaudri         ###   ########.fr       */
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

static void	exec_echo_builtin(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i = i + 1;
	}
	ft_printf("\n");
}

static void	execute_builtin_in_child(t_shell *shell, t_command *cmd, char **env)
{
	(void)env;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		exec_echo_builtin(cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		if (cmd->args[1] == NULL)
			write_export(shell->export_lines);
	}
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		write_env(NULL, shell->env_lines);
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

static void	send_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
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
	if (cmd->heredoc_delim != NULL)
	{
		hd_fd = handle_heredoc(cmd->heredoc_delim);
		if (hd_fd == -1)
			send_error("heredoc");
		if (dup2(hd_fd, STDIN_FILENO) == -1)
			send_error("dup2 heredoc");
		close(hd_fd);
	}
	if (apply_command_redirections(cmd) == -1)
		exit(EXIT_FAILURE);
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin_in_child(ctx->shell, cmd, ctx->env);
		exit(0);
	}
	cmd_path = get_command_path(cmd->args[0], ctx->shell);
	if (cmd_path == NULL)
		send_error("command not found");
	execve(cmd_path, cmd->args, ctx->env);
	send_error("execve");
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
