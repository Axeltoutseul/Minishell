/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:39:27 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/06 15:46:14 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_shell *shell, t_prompt *prompt)
{
	int	i;

	i = 1;
	if (prompt->nb_args == 1)
		ft_printf("unset: not enough arguments\n");
	else
	{
		while (prompt->strs[i])
		{
			if (!valid_name(prompt->strs[i]))
			{
				ft_printf("unset: %s: invalid parameter name\n",
					prompt->strs[i]);
				break ;
			}
			if (ft_strcmp(prompt->strs[i], "_") != 0)
			{
				remove_line(&shell->env_lines, prompt->strs[i]);
				remove_line(&shell->export_lines, prompt->strs[i]);
			}
			i++;
		}
	}
}

void	remove_line(t_env **lst, char *arg)
{
	t_env	*next_one;
	t_env	*temp;

	temp = *lst;
	if (ft_strcmp(temp->name, arg) == 0)
	{
		*lst = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		return ;
	}
	while (temp)
	{
		if (temp->next && ft_strcmp(temp->next->name, arg) == 0)
		{
			next_one = temp->next;
			temp->next = temp->next->next;
			free(next_one->name);
			free(next_one->value);
			free(next_one);
			return ;
		}
		temp = temp->next;
	}
}
