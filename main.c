/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:28:15 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/04 16:39:57 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_pipeline	*pipeline;

	(void)argc;
	(void)argv;
	setup_signal();
	while (1)
	{
		line = readline("\033[0;32mminishell> \033[0m");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		verif_history(line);
		pipeline = parse_input(line);
		if (pipeline != NULL)
		{
			execute_pipeline(pipeline, env);
			free_pipeline(pipeline);
		}
		free(line);
	}
	return (0);
}*/

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	t_prompt	*prompt;
	const char	*buffer;

	setup_signal();
	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	while (1)
	{
		buffer = readline("\033[0;32mminishell> \033[0m");
		if (!buffer)
		{
			write(2, "exit\n", 5);
			break ;
		}
		verif_history(buffer);
		prompt = init_prompt(buffer);
		if (valid_prompt(buffer))
			execute_builtin(shell, prompt);
		free_prompt(prompt);
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
