/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:28:15 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/27 09:43:53 by qacjl            ###   ########.fr       */
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

void	exec_command(t_shell *shell, t_prompt *prompt, char **env, char *line)
{
	char		*tmp;
	int			j;
	t_pipeline	*pipeline;

	if (!count_strings(prompt->strs) || !closed_quotes(line))
		return ;
	tmp = get_line_without_space(line);
	j = ft_strlen(tmp) - 1;
	if (tmp[0] == '|' || tmp[j] == '|' || invalid_prompt(tmp))
	{
		if (tmp[0] == '|' || tmp[j] == '|')
			ft_printf("bash: syntax error near unexpected token `|'\n");
		else
			ft_printf("bash: syntax error near unexpected token `newline'\n");
		free(tmp);
		return ;
	}
	free(tmp);
	if (!ft_strchr(line, '|') && is_builtin(prompt->strs[0])
		&& !contains_redirection(prompt->strs))
		return (execute_builtin(shell, prompt));
	pipeline = parse_input(line);
	if (pipeline == NULL)
		return ;
	check_cmd(pipeline);
	signal(SIGINT, SIG_IGN);
	execute_pipeline(shell, pipeline, env);
	signal(SIGINT, handle_sigint);
	free_pipeline(pipeline);
}

int	main(int argc, char **argv, char **env)
{
	t_shell		*shell;
	char		*line;
	t_prompt	*prompt;
	char		*shlvl_env;
	int			shlvl;

	(void)argc;
	(void)argv;
	shlvl_env = getenv("SHLVL");
	shlvl = 0;
	if (shlvl_env)
		shlvl = atoi(shlvl_env);
	if (shlvl <= 1)
		setup_signal();
	else
		signal(SIGINT, SIG_DFL);
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
