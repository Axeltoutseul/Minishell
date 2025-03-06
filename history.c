/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:44:05 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/06 16:36:14 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_history(t_shell *shell, const char *line)
{
	t_list	*new_node;

	new_node = ft_lstnew(ft_strdup(line));
	if (new_node == NULL)
		return ;
	ft_lstadd_back(&shell->history, new_node);
	add_history(line);
}

void	display_history(t_shell *shell)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = shell->history;
	while (temp)
	{
		ft_printf("%d  %s\n", i + 1, (char *)temp->content);
		i = i + 1;
		temp = temp->next;
	}
}

void	verif_history(t_shell *shell, const char *input)
{
	if (input[0] != '\0')
		update_history(shell, input);
	if (ft_strcmp(input, "history") == 0)
		display_history(shell);
}
