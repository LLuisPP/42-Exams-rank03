/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:59:09 by lprieto-          #+#    #+#             */
/*   Updated: 2024/07/27 16:54:55 by lprieto-         ###   ########.fr       */
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

int	ft_printf(const char *fmt, ... )
{
	int len = 0;

	va_list	ptr;
	va_start(ptr, fmt);

	while (*fmt)
	{
		if ((*fmt == '%') && ((*(fmt + 1) == 's') || (*(fmt + 1) == 'd') || (*(fmt + 1) == 'x')))
		{
			fmt++;
			if (*fmt == 's')
				put_str(va_arg(ptr, char *), &len);
			else if (*fmt == 'd')
				put_digit((long long int)va_arg(ptr, int), 10, &len);
			else if (*fmt == 'x')
				put_digit((long long int)va_arg(ptr, unsigned int), 16, &len);
		}
		else
			len += write(1, fmt, 1);
		fmt++;
	}
	return (va_end(ptr), len);
}

