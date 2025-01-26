/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:18:54 by axbaudri          #+#    #+#             */
/*   Updated: 2024/01/12 14:58:51 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_args(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		count += ft_write_address(va_arg(args, void *));
	else if (c == 'd')
		count += ft_putnbr(va_arg(args, int));
	else if (c == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		count += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		count += ft_putnbr_base_lower(va_arg(args, int), 16);
	else if (c == 'X')
		count += ft_putnbr_base_upper(va_arg(args, int), 16);
	else if (c == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, str);
	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += write_args(str[i], args);
		}
		else
		{
			ft_putchar(str[i]);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

/*#define S2 "Mussum Ipsum, cacilds vidis litro abertis. \
Posuere libero varius. Nullam a nisl ut ante blandit hendrerit. \
Aenean sit amet nisi. Atirei o pau no gatis, per gatis num morreus."
#define TEST "%p", &s2

int	main(void)
{
	printf(" %d \n", printf("i"));
	printf(" %d \n", ft_printf("i"));
	return (0);
}*/
