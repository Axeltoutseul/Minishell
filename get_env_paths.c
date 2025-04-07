/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:49:59 by axbaudri          #+#    #+#             */
/*   Updated: 2025/04/01 14:28:46 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_value(char **envp, char *name)
{
	int		i;
	int		size;
	char	*path;

	i = 0;
	size = ft_strlen(name) + 1;
	while (envp[i] && ft_strncmp(envp[i], name, size - 1) != 0)
	{
		i = i + 1;
	}
	if (!envp[i] || (envp[i] && !ft_strchr(envp[i], '=')))
		return (NULL);
	path = ft_strdup(envp[i] + size);
	return (path);
}

int	get_shell_level(char **envp)
{
	int		i;
	int		shlvl;

	i = 0;
	if (!envp[0])
		return (-1);
	while (ft_strncmp(envp[i], "SHLVL=", 6) != 0)
	{
		i = i + 1;
	}
	shlvl = ft_atoi(envp[i] + 6);
	return (shlvl);
}

char	**split_path(char *env_line)
{
	int		i;
	char	**splitted_path;

	i = 0;
	if (!env_line)
		return (NULL);
	splitted_path = ft_split(env_line, ':');
	i = 0;
	while (splitted_path[i])
	{
		splitted_path[i] = join_and_free(splitted_path[i], "/");
		i = i + 1;
	}
	return (splitted_path);
}

char	*get_command_path(char *cmd, t_shell *shell)
{
	char	*full_path;

	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	if (shell->splitted_path == 0)
		return (0);
	full_path = search_cmd_in_paths(shell->splitted_path, cmd);
	return (full_path);
}
