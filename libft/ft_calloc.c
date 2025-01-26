/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:39:13 by axbaudri          #+#    #+#             */
/*   Updated: 2024/05/14 15:28:20 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	void			*new_var;
	unsigned char	*chaine;

	if (size && (count > SIZE_MAX / size))
		return (NULL);
	new_var = (void *)malloc(count * size);
	if (new_var == NULL)
		return (NULL);
	chaine = (unsigned char *)new_var;
	i = 0;
	while (i < count)
		chaine[i++] = '\0';
	return (new_var);
}

/*static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	main(void)
{
	char *str = "Bonjour tout le monde";
	char *new_string = (char *)ft_calloc((size_t)ft_strlen(str), sizeof(char));
	ft_strcpy(new_string, str);
	printf("%s", new_string);
	return (0);
}*/
