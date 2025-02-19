/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:44 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/19 18:06:56 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(char *cmd_line)
{
	int	i;
	int	s_quote_count;
	int	d_quote_count;

	i = 0;
	s_quote_count = count_occurrences(cmd_line, '\'');
	d_quote_count = count_occurrences(cmd_line, '"');
	if (s_quote_count % 2 == 1 || d_quote_count % 2 == 1)
		return (0);
	while (cmd_line[i])
	{
		
	}
	return (1);
}
