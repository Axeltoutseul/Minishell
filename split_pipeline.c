/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:11:01 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/21 16:39:11 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_pipeline(const char *line)//a modifie 
{
	int		i;
	int		start;
	int		count;
	char	**segments;//6variable au lieu de 5 limit
	int		in_single;
	int		in_double;

	i = 0;
	start = 0;
	count = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (line[i] == '|' && !in_single && !in_double)
			count++;
		i++;
	}
	//je pense pouvoir separer la fonction en deux a partir de cette endroit avec segment qui n'est pas encore utilise  ce moment la 
	segments = malloc(sizeof(char *) * (count + 2));
	if (!segments)
		return (NULL);
	i = 0;
	start = 0;
	count = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (line[i] == '|' && !in_single && !in_double)
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
