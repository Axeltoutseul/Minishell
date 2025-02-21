/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:10:48 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/21 15:15:19 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_env(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		ft_printf("%s\n", (char *)temp->content);
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

char	*copy_line_with_quotes(char *src)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 3));
	if (!dest)
		return (NULL);
	while (src[i] && src[i] != '=')
		dest[j++] = src[i++];
	if (src[i] == '=')
		dest[j++] = src[i++];
	dest[j++] = '"';
	while (src[i])
		dest[j++] = src[i++];
	dest[j++] = '"';
	dest[j] = 0;
	return (dest);
}
