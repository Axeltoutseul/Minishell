/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:52 by axbaudri          #+#    #+#             */
/*   Updated: 2024/12/13 18:37:05 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char **argv, char **envp, t_shell *shell)
{
	if (ft_strcmp(shell->words[0], "echo") == 0
		&& ft_strcmp(shell->words[1], "-n") == 0)
		ft_printf("%s", shell->echo);
	else if (ft_strcmp(shell->words[0], "env") == 0
		&& count_words(argv[1]) == 1)
		write_env(envp);
	else if (ft_strcmp(shell->words[0], "pwd") == 0
		&& count_words(argv[1]) == 1)
		ft_printf("%s\n", shell->folder_path);
}

/*int	count_occurrences(char *str, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}*/

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc != 2)
		ft_printf("");
	else
	{
		shell = init_shell(argc, argv, envp);
		execute_command(argv, envp, shell);
		free_terminal(shell);
	}
	return (0);
}
