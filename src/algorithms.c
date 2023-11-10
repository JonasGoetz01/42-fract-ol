/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:30:37 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/10 13:39:10 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	mandelbrot_routine(t_fract *mbt, t_helper *helper)
{
	helper->a = ((double)helper->x / mbt->width) * (mbt->zoom * 2) - mbt->zoom
		+ mbt->offsetx;
	helper->b = ((double)helper->y / mbt->height) * (mbt->zoom * 2) - mbt->zoom
		+ mbt->offsety;
	helper->ca = helper->a;
	helper->cb = helper->b;
	helper->n = 0;
	while (helper->n < MAX_ITERATIONS)
	{
		helper->aa = helper->a * helper->a - helper->b * helper->b;
		helper->bb = 2 * helper->a * helper->b;
		helper->a = helper->aa + helper->ca;
		helper->b = helper->bb + helper->cb;
		if (helper->a * helper->a + helper->b * helper->b > LIMIT)
			break ;
		helper->n++;
	}
}

void	mandelbrot(void *param)
{
	int			color;
	t_helper	helper;
	t_fract		*mbt;

	mbt = (t_fract *)param;
	helper.y = 0;
	while (helper.y < mbt->height)
	{
		helper.x = 0;
		while (helper.x < mbt->width)
		{
			mandelbrot_routine(mbt, &helper);
			if (helper.n == MAX_ITERATIONS)
				color = 0;
			else
				color = (helper.n * 255) / MAX_ITERATIONS;
			mlx_put_pixel(mbt->img, helper.x, helper.y, get_rgba(color, color,
					color, 255));
			helper.x++;
		}
		helper.y++;
	}
	mlx_image_to_window(mbt->mlx, mbt->img, 0, 0);
}

void	calc_color(int *color, double *smooth_color, t_helper *helper,
		t_fract *jlt)
{
	*smooth_color = helper->n + 1 - log(log(sqrt(helper->a * helper->a
					+ helper->b * helper->b))) / log(2.0);
	*color = (int)(*smooth_color / MAX_ITERATIONS * 255);
	mlx_put_pixel(jlt->img, helper->x, helper->y, get_rgba(*color, *color,
			*color, 255));
}

void	julia_routine(t_fract *jlt, t_helper *helper)
{
	int		color;
	double	smooth_color;

	helper->x = 0;
	while (helper->x < jlt->width)
	{
		helper->a = ((double)helper->x / jlt->width) * (jlt->zoom * 2)
			- jlt->zoom + jlt->offsetx;
		helper->b = ((double)helper->y / jlt->height) * (jlt->zoom * 2)
			- jlt->zoom + jlt->offsety;
		helper->n = 0;
		while (helper->n < MAX_ITERATIONS)
		{
			helper->aa = helper->a * helper->a - helper->b * helper->b;
			helper->bb = 2 * helper->a * helper->b;
			helper->a = helper->aa + jlt->ca;
			helper->b = helper->bb + jlt->cb;
			if (helper->a * helper->a + helper->b * helper->b > LIMIT)
				break ;
			helper->n++;
		}
		calc_color(&color, &smooth_color, helper, jlt);
		helper->x++;
	}
}

void	julia(void *param)
{
	t_helper	helper;
	t_fract		*jlt;

	jlt = (t_fract *)param;
	helper.y = 0;
	while (helper.y < jlt->height)
	{
		julia_routine(jlt, &helper);
		helper.y++;
	}
	mlx_image_to_window(jlt->mlx, jlt->img, 0, 0);
}
