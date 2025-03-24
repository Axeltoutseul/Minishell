/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:52 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/24 12:02:16 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	exec_echo(t_prompt *prompt)
{
	int	i;

	i = 1;
	if (ft_strcmp(prompt->strs[1], "-n") == 0)
		i++;
	while (prompt->strs[i])
	{
		if (ft_strcmp(prompt->strs[i], ">") == 0
			|| ft_strcmp(prompt->strs[i], ">>") == 0)
			break ;
		ft_printf("%s", prompt->strs[i]);
		if (prompt->strs[i + 1] && ft_strcmp(prompt->strs[i + 1], ">") != 0
			&& ft_strcmp(prompt->strs[i + 1], ">>") != 0)
			ft_printf(" ");
		i++;
	}
	if (!(prompt->strs[1] && ft_strcmp(prompt->strs[1], "-n") == 0))
		ft_printf("\n");
}*/

void	exec_exit(t_shell *shell, t_prompt *prompt)
{
	free_prompt(prompt);
	free_terminal(shell);
	write(2, "exit\n", 5);
	exit(1);
}

void	execute_builtin(t_shell *shell, t_prompt *prompt)
{
	/*if (ft_strcmp(prompt->strs[0], "echo") == 0)
		exec_echo(prompt);*/
	if (ft_strcmp(prompt->strs[0], "export") == 0 && prompt->strs[1])
		exec_export(shell, prompt);
	/*else if (ft_strcmp(prompt->strs[0], "env") == 0)
		write_env(shell->env_lines);*/
	else if (ft_strcmp(prompt->strs[0], "cd") == 0)
		exec_cd(shell, prompt);
	/*else if (ft_strcmp(prompt->strs[0], "pwd") == 0)
		ft_printf("%s\n", shell->pwd);*/
	else if (ft_strcmp(prompt->strs[0], "unset") == 0)
		exec_unset(shell, prompt);
	else if (ft_strcmp(prompt->strs[0], "exit") == 0)
		exec_exit(shell, prompt);
}
