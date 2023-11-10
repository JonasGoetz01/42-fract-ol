/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sttodo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:36:18 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/10 10:48:44 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	isdigitown(char c)
{
	return (c >= '0' && c <= '9');
}

int	isspaceown(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v');
}

double	parse_fraction(const char **str)
{
	double	fraction;

	fraction = 1.0;
	while (isdigitown(**str))
	{
		fraction /= 10.0;
		fraction += (**str - '0') * fraction;
		(*str)++;
	}
	return (fraction);
}

double	strtodo(const char *str)
{
	int		sign;
	double	result;

	while (isspaceown(*str))
		str++;
	if (*str == '-')
		sign = -1;
	else
		sign = 1;
	if (*str == '-' || *str == '+')
		str++;
	result = 0.0;
	while (isdigitown(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		result += parse_fraction(&str);
	}
	return (sign * result);
}
