/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:52 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/04 20:01:40 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_echo(t_prompt *prompt)
{
	prompt->echo = exec_echo(prompt->cmd_line, prompt->strs);
	ft_printf("%s", prompt->echo);
	free(prompt->echo);
}

void	execute_command(t_shell *shell, t_prompt *prompt)
{
	if (!ft_strlen(prompt->cmd_line))
		ft_printf("");
	else if (ft_strcmp(prompt->strs[0], "echo") == 0
		&& ft_strcmp(prompt->strs[1], "-n") == 0)
		display_echo(prompt);
	else if (ft_strcmp(prompt->strs[0], "export") == 0
		&& count_words(prompt->cmd_line) == 1)
		write_env(shell->export, prompt);
	else if (ft_strcmp(prompt->strs[0], "env") == 0
		&& count_words(prompt->cmd_line) == 1)
		write_env(shell->env, prompt);
	else if (ft_strcmp(prompt->strs[0], "cd") == 0)
		exec_cd(prompt->strs[1]);
	else if (ft_strcmp(prompt->strs[0], "pwd") == 0
		&& count_words(prompt->cmd_line) == 1)
		ft_printf("%s\n", shell->folder_path);
	else if (ft_strcmp(prompt->strs[0], "exit") == 0
		&& count_words(prompt->cmd_line) == 1)
		exit(1);
	else
		ft_printf("command not found: %s\n", prompt->strs[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	t_prompt	*prompt;
	const char	*buffer;

	(void)argv;
	if (argc == 1)
	{
		shell = init_shell(envp);
		buffer = readline("\033[0;36m> \033[0m");
		while (buffer)
		{
			prompt = parse_prompt(buffer);
			execute_command(shell, prompt);
			free_prompt(prompt);
			buffer = readline("\033[0;36m> \033[0m");
		}
		free_prompt(prompt);
		free_terminal(shell);
	}
	return (0);
}

/*int	main(void)
{
	int i = 0;
	char *buffer = readline("> ");
	char **strs = ft_split(buffer, ' ');
	while (strs[i])
		ft_printf("%s\n", strs[i++]);
	rl_clear_history();
	free(buffer);
	free_2d_array(strs);
	return (0);
}*/
