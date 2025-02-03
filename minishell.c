/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:52 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/03 16:45:43 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_shell *shell, t_prompt *prompt)
{
	if (!prompt->strs)
		ft_printf("");
	if (ft_strcmp(prompt->strs[0], "echo") == 0
		&& ft_strcmp(prompt->strs[1], "-n") == 0)
	{
		shell->echo = exec_echo(prompt->cmd_line, prompt->strs);
		ft_printf("%s\n", shell->echo);
		free(shell->echo);
	}
	else if (ft_strcmp(prompt->cmd_line, "export") == 0
		&& count_words(prompt->cmd_line) == 1)
		write_env(shell->export, prompt);
	else if (ft_strcmp(prompt->cmd_line, "env") == 0
		&& count_words(prompt->cmd_line) == 1)
		write_env(shell->env, prompt);
	else if (ft_strcmp(prompt->cmd_line, "pwd") == 0
		&& count_words(prompt->cmd_line) == 1)
		ft_printf("%s\n", shell->folder_path);
	else if (ft_strcmp(prompt->cmd_line, "exit") == 0
		&& count_words(prompt->cmd_line) == 1)
		exit(1);
	else
		ft_printf("command not found: %s\n", prompt->strs[0]);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_shell		*shell;
	t_prompt	*prompt;
	int			buffer_size;
	const char	*buffer;

	if (argc == 1)
	{
		buffer_size = 2048;
		buffer = (char *)ft_calloc(sizeof(char), buffer_size);
		shell = init_shell(envp);
		buffer = readline("$> ");
		while (buffer)
		{
			prompt = parse_prompt(buffer);
			execute_command(shell, prompt);
			free_prompt(prompt);
			buffer = readline("$> ");
		}
		free_terminal(shell);
	}
	return (0);
}

/*int	main(int argc, char **argv)
{
	char **strs = get_lines(argv + 1);
	int i = 0;
	while (i < argc - 1)
		ft_printf("%s\n", strs[i++]);
	free_2d_array(strs);
	return (0);
}*/
