/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:59:09 by lprieto-          #+#    #+#             */
/*   Updated: 2024/07/27 16:07:20 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	put_str(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(1, str, 1);
		*len += 1;
		str++;
	}
}

void	put_digit(long long int nbr, int base, int *len)
{
	char	*hex = "0123456789abcdef";

	if (nbr < 0)
	{
		nbr = -nbr;
		*len += 1;
		write(1, "-", 1);
	}
	if (nbr >= base)
		put_digit((nbr / base), base, len);
	*len += 1;
	write(1, &hex[nbr % base], 1);
}

int	ft_printf(const char *format, ... )
{
	int length = 0;

	va_list	pointer;
	va_start(pointer, format);

	while (*format)
	{
		if ((*format == '%') && ((*(format + 1) == 's') || (*(format + 1) == 'd') || (*(format + 1) == 'x')))
		{
			format++;
			if (*format == 's')
				put_str(va_arg(pointer, char *), &length);
			else if (*format == 'd')
				put_digit((long long int)va_arg(pointer, int), 10, &length);
			else if (*format == 'x')
				put_digit((long long int)va_arg(pointer, unsigned int), 16, &length);
		}
		else
			length += write(1, format, 1);
		format++;
	}
	return (va_end(pointer), length);
}
