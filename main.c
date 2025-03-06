/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:28:15 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/06 16:36:34 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd, const char *option)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0 && ft_strcmp(option, "-n") == 0)
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

int	main(int argc, char **argv, char **env)
{
	t_shell		*shell;
	char		*line;
	t_prompt	*prompt;
	t_pipeline	*pipeline;

	(void)argc;
	(void)argv;
	setup_signal();
	shell = init_shell(env);
	while (1)
	{
		line = readline("\033[0;32mminishell> \033[0m");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (line[0] != '\0')
			add_history(line);
		verif_history(shell, line);
		prompt = init_prompt(line);
		if (is_builtin(prompt->strs[0], prompt->strs[1]))
			execute_builtin(shell, prompt);
		else
		{
			pipeline = parse_input(line);
			if (pipeline != NULL)
			{
				execute_pipeline(pipeline, env);
				free_pipeline(pipeline);
			}
		}
		free_prompt(prompt);
		free(line);
	}
	free_terminal(shell);
	return (0);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	t_prompt	*prompt;
	int			i;
	const char	*buffer;

	setup_signal();
	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	while (1)
	{
		i = 0;
		buffer = readline("\033[0;32mminishell> \033[0m");
		if (!buffer)
		{
			write(2, "exit\n", 5);
			break ;
		}
		verif_history(buffer);
		prompt = init_prompt(buffer);
		while (prompt->strs[i])
		{
			ft_printf("prompt->strs[%d] = %s\n", i, prompt->strs[i]);
			i++;
		}
		free_prompt(prompt);
	}
	free_terminal(shell);
	return (0);
}*/
