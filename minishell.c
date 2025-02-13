/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:52 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/13 13:47:16 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_echo(t_prompt *prompt)
{
	prompt->echo = exec_echo(prompt->cmd_line, prompt->strs);
	ft_printf("%s", prompt->echo);
	free(prompt->echo);
}

void	exec_exit(void)
{
	write(2, "exit\n", 5);
	exit(1);
}

void	execute_command(t_shell *shell, t_prompt *prompt)
{
	t_list	*temp;

	temp = shell->export_lines;
	if (!ft_strlen(prompt->cmd_line))
		ft_printf("");
	else if (ft_strcmp(prompt->strs[0], "echo") == 0
		&& ft_strcmp(prompt->strs[1], "-n") == 0)
		display_echo(prompt);
	else if (ft_strcmp(prompt->strs[0], "export") == 0
		&& count_words(prompt->cmd_line) == 1)
		write_env(shell->export_lines);
	else if (ft_strcmp(prompt->strs[0], "env") == 0
		&& count_words(prompt->cmd_line) == 1)
		write_env(shell->env_lines);
	else if (ft_strcmp(prompt->strs[0], "cd") == 0
		&& count_strings(prompt->strs) == 2)
		exec_cd(shell, prompt);
	else if (ft_strcmp(prompt->strs[0], "pwd") == 0
		&& count_words(prompt->cmd_line) == 1)
		ft_printf("%s\n", shell->pwd);
	else if (ft_strcmp(prompt->strs[0], "unset") == 0
		&& count_words(prompt->cmd_line) > 1)
		exec_unset(shell, prompt);
	else if (ft_strcmp(prompt->strs[0], "exit") == 0
		&& count_words(prompt->cmd_line) == 1)
		exec_exit();
	else
		ft_printf("command not found: %s\n", prompt->strs[0]);
}

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
		add_history(buffer);
		verif_history(buffer);
		prompt = init_prompt(buffer);
		execute_command(shell, prompt);
		free_prompt(prompt);
	}
	free_terminal(shell);
	return (0);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	t_list		*temp;
	int			i;

	setup_signal();
	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	temp = shell->env_lines;
	i = 0;
	while (temp)
	{
		ft_printf("%s\n", temp->content);
		temp = temp->next;
	}
	free_terminal(shell);
	return (0);
}*/

/*int	main(int argc, char **argv, char **envp)
{
	t_list	*lst;
	t_list	*new;
	t_list	*temp;
	int		i;

	(void)argc;
	(void)argv;
	lst = NULL;
	i = 0;
	while (envp[i])
	{
		new = ft_lstnew((void *)envp[i++]);
		ft_lstadd_back(&lst, new);
	}
	temp = lst;
	while (temp->next)
	{
		ft_printf("%s\n", temp->content);
		temp = temp->next;
	}
	return (0);
}*/
