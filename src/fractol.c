/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:33:48 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/02 16:28:06 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITERATIONS 100

uint32_t	mandelbrot(double real, double imag)
{
	uint32_t	n;
	double		r;
	double		i;
	double		r2;
	double		i2;

	r = 0.0;
	i = 0.0;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		r2 = r * r;
		i2 = i * i;
		if (r2 + i2 > 4.0)
		{
			return (n);
		}
		i = 2 * r * i + imag;
		r = r2 - i2 + real;
		n++;
	}
	return (MAX_ITERATIONS);
}

uint32_t	mapToColor(uint32_t value, uint32_t max_iterations)
{
	double	t;
	double	r;
	double	g;
	double	b;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	double	colors[][3] = {{0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}};

	t = (double)value / (double)max_iterations;
	r = colors[0][0] + t * (colors[1][0] - colors[0][0]);
	g = colors[0][1] + t * (colors[1][1] - colors[0][1]);
	b = colors[0][2] + t * (colors[1][2] - colors[0][2]);
	red = (uint8_t)(r * 255);
	green = (uint8_t)(g * 255);
	blue = (uint8_t)(b * 255);
	return ((red << 16) | (green << 8) | blue);
}

static void	clear_screen(mlx_t *mlx)
{
	uint32_t	x;
	uint32_t	y;
	mlx_image_t	*img;

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(img, x, y, mapToColor(0, MAX_ITERATIONS));
			x++;
		}
		y++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
}

static void	gen_image(void *param)
{
	uint32_t		x;
	uint32_t		y;
	mlx_image_t		*img;
	double			real;
	double			imag;
	uint32_t		value;
	static double	limit;
	mlx_t			*mlx;

	mlx = param;
	limit += 0.02;
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			real = (x - WIDTH / limit) * pow(limit, 2) / WIDTH;
			imag = (y - HEIGHT / limit) * pow(limit, 2) / HEIGHT;
			value = mandelbrot(real, imag);
			mlx_put_pixel(img, x, y, mapToColor(value, MAX_ITERATIONS));
			x++;
		}
		y++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
	clear_screen(mlx);
}

int	main(void)
{
	mlx_t	*mlx;
	double	limit;

	limit = 1.0;
	mlx = mlx_init(WIDTH, HEIGHT, "fract'ol", true);
	mlx_loop_hook(mlx, gen_image, mlx);
	mlx_loop(mlx);
	return (0);
}
