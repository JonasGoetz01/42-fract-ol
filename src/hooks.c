/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:20:51 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/10 13:41:01 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	quit(mlx_key_data_t keydata, void *param)
{
	t_fract	*mbt;
	double	range_x;
	double	range_y;

	mbt = (t_fract *)param;
	if (keydata.key == MLX_KEY_RIGHT)
		mbt->offsetx -= 0.05;
	else if (keydata.key == MLX_KEY_DOWN)
		mbt->offsety -= 0.05;
	else if (keydata.key == MLX_KEY_LEFT)
		mbt->offsetx += 0.05;
	else if (keydata.key == MLX_KEY_UP)
		mbt->offsety += 0.05;
	else if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	else
		return ;
	range_x = mbt->width / mbt->zoom;
	range_y = mbt->height / mbt->zoom;
	mbt->ca = mbt->offsetx / mbt->width * range_x - range_x / 2;
	mbt->cb = mbt->offsety / mbt->height * range_y - range_y / 2;
	if (mbt->set == 1)
		mandelbrot(mbt);
	else if (mbt->set == 2)
		julia(mbt);
}

void	scroll(double a, double b, void *mbt)
{
	a++;
	if (b > 0)
		((t_fract *)mbt)->zoom -= 0.1;
	else
		((t_fract *)mbt)->zoom += 0.01;
	if (((t_fract *)mbt)->set == 1)
		mandelbrot(mbt);
	else if (((t_fract *)mbt)->set == 2)
		julia(mbt);
}

void	resize(int a, int b, void *param)
{
	t_fract	*fract;

	fract = (t_fract *)param;
	fract->height = b;
	fract->width = a;
	mlx_delete_image(fract->mlx, fract->img);
	fract->img = mlx_new_image(fract->mlx, a, b);
	if (fract->set == 1)
		mandelbrot(fract);
	else if (fract->set == 2)
		julia(fract);
}
