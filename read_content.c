/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:43:09 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/30 14:10:42 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strings(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

char	**get_lines(char **envp)
{
	int		i;
	int		size;
	char	**lines;

	i = 0;
	size = count_strings(envp);
	lines = (char **)malloc(sizeof(char *) * (size + 1));
	if (!lines)
		return (NULL);
	while (i < size)
	{
		lines[i] = ft_strdup(envp[i]);
		i++;
	}
	lines[i] = NULL;
	return (lines);
}

char	**get_env_lines(t_env *env)
{
	t_env	*temp;
	int		i;
	char	**new_lines;

	i = 0;
	new_lines = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	if (!new_lines || !env)
		return (NULL);
	temp = env;
	while (temp)
	{
		new_lines[i] = ft_strdup(temp->line);
		temp = temp->next;
		i++;
	}
	new_lines[i] = 0;
	return (new_lines);
}
