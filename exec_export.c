/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:44:58 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/21 17:10:16 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export(t_shell *shell, t_prompt *prompt)
{
	if (count_words(prompt->cmd_line) == 1)
		write_export(shell->export_lines);
	else
		add_lines(shell, prompt);
}

void	add_lines(t_shell *shell, t_prompt *prompt)
{
	t_list	*new;
	int		i;

	i = 1;
	while (i < count_strings(prompt->strs))
	{
		new = ft_lstnew(ft_strdup(prompt->strs[i++]));
		ft_lstadd_back(&shell->export_lines, new);
	}
}
