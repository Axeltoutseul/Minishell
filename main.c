/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:28:15 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/31 16:29:09 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int			state;

	state = 0;
	if (!count_strings(prompt->strs) || !closed_quotes(line))
		return ;
	tmp = get_line_without_space(line);
	if (invalid_prompt(tmp, &state))
	{
		if (invalid_prompt(tmp, &state) == 2)
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

int	main(int argc, char **argv, char **env)
{
	t_shell		*shell;
	char		*line;
	t_prompt	*prompt;

	(void)argc;
	(void)argv;
	shell = init_shell(env);
	check_signal(&shell->shlvl);
	while (1)
	{
		line = readline("\001\033[0;32m\002minishell> \001\033[0m\002");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
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
	return (0);
}
