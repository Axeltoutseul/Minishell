/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:39:27 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/30 13:56:58 by axbaudri         ###   ########.fr       */
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
		free_2d_array(shell->env);
		shell->env = get_env_lines(shell->env_lines);
	}
}

void	del_content(t_env *temp)
{
	free(temp->name);
	free(temp->value);
	free(temp->line);
	free(temp);
}

void	remove_line(t_env **lst, char *arg)
{
	t_env	*next_one;
	t_env	*temp;

	temp = *lst;
	if (ft_strcmp(temp->name, arg) == 0)
	{
		*lst = temp->next;
		del_content(temp);
		return ;
	}
	while (temp)
	{
		if (temp->next && ft_strcmp(temp->next->name, arg) == 0)
		{
			next_one = temp->next;
			temp->next = temp->next->next;
			del_content(next_one);
			return ;
		}
		temp = temp->next;
	}
}
