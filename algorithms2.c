/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:21:30 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/13 12:02:48 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	bs_helper(t_helper helper, t_fract *bs)
{
	int	color;

	bs->ca = ((double)helper.x / bs->width) * (bs->zoom * 2) - bs->zoom
		+ bs->offsetx;
	bs->cb = ((double)helper.y / bs->height) * (bs->zoom * 2) - bs->zoom
		+ bs->offsety;
	helper.a = 0;
	helper.b = 0;
	helper.n = 0;
	while (helper.n < MAX_ITERATIONS)
	{
		helper.aa = helper.a * helper.a - helper.b * helper.b;
		helper.bb = 2 * fabs(helper.a * helper.b);
		helper.a = helper.aa + bs->ca;
		helper.b = helper.bb + bs->cb;
		if (helper.a * helper.a + helper.b * helper.b > LIMIT)
			break ;
		helper.n++;
	}
	if (helper.n == MAX_ITERATIONS)
		color = 0;
	else
		color = (helper.n * 255) / MAX_ITERATIONS;
	mlx_put_pixel(bs->img, helper.x, helper.y, get_vibrant_rgba(color));
}

void	burning_ship(void *param)
{
	t_helper	helper;
	t_fract		*bs;

	bs = (t_fract *)param;
	helper.y = 0;
	while (helper.y < bs->height)
	{
		helper.x = 0;
		while (helper.x < bs->width)
		{
			bs_helper(helper, bs);
			helper.x++;
		}
		helper.y++;
	}
	mlx_image_to_window(bs->mlx, bs->img, 0, 0);
}
