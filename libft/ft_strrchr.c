/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:12:45 by axbaudri          #+#    #+#             */
/*   Updated: 2024/09/30 16:51:46 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int to_find)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)to_find)
			return ((char *)str + i);
		i--;
	}
	return (0);
}

/*int	main(void)
{
	printf("%s", ft_strrchr("tripouille", 't' + 256));
	return (0);
}*/
