/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_tokeniser3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:42:20 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/27 12:42:44 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection(const char *line, int *i, int *j, char *new_line)
{
	if (*i > 0 && line[*i - 1] != ' ')
		new_line[(*j)++] = ' ';
	new_line[(*j)++] = line[*i];
	if (line[*i + 1] && line[*i + 1] == line[*i])
	{
		*i = *i + 1;
		new_line[(*j)++] = line[*i];
	}
	if (line[*i + 1] && line[*i + 1] != ' ')
		new_line[(*j)++] = ' ';
}
