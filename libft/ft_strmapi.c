/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:27:04 by axbaudri          #+#    #+#             */
/*   Updated: 2023/11/16 19:27:06 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	size;
	char			*new_string;

	i = 0;
	size = ft_strlen(s);
	new_string = (char *)malloc(sizeof(char) * (size + 1));
	if (new_string == NULL)
		return (NULL);
	while (i < size)
	{
		new_string[i] = f(i, s[i]);
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

/*static char	my_function(unsigned int i, char c)
{
	(void) i;
	return (c);
}

int main(void)
{
	char *str = "Welcome to 42 school";
	char *new_string = ft_strmapi(str, &my_function);
	printf("%s", new_string);
	return (0);
}*/
