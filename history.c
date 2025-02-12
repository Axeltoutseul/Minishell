/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:44:05 by qacjl             #+#    #+#             */
/*   Updated: 2025/02/12 15:56:22 by axbaudri         ###   ########.fr       */
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
			ft_printf("%d  %s\n", i + 1, history_list[i]->line); //history ne commence pas a 0
			i++;
		}
	}
}

void	verif_history(char *input)
{
	if (strcmp(input, "history") == 0)
	{
		display_history();
	}
	else
	{
		ft_printf("Exécution de la commande : %s\n", input);
	}
}

//ajout dans le main apres if (!input)
/*int main(void)
{
	char	*input;

	read_history("history.txt");
	using_history();
	if (*input)
	{
		add_history(input);
		verif_history(input);
	}
	write_history("history.txt");
	return (0);
}*/
