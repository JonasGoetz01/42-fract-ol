/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:33:48 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/03 17:57:18 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 360
#define HEIGHT 360
#define MAX_ITERATIONS 100
#define LIMIT 16

double	map(int value, int start1, int stop1, int start2, int stop2)
{
	return (start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1)));
}

uint32_t	rgb_color(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int	mandelbrot(double real, double imag)
{
	int		n;
	double	oreal;
	double	oimag;
	double	real_squared;
	double	imag_squared;

	n = 0;
	oreal = real;
	oimag = imag;
	while (n < MAX_ITERATIONS)
	{
		real_squared = real * real;
		imag_squared = imag * imag;
		if (real_squared + imag_squared > LIMIT * LIMIT)
			break ;
		imag = 2 * real * imag + oimag;
		real = real_squared - imag_squared + oreal;
		n++;
	}
	return (n);
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			x;
	int			y;
	int			color;
	double		real;
	double		imag;
	int			iterations;

	mlx = mlx_init(WIDTH, HEIGHT, "fract'ol", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			real = map(x, 0, WIDTH, -2.0, 2.0);
			imag = map(y, 0, HEIGHT, -2.0, 2.0);
			iterations = mandelbrot(real, imag);
			color = map(iterations, 0, MAX_ITERATIONS, 0, 255);
			mlx_put_pixel(img, x, y, rgb_color(255, color, color, color));
			x++;
		}
		y++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
