/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:11:01 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/27 11:34:54 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quote_state(int *state, char c)
{
	if (c == '\'' && *state != 2)
	{
		if (*state == 1)
			*state = 0;
		else
			*state = 1;
	}
	else if (c == '\"' && *state != 1)
	{
		if (*state == 2)
			*state = 0;
		else
			*state = 2;
	}
}

int	count_segments(const char *line)
{
	int	i;
	int	state;
	int	count;

	i = 0;
	state = 0;
	count = 0;
	while (line[i])
	{
		update_quote_state(&state, line[i]);
		if (line[i] == '|' && state == 0)
			count++;
		i = i + 1;
	}
	return (count);
}

void	fill_segments(const char *line, char **segments)
{
	int	i;
	int	start;
	int	state;
	int	seg_index;

	i = 0;
	start = 0;
	state = 0;
	seg_index = 0;
	while (line[i])
	{
		update_quote_state(&state, line[i]);
		if (line[i] == '|' && state == 0)
		{
			segments[seg_index] = ft_strndup(line + start, i - start);
			seg_index = seg_index + 1;
			start = i + 1;
		}
		i = i + 1;
	}
	segments[seg_index] = ft_strdup(line + start);
	segments[seg_index + 1] = NULL;
}

char	**split_pipeline(const char *line)
{
	int		count;
	char	**segments;

	count = count_segments(line);
	segments = malloc(sizeof(char *) * (count + 2));
	if (segments == NULL)
		return (NULL);
	fill_segments(line, segments);
	return (segments);
}
