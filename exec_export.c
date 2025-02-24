/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:44:58 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/24 19:03:35 by axbaudri         ###   ########.fr       */
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
	t_env	*new;
	t_env	*temp;
	int		i;

	i = 1;
	while (i < count_strings(prompt->strs))
	{
		new = new_line(prompt->strs[i]);
		temp = new_line(prompt->strs[i]);
		add_env_line(&shell->env_lines, new);
		add_env_line(&shell->export_lines, temp);
		i++;
	}
}

int	is_in_list(t_env *env, char *var_name)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(var_name, temp->name) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}
