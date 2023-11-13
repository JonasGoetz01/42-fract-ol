/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:19:31 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/13 11:32:07 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_vibrant_rgba(int gradient_value)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (gradient_value * 2) % 256;
	green = (gradient_value * 3) % 256;
	blue = (gradient_value * 4) % 256;
	red = red / 2;
	green = green / 2;
	blue = blue / 2;
	alpha = 255;
	return (get_rgba(red, green, blue, alpha));
}
