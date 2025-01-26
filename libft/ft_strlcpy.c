/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:05:04 by axbaudri          #+#    #+#             */
/*   Updated: 2023/11/07 12:05:06 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = (size_t)ft_strlen(src);
	if (size <= 0)
		dest = "\0";
	else if (size == 1)
		dest[0] = '\0';
	else
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (length);
}

/*int	main(void)
{
	char dest[11] = "coucou";
	char src[11] = "p";
	printf("%ld\n", ft_strlcpy(dest, src, 0));
	printf("%s", dest);
	return (0);
}*/
