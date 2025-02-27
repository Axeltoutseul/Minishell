/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:49:59 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/27 20:00:38 by axbaudri         ###   ########.fr       */
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
		i++;
	path = ft_strdup(envp[i] + size);
	return (path);
}

int	get_shell_level(char **envp)
{
	int	i;
	int	shlvl;

	i = 0;
	while (ft_strncmp(envp[i], "SHLVL=", 6) != 0)
		i++;
	shlvl = ft_atoi(envp[i] + 6);
	return (shlvl);
}

char	**split_path(char **envp)
{
	int		i;
	char	**splitted_path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	splitted_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (splitted_path[i])
	{
		splitted_path[i] = join_and_free(splitted_path[i], "/");
		i++;
	}
	return (splitted_path);
}
