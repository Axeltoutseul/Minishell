/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:28:15 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/25 15:38:06 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "history") == 0)
		return (1);
	return (0);
}

int	contains_redirection(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], ">")
			|| !ft_strcmp(tokens[i], ">>")
			|| !ft_strcmp(tokens[i], "<")
			|| !ft_strcmp(tokens[i], "<<"))
			return (1);
		i++;
	}
	return (0);
}

void	exec_command(t_shell *shell, t_prompt *prompt, char **env, char *line)
{
	t_pipeline	*pipeline;
	int			i;

	if (!ft_strlen(line) || !count_strings(prompt->strs))
		return ;
	if (!ft_strchr(line, '|') && is_builtin(prompt->strs[0])
		&& !contains_redirection(prompt->strs))
	{
		execute_builtin(shell, prompt);
		return ;
	}
	pipeline = parse_input(line);
	i = 0;
	while (i < pipeline->count)
	{
		if (pipeline->commands[i].heredoc_delim)
		{
			pipeline->commands[i].heredoc_fd = handle_heredoc_parent_pipe
				(pipeline->commands[i].heredoc_delim);
			if (pipeline->commands[i].heredoc_fd == -1)
			{
				free_pipeline(pipeline);
				return ;
			}
			free(pipeline->commands[i].heredoc_delim);
			pipeline->commands[i].heredoc_delim = NULL;
		}
		i++;
	}
	execute_pipeline(shell, pipeline, env);
	free_pipeline(pipeline);
}

int	main(int argc, char **argv, char **env)
{
	t_shell		*shell;
	char		*line;
	t_prompt	*prompt;

	(void)argc;
	(void)argv;
	setup_signal();
	shell = init_shell(env);
	while (1)
	{
		line = readline("\001\033[0;32m\002minishell> \001\033[0m\002");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		verif_history(shell, line);
		prompt = init_prompt(line);
		exec_command(shell, prompt, env, line);
		free_prompt(prompt);
		free(line);
	}
	free_terminal(shell);
	return (0);
}
