/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:49:59 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/26 13:07:41 by qacjl            ###   ########.fr       */
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
	int	i;
	int	shlvl;

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

static char	**get_paths(char **env)
{
	int		i;
	char	*path_var;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i = i + 1;
	}
	if (env[i] == 0)
		return (NULL);
	path_var = env[i] + 5;
	paths = ft_split(path_var, ':');
	return (paths);
}

static char	*join_cmd_to_path(char *path, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

char	*get_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	paths = get_paths(env);
	if (paths == NULL)
		return (NULL);
	i = 0;
	full_path = NULL;
	while (paths[i])
	{
		full_path = join_cmd_to_path(paths[i], cmd);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_2d_array(paths);
			return (full_path);
		}
		free(full_path);
		i = i + 1;
	}
	free_2d_array(paths);
	return (NULL);
}
