/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:28:15 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/21 13:03:11 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirections(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->op);
		free(redir->target);
		free(redir);
		redir = tmp;
	}
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;
	int	j;

	if (pipeline == NULL)
		return ;
	i = 0;
	while (i < pipeline->count)
	{
		if (pipeline->commands[i].args)
		{
			j = 0;
			while (pipeline->commands[i].args[j])
			{
				free(pipeline->commands[i].args[j]);
				j++;
			}
			free(pipeline->commands[i].args);
		}
		if (pipeline->commands[i].heredoc_delim)
			free(pipeline->commands[i].heredoc_delim);
		if (pipeline->commands[i].redirections)
			free_redirections(pipeline->commands[i].redirections);
		i++;
	}
	free(pipeline->commands);
	free(pipeline);
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

	if (!count_words(line))
		ft_printf("");
	else if (!closed_quotes(line))
		ft_printf("syntax error: unclosed quote\n");
	else if (is_builtin(prompt->strs[0]))
		execute_builtin(shell, prompt);
	pipeline = parse_input(line);
	if (pipeline != NULL)
	{
		execute_pipeline(shell, pipeline, env);
		free_pipeline(pipeline);
	}
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

/*int	main(int argc, char **argv, char **env)
{
	t_shell		*shell;
	int			i;
	char		*line;
	char		**strs;

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
		strs = split_pipeline(line);
		i = 0;
		while (strs[i])
			ft_printf("%s\n", strs[i++]);
		free(line);
	}
	free_terminal(shell);
	return (0);
}*/
