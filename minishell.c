/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:52 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/31 13:52:32 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	execute_command(char **strs, char **envp, t_shell *shell)
{
	char	**words;
	char	*echo;

	words = ft_split(shell->cmd_line, ' ');
	echo = ft_strjoin2(count_words(strs[0] - 2), words + 2, " ");
	if (ft_strcmp(strs[0], "echo") == 0 && ft_strcmp(strs[1], "-n") == 0)
		ft_printf("%s", echo);
	else if (ft_strcmp(strs[0], "env") == 0
		&& count_words(strs[0]) == 1)
		write_env(envp);
	else if (ft_strcmp(words[0], "pwd") == 0
		&& count_words(strs[0]) == 1)
		ft_printf("%s\n", shell->folder_path);
	free_2d_array(words);
	free(echo);
}*/

void	execute_command(char **strs, char **envp, t_shell *shell)
{
	char	**words;
	char	*echo;

	if (ft_strcmp(strs[0], "echo") == 0 && ft_strcmp(strs[1], "-n") == 0)
	{
		words = ft_split(shell->cmd_line, ' ');
		echo = ft_strjoin2(count_words(shell->cmd_line) - 2, words + 2, " ");
		ft_printf("%s\n", echo);
		free_2d_array(words);
		free(echo);
	}
	else if (ft_strcmp(shell->cmd_line, "export") == 0
		&& count_words(shell->cmd_line) == 1)
		write_env(shell->export);
	else if (ft_strcmp(shell->cmd_line, "env") == 0
		&& count_words(shell->cmd_line) == 1)
		write_env(envp);
	else if (ft_strcmp(shell->cmd_line, "pwd") == 0
		&& count_words(shell->cmd_line) == 1)
		ft_printf("%s\n", shell->folder_path);
	else if (ft_strcmp(shell->cmd_line, "exit") == 0
		&& count_words(shell->cmd_line) == 1)
		exit(1);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	int			buffer_size;
	const char	*buffer;
	char		**strs;

	if (argc == 1)
	{
		buffer_size = 2048;
		buffer = (char *)ft_calloc(sizeof(char), buffer_size);
		shell = init_shell(argc, argv, envp);
		buffer = readline("$> ");
		strs = ft_split(buffer, ' ');
		while (buffer)
		{
			shell->cmd_line = ft_strdup(buffer);
			execute_command(strs, envp, shell);
			free(shell->cmd_line);
			buffer = readline("$> ");
			strs = ft_split(buffer, ' ');
		}
		free_terminal(shell);
	}
	return (0);
}*/

int	main(int argc, char **argv)
{
	int		count;
	if (argc > 1)
	{
		count = count_quotes(argv[1]);
		ft_printf("%d", count);
	}
	return (0);
}
