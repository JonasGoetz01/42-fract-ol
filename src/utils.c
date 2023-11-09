/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:19:31 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/09 16:17:58 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

double	map(double value, double start1, double stop1, double start2,
		double stop2)
{
	return (start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1)));
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	isspaceown(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	isdigitown(char c)
{
	return (c >= '0' && c <= '9');
}

double	strtodo(const char *str)
{
	int		sign;
	double	result;
	double	fraction;
	int		exponentSign;
	int		exponent;

	while (isspaceown(*str))
	{
		str++;
	}
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		sign = (*str++ == '-') ? -1 : 1;
	}
	result = 0.0;
	while (isdigitown(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		fraction = 1.0;
		while (isdigitown(*str))
		{
			fraction /= 10.0;
			result += (*str - '0') * fraction;
			str++;
		}
	}
	if (*str == 'e' || *str == 'E')
	{
		str++;
		exponentSign = 1;
		if (*str == '-' || *str == '+')
		{
			exponentSign = (*str++ == '-') ? -1 : 1;
		}
		exponent = 0;
		while (isdigitown(*str))
		{
			exponent = exponent * 10 + (*str - '0');
			str++;
		}
		while (exponent-- > 0)
		{
			result = (exponentSign == 1) ? result * 10.0 : result / 10.0;
		}
	}
	return (sign * result);
}
