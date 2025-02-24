/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:44:58 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/24 11:57:04 by axbaudri         ###   ########.fr       */
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
	t_list	*temp;
	int		i;
	int		j;

	i = 1;
	while (i < count_strings(prompt->strs))
	{
		j = 0;
		while (prompt->strs[i][j] && prompt->strs[i][j] != '=')
			j++;
		new = ft_lstnew(ft_strdup(prompt->strs[i]));
		temp = ft_lstnew(ft_strndup(prompt->strs[i], j));
		ft_lstadd_back(&shell->export_lines, new);
		ft_lstadd_back(&shell->vars, temp);
		if (ft_strchr(prompt->strs[i], '='))
			ft_lstadd_back(&shell->env_lines, new);
		i++;
	}
}

int	is_in_list(t_list *vars, char *var_name)
{
	t_list	*temp;

	temp = vars;
	while (temp)
	{
		if (ft_strcmp(var_name, temp->content) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}
