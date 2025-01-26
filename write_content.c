/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:10:48 by axbaudri          #+#    #+#             */
/*   Updated: 2024/12/13 18:18:48 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		ft_printf("%s\n", envp[i++]);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
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
	new_string[total_size] = 0;
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
	return (new_string);
}
