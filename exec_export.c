/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:44:58 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/27 16:05:24 by axbaudri         ###   ########.fr       */
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

void	add_to_env_and_export(t_env *new, t_env *temp, t_shell *shell)
{
	add_env_line(&shell->env_lines, new);
	add_env_line(&shell->export_lines, temp);
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
		if (!valid_arg(new->name, prompt->strs[i]))
		{
			check_error(new->name, prompt->strs[i]);
			break ;
		}
		else if (!is_in_list(shell->export_lines, new->name))
			add_to_env_and_export(new, temp, shell);
		else if (ft_strchr(prompt->strs[i], '='))
		{
			update_line(prompt->strs[i], &shell->env_lines);
			update_line(prompt->strs[i], &shell->export_lines);
		}
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

void	update_line(char *arg, t_env **env)
{
	t_env	*temp;
	int		i;
	char	*var_name;

	temp = *env;
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	var_name = ft_strndup(arg, i);
	while (temp)
	{
		if (ft_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			if (arg[i + 1] == '\'')
				temp->value = ft_strtrim(ft_strchr(arg, '=') + 1, "'");
			else
				temp->value = ft_strtrim(ft_strchr(arg, '=') + 1, "\"");
		}
		temp = temp->next;
	}
}
