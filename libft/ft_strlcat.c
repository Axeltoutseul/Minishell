/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:02:28 by axbaudri          #+#    #+#             */
/*   Updated: 2023/11/07 12:02:31 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen((char *)src);
	if (size > dest_len)
	{
		while (src[i] && i < size - (dest_len + 1))
		{
			dest[dest_len + i] = ((char *)src)[i];
			i++;
		}
		dest[dest_len + i] = '\0';
		return (dest_len + src_len);
	}
	else
		return (size + src_len);
}

/*int	main(void)
{
	char dest[20] = "erfersgerg";
	char src[20] = "qwPDKQPDKE";
	printf("%ld\n", ft_strlcat(dest, src, 20));
	printf("%s", dest);
	return (0);
}*/
