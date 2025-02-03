/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:43:09 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/03 16:40:12 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*save_text(int fd)
{
	char	*temp;
	char	*content;

	temp = " ";
	while (temp)
	{
		temp = get_next_line(fd);
		if (temp)
			content = join_and_free(content, temp);
		free(temp);
	}
	return (content);
}

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
		if (ft_strncmp(envp[i], "_=", 2) == 0)
			lines[i] = ft_strdup("_=/usr/bin/env");
		else
			lines[i] = ft_strdup(envp[i]);
		i++;
	}
	lines[i] = NULL;
	return (lines);
}

int	count_words(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[0] != 0 && str[0] != 32)
	{
		i++;
		count++;
	}
	while (str[i])
	{
		if (str[i] == 32 && (str[i + 1] != 0 && str[i + 1] != 32))
			count++;
		i++;
	}
	return (count);
}
