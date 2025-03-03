/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:44:05 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/03 18:23:31 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_history(void)
{
	HIST_ENTRY	**history_list;
	int			i;

	history_list = history_get_history_state()->entries;
	i = 0;
	if (history_list)
	{
		while (history_list[i])
		{
			ft_printf("%d  %s\n", i + 1, history_list[i]->line);
			i++;
		}
	}
}

void	verif_history(const char *input)
{
	if (input[0] != '\0')
		add_history(input);
	if (strcmp(input, "history") == 0)
		display_history();
}
