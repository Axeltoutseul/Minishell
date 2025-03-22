/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:28:15 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/22 17:01:54 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_redirect(char **cmds)
{
	int	i;
	int	end;

	i = 0;
	while (cmds[i])
	{
		end = ft_strlen(cmds[i]) - 1;
		while (cmds[i][end] && is_space(cmds[i][end]))
			end--;
		if (cmds[i][end] == '<' || cmds[i][end] == '>')
			return (1);
		i++;
	}
	return (0);
}

static int	invalid_prompt(char	*line)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(line) - 1;
	if (line[i] == '|' || line[j] == '|')
		return (1);
	while (line[i])
	{
		if (ft_strlen(line + i) >= 2 && line[i] == '|' && line[i + 1] == '|')
			return (1);
		if (ft_strlen(line + i) >= 2 && ((line[i] == '<' && line[i + 1] == '>')
			|| (line[i] == '>' && line[i + 1] == '<')))
			return (1);
		if (ft_strlen(line + i) >= 3)
		{
			if ((line[i] == '<' || line[i] == '>')
				&& (line[i + 1] == '<' || line[i + 1] == '>')
				&& (line[i + 2] == '<' || line[i + 2] == '>'))
				return (1);
		}
		i++;
	}
	return (0);
}

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

void	exec_command(t_shell *shell, t_prompt *prompt, char **env, char *line)
{
	t_pipeline	*pipeline;
	char		*new_string;

	new_string = get_line_without_space(line);
	if (!count_strings(prompt->strs))
		ft_printf("");
	else if (!closed_quotes(line))
		ft_printf("syntax error: unclosed quote\n");
	else if (invalid_prompt(new_string) || invalid_redirect(prompt->cmds))
		ft_printf("syntax error near unexpected token\n");
	else
	{
		if (is_builtin(prompt->strs[0]) && !prompt->cmds[1])
			execute_builtin(shell, prompt);
		pipeline = parse_input(line);
		if (pipeline != NULL)
		{
			execute_pipeline(shell, pipeline, env);
			free_pipeline(pipeline);
		}
	}
	free(new_string);
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
