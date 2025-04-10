/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:44:58 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/30 15:56:10 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export(t_shell *shell, t_prompt *prompt)
{
	if (count_words(prompt->cmd_line) == 1)
		write_export(shell->export_lines);
	else
		add_lines(shell, prompt);
	free_2d_array(shell->env);
	shell->env = get_env_lines(shell->env_lines);
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
			free_new_and_temp(new, temp);
			break ;
		}
		else if (!is_in_list(shell->export_lines, new->name))
			add_to_env_and_export(new, temp, shell);
		else if (ft_strchr(prompt->strs[i], '='))
		{
			update_line(prompt->strs[i], &shell->env_lines);
			update_line(prompt->strs[i], &shell->export_lines);
			free_new_and_temp(new, temp);
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
	char	*value;

	temp = *env;
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	var_name = ft_strndup(arg, i);
	value = ft_strdup(ft_strchr(arg, '=') + 1);
	while (temp)
	{
		if (ft_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			free(temp->line);
			temp->value = value;
			temp->line = ft_strjoin(temp->name, "=");
			temp->line = join_and_free(temp->line, temp->value);
		}
		temp = temp->next;
	}
	free(var_name);
}
