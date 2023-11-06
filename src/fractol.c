/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:33:48 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/06 10:55:56 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 500
#define HEIGHT 500
#define MAX_ITERATIONS 200
#define LIMIT 16

double	map(double value, double start1, double stop1, double start2,
		double stop2)
{
	return (start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1)));
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	mandelbrot(void *param)
{
	int				color;
	t_helper		helper;
	t_mandelbrot	*mbt;

	mbt = (t_mandelbrot *)param;
	helper.x = 0;
	helper.y = 0;
	while (helper.y < HEIGHT)
	{
		helper.x = 0;
		while (helper.x < WIDTH)
		{
			helper.a = map(helper.x, 0, WIDTH, -(*mbt->zoom), *mbt->zoom);
			helper.b = map(helper.y, 0, HEIGHT, -(*mbt->zoom), *mbt->zoom);
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

void	scroll(double a, double b, void *zoom)
{
	a++;
	*(double *)zoom -= b * 0.01;
}

int	main(void)
{
	t_mandelbrot	mbt;
	mlx_t			*mlx;
	mlx_image_t		*img;
	double			zoom;

	zoom = 2.5;
	mlx = mlx_init(WIDTH, HEIGHT, "fract'ol", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_scroll_hook(mlx, scroll, &zoom);
	mbt.img = img;
	mbt.mlx = mlx;
	mbt.zoom = &zoom;
	mlx_loop_hook(mlx, mandelbrot, &mbt);
	mlx_loop(mlx);
	return (0);
}
