/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:49:59 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/31 20:11:00 by axbaudri         ###   ########.fr       */
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

char	*get_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_line;
	char	*full_path;

	if (ft_strchr(cmd, '/') != NULL)
	{
		return (ft_strdup(cmd));
	}
	path_line = get_path_value(env, "PATH");
	paths = split_path(path_line);
	if (paths == 0)
	{
		return (0);
	}
	full_path = search_cmd_in_paths(paths, cmd);
	free_2d_array(paths);
	free(path_line);
	return (full_path);
}
