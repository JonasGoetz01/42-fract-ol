/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:20:51 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/10 14:48:45 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	quit(mlx_key_data_t keydata, void *param)
{
	t_fract	*mbt;

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
	double	aspect_ratio;
	double	new_aspect_ratio;

	fract = (t_fract *)param;
	aspect_ratio = (double)fract->width / (double)fract->height;
	new_aspect_ratio = (double)a / (double)b;
	if (aspect_ratio < new_aspect_ratio)
	{
		fract->width = a;
		fract->height = a / aspect_ratio;
	}
	else
	{
		fract->height = b;
		fract->width = b * aspect_ratio;
	}
	mlx_delete_image(fract->mlx, fract->img);
	fract->img = mlx_new_image(fract->mlx, fract->width, fract->height);
	if (fract->set == 1)
		mandelbrot(fract);
	else if (fract->set == 2)
		julia(fract);
}
