/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:14:13 by axbaudri          #+#    #+#             */
/*   Updated: 2023/11/13 14:14:15 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int to_find, size_t size)
{
	size_t	i;
	char	*new_string;

	i = 0;
	new_string = (char *) str;
	while (i < size)
	{
		if (to_find > 127 || to_find < -127)
			to_find %= 128;
		if (new_string[i] == (char)to_find)
			return (new_string + i);
		else
			i++;
	}
	return (0);
}

/*int	main(void)
{
	const char str[] = {0, 1, 2, 3, 4, 5};
	char *result = ft_memchr(str, 2, 3);
	printf("%s", result);
	return (0);
}*/
