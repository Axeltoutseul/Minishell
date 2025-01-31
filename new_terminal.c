/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:09:19 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/31 16:00:41 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->path = find_path_line(envp);
	shell->folder_path = get_folder_path(envp);
	shell->splitted_path = ft_split(shell->path, ':');
	shell->export = get_lines(envp);
	sort_strings(shell->export, count_strings(envp));
	return (shell);
}

char	*find_path_line(char **envp)
{
	int		i;
	char	*path_line;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path_line = ft_strdup(envp[i] + 5);
	return (path_line);
}

char	*get_folder_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strncmp(envp[i], "PWD=", 4) != 0)
		i++;
	path = ft_strdup(envp[i] + 4);
	return (path);
}
