/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:14:33 by axbaudri          #+#    #+#             */
/*   Updated: 2023/11/13 14:14:35 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int value, size_t n)
{
	size_t	i;
	char	*chaine;

	i = 0;
	chaine = src;
	while (i < n)
	{
		chaine[i] = (char) value;
		i++;
	}
	return ((char *) chaine);
}

/*int	main(void)
{
	char src[20] = "Ceci est une string";

	memset(src, 0, 1);
	printf("%s", src);
	return (0);
}*/
