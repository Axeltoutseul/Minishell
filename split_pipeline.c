/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:11:01 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/25 05:20:02 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_pipeline(const char *line)
{
	int		i;
	int		start;
	int		count;
	char	**segments;
	int		state;

	i = 0;
	start = 0;
	count = 0;
	state = 0;
	while (line[i])
	{
		if (line[i] == '\'' && state != 2)
		{
			if (state == 1)
				state = 0;
			else
				state = 1;
		}
		else if (line[i] == '\"' && state != 1)
		{
			if (state == 2)
				state = 0;
			else
				state = 2;
		}
		else if (line[i] == '|' && state == 0)
			count++;
		i++;
	}
	segments = malloc(sizeof(char *) * (count + 2));
	if (!segments)
		return (NULL);
	i = 0;
	start = 0;
	count = 0;
	state = 0;
	while (line[i])
	{
		if (line[i] == '\'' && state != 2)
		{
			if (state == 1)
				state = 0;
			else
				state = 1;
		}
		else if (line[i] == '\"' && state != 1)
		{
			if (state == 2)
				state = 0;
			else
				state = 2;
		}
		else if (line[i] == '|' && state == 0)
		{
			segments[count++] = ft_strndup(line + start, i - start);
			start = i + 1;
		}
		i++;
	}
	segments[count] = ft_strdup(line + start);
	segments[count + 1] = NULL;
	return (segments);
}
