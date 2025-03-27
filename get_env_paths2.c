/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_paths2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:22:47 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/27 11:21:14 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **env, char *key)
{
	int		i;
	int		key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			return (env[i] + key_len);
		}
		i = i + 1;
	}
	return (0);
}

char	*search_cmd_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	full_path = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], cmd);
		if (access(temp, F_OK | X_OK) == 0)
		{
			full_path = temp;
			return (full_path);
		}
		free(temp);
		i = i + 1;
	}
	return (0);
}
