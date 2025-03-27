/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:49:59 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/27 11:18:49 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_value(char **envp, char *name)
{
	int		i;
	int		size;
	char	*path;

	i = 0;
	size = ft_strlen(name);
	while (ft_strncmp(envp[i], name, size) != 0)
	{
		i = i + 1;
	}
	path = ft_strdup(envp[i] + size);
	return (path);
}

int	get_shell_level(char **envp)
{
	int		i;
	int		shlvl;

	i = 0;
	while (ft_strncmp(envp[i], "SHLVL=", 6) != 0)
	{
		i = i + 1;
	}
	shlvl = ft_atoi(envp[i] + 6);
	return (shlvl);
}

char	**split_path(char **envp)
{
	int		i;
	char	**splitted_path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		i = i + 1;
	}
	splitted_path = ft_split(envp[i] + 5, ':');
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
	char	*full_path;

	if (ft_strchr(cmd, '/') != NULL)
	{
		return (ft_strdup(cmd));
	}
	paths = split_path(env);
	if (paths == 0)
	{
		return (0);
	}
	full_path = search_cmd_in_paths(paths, cmd);
	free_2d_array(paths);
	return (full_path);
}
