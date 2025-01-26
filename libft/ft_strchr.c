/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:10:21 by axbaudri          #+#    #+#             */
/*   Updated: 2024/05/14 15:27:46 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int to_find)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == to_find)
			return ((char *)str + i);
		i++;
	}
	if (to_find == 0)
		return ((char *)str + i);
	return (0);
}

/*int	main(void)
{
	printf("%s\n", strchr("Voici une string", 't' + 128));
	return (0);
}*/
