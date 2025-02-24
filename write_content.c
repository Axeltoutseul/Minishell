/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:10:48 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/24 18:49:04 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->value)
			ft_printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void	write_export(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->value)
			ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		else
			ft_printf("declare -x %s=\"\"\n", temp->name);
		temp = temp->next;
	}
}

int	calculate_total_size(int size, char **strs, char *sep)
{
	int	i;
	int	total_size;

	i = 0;
	total_size = 0;
	while (i < size)
	{
		total_size += ft_strlen(strs[i]);
		if (i < size - 1)
			total_size += ft_strlen(sep);
		i++;
	}
	return (total_size);
}

char	*ft_strjoin2(int size, char **strs, char *sep)
{
	int		i;
	int		j;
	int		total_size;
	char	*new_string;

	i = 0;
	j = 0;
	total_size = calculate_total_size(size, strs, sep);
	new_string = (char *)malloc(sizeof(char) * total_size + 1);
	if (!new_string)
		return (NULL);
	while (i < size)
	{
		ft_strcpy(new_string + j, strs[i]);
		j += ft_strlen(strs[i]);
		if (i < size - 1)
		{
			ft_strcpy(new_string + j, sep);
			j += ft_strlen(sep);
		}
		i++;
	}
	new_string[total_size] = 0;
	return (new_string);
}
