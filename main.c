/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:28:15 by axbaudri          #+#    #+#             */
/*   Updated: 2025/04/01 02:10:21 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_cmd(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->count)
	{
		if (pipeline->commands[i].heredoc_delim)
		{
			pipeline->commands[i].heredoc_fd = handle_heredoc_parent_pipe
				(pipeline->commands[i].heredoc_delim);
			if (pipeline->commands[i].heredoc_fd == -1)
				return (free_pipeline(pipeline));
			free(pipeline->commands[i].heredoc_delim);
			pipeline->commands[i].heredoc_delim = NULL;
		}
		i++;
	}
}

void	exec_command2(t_pipeline *pipeline, t_shell *shell, char **env)
{
	check_cmd(pipeline);
	signal(SIGINT, SIG_IGN);
	execute_pipeline(shell, pipeline, env);
	signal(SIGINT, handle_sigint);
	free_pipeline(pipeline);
}

void	exec_command(t_shell *shell, t_prompt *prompt, char **env, char *line)
{
	char		*tmp;
	t_pipeline	*pipeline;

	if (!count_strings(prompt->strs) || !closed_quotes(line))
		return ;
	tmp = get_line_without_space(line);
	if (invalid_prompt(tmp))
	{
		if (invalid_prompt(tmp) == 2)
			ft_printf("bash: syntax error near unexpected token `|'\n");
		else
			ft_printf("bash: syntax error near unexpected token `newline'\n");
		return (free(tmp));
	}
	free(tmp);
	if (!ft_strchr(line, '|') && is_builtin(prompt->strs[0])
		&& !contains_redirection(prompt->strs))
		return (execute_builtin(shell, prompt));
	pipeline = parse_input(line, shell->env);
	if (pipeline == NULL)
		return ;
	exec_command2(pipeline, shell, env);
}

static int	process_input(t_shell *shell, char **env)
{
	char		*line;
	t_prompt	*prompt;

	line = readline("\001\033[0;32m\002minishell> \001\033[0m\002");
	if (line == NULL)
	{
		write(1, "exit\n", 5);
		shell->exit_status = 1;
		return (-1);
	}
	verif_history(shell, line);
	prompt = init_prompt(line, shell->env);
	exec_command(shell, prompt, env, line);
	update_vars(shell);
	free_prompt(prompt);
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell		*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(env);
	set_shell_instance(shell);
	check_signal(&shell->shlvl);
	while (process_input(shell, env) != -1)
		;
	free_terminal(shell);
	return (shell->exit_status);
}
/*int	main(int argc, char **argv, char **env)
{
	t_shell		*shell;
	char		*line;
	t_prompt	*prompt;

	(void)argc;
	(void)argv;
	shell = init_shell(env);
	set_shell_instance(shell);
	check_signal(&shell->shlvl);
	while (1)
	{
		line = readline("\001\033[0;32m\002minishell> \001\033[0m\002");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			shell->exit_status = 1;
			break ;
		}
		verif_history(shell, line);
		prompt = init_prompt(line, shell->env);
		exec_command(shell, prompt, env, line);
		update_vars(shell);
		free_prompt(prompt);
		free(line);
	}
	free_terminal(shell);
	return (shell->exit_status);
}*/
