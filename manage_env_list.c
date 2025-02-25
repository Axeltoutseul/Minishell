/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:16:06 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/25 18:33:13 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_line(char *env_line)
{
	t_env	*new_node;
	int		i;
	int		size;

	new_node = (t_env *)malloc(sizeof(t_env));
	i = 0;
	if (!new_node)
		return (NULL);
	while (env_line[i] && env_line[i] != '=')
		i++;
	new_node->name = ft_strndup(env_line, i);
	if (ft_strchr(env_line, '='))
	{
		size = ft_strlen(ft_strchr(env_line, '=') + 1);
		if (env_line[i + 1] == '\'')
			new_node->value = ft_strtrim(ft_strchr(env_line, '=') + 1, "'");
		else
			new_node->value = ft_strtrim(ft_strchr(env_line, '=') + 1, "\"");
	}
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

void	add_env_line(t_env **env, t_env *new)
{
	t_env	*temp;

	temp = *env;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	free_env_lines(t_env *env)
{
	t_env	*temp;
	t_env	*next;

	if (!env)
		return ;
	temp = env;
	while (temp)
	{
		next = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = next;
	}
}
