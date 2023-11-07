/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:30:37 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/07 06:23:38 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(void *param)
{
	int			color;
	t_helper	helper;
	t_fract		*mbt;

	mbt = (t_fract *)param;
	helper.x = 0;
	helper.y = 0;
	while (helper.y < mbt->height)
	{
		helper.x = 0;
		while (helper.x < mbt->width)
		{
			helper.a = map(helper.x, 0, mbt->width, -(mbt->zoom), mbt->zoom);
			helper.b = map(helper.y, 0, mbt->height, -(mbt->zoom), mbt->zoom);
			helper.ca = helper.a;
			helper.cb = helper.b;
			helper.n = 0;
			while (helper.n < MAX_ITERATIONS)
			{
				helper.aa = helper.a * helper.a - helper.b * helper.b;
				helper.bb = 2 * helper.a * helper.b;
				helper.a = helper.aa + helper.ca;
				helper.b = helper.bb + helper.cb;
				if (helper.a * helper.a + helper.b * helper.b > LIMIT)
					break ;
				helper.n++;
			}
			color = map(helper.n, 0, MAX_ITERATIONS, 0, 1);
			color = map(sqrt(color), 0, 1, 0, 255);
			mlx_put_pixel(mbt->img, helper.x, helper.y, get_rgba(color, color,
					color, 255));
			helper.x++;
		}
		helper.y++;
	}
	mlx_image_to_window(mbt->mlx, mbt->img, 0, 0);
}

void	julia(void *param)
{
	int			color;
	t_helper	helper;
	t_fract		*jlt;
	double		smooth_color;

	jlt = (t_fract *)param;
	jlt->ca = -0.8;
	jlt->cb = 0.156;
	helper.y = 0;
	while (helper.y < jlt->height)
	{
		helper.x = 0;
		while (helper.x < jlt->width)
		{
			helper.a = map(helper.x, 0, jlt->width, -(jlt->zoom), jlt->zoom);
			helper.b = map(helper.y, 0, jlt->height, -(jlt->zoom), jlt->zoom);
			helper.n = 0;
			while (helper.n < MAX_ITERATIONS)
			{
				helper.aa = helper.a * helper.a - helper.b * helper.b;
				helper.bb = 2 * helper.a * helper.b;
				helper.a = helper.aa + jlt->ca;
				helper.b = helper.bb + jlt->cb;
				if (helper.a * helper.a + helper.b * helper.b > LIMIT)
					break ;
				helper.n++;
			}
			smooth_color = helper.n + 1 - log(log(sqrt(helper.a * helper.a
							+ helper.b * helper.b))) / log(2.0);
			color = map(smooth_color, 0, MAX_ITERATIONS, 0, 255);
			mlx_put_pixel(jlt->img, helper.x, helper.y, get_rgba(color, color,
					color, 255));
			helper.x++;
		}
		helper.y++;
	}
	mlx_image_to_window(jlt->mlx, jlt->img, 0, 0);
}
