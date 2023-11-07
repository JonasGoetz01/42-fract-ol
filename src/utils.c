/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:19:31 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/07 22:51:38 by jgotz            ###   ########.fr       */
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

double strtodo(const char* str)
{
	while (isspace(*str))
	{
		str++;
	}
	int sign = 1;
	if (*str == '-' || *str == '+')
	{
		sign = (*str++ == '-') ? -1 : 1;
	}
	double result = 0.0;
	while (isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		double fraction = 1.0;
		while (isdigit(*str))
		{
			fraction /= 10.0;
			result += (*str - '0') * fraction;
			str++;
		}
	}
	if (*str == 'e' || *str == 'E')
	{
		str++;
		int exponentSign = 1;
		if (*str == '-' || *str == '+')
		{
			exponentSign = (*str++ == '-') ? -1 : 1;
		}

		int exponent = 0;
		while (isdigit(*str))
		{
			exponent = exponent * 10 + (*str - '0');
			str++;
		}
		while (exponent-- > 0)
		{
			result = (exponentSign == 1) ? result * 10.0 : result / 10.0;
		}
	}
	return sign * result;
}