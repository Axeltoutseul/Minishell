/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:13:59 by axbaudri          #+#    #+#             */
/*   Updated: 2023/11/13 14:14:01 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t	i;

	i = 0;
	if (dest <= src)
	{
		while (i < size)
		{
			((char *) dest)[i] = ((char *) src)[i];
			i++;
		}
	}
	else
	{
		dest += size;
		src += size;
		while (size > 0)
		{
			*(char *)--dest = *(char *)--src;
			size--;
		}
	}
	return (dest);
}

/*int	main(void)
{
	const char src[] = "Aticleworld";
	char dest[] = "Amlendra";

	memmove(dest, src, 9);
	printf("%s", dest);
	return (0);
}*/
