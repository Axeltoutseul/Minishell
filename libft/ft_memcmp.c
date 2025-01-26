/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:13:07 by axbaudri          #+#    #+#             */
/*   Updated: 2023/11/07 11:13:09 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	size_t			i;
	unsigned char	*chaine1;
	unsigned char	*chaine2;

	i = 0;
	chaine1 = (unsigned char *)s1;
	chaine2 = (unsigned char *)s2;
	while (i < size)
	{
		if (chaine1[i] != chaine2[i])
			return (chaine1[i] - chaine2[i]);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	//char s[] = {-128, 0, 127, 0};
	//char sCpy[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};

	printf("%d\n", ft_memcmp(s2, s3, 3));
	return (0);
}*/
