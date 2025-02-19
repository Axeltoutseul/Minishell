/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:39:27 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/19 18:04:16 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_shell *shell, t_prompt *prompt)
{
	int	i;

	i = 1;
	while (prompt->strs[i])
	{
		find_env_line(shell, prompt->strs[i], &shell->env_lines);
		find_env_line(shell, prompt->strs[i], &shell->export_lines);
		i++;
	}
}

void	find_env_line(t_shell *shell, char *var, t_list **lst)
{
	int		size;
	t_list	*name;
	t_list	*temp;

	temp = *lst;
	name = shell->vars;
	while (name && ft_strcmp(name->content, var) != 0)
		name = name->next;
	if (name && ft_strcmp(name->content, "_") != 0)
	{
		size = ft_strlen(name->content);
		while (temp && ft_strncmp(name->content, temp->content, size) != 0)
			temp = temp->next;
		if (temp)
			remove_line(lst, temp->content);
	}
}

void	remove_line(t_list **lst, char *line)
{
	t_list	*next_one;
	t_list	*temp;

	temp = *lst;
	if (ft_strcmp(temp->content, line) == 0)
	{
		*lst = temp->next;
		free(temp->content);
		free(temp);
		return ;
	}
	while (temp)
	{
		if (temp->next && ft_strcmp(temp->next->content, line) == 0)
		{
			next_one = temp->next;
			temp->next = temp->next->next;
			free(next_one->content);
			free(next_one);
			return ;
		}
		temp = temp->next;
	}
}
