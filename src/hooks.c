/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:20:51 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/09 16:33:28 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	quit(mlx_key_data_t keydata, void *param)
{
	t_fract	*mbt;

	mbt = (t_fract *)param;
	if (keydata.key == 65361)
		mbt->offsetx -= 0.1;
	else if (keydata.key == 65362)
		mbt->offsety -= 0.1;
	else if (keydata.key == 65363)
		mbt->offsetx += 0.1;
	else if (keydata.key == 65364)
		mbt->offsety += 0.1;
	else if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	else
		return ;
	mbt->ca = map(mbt->offsetx, 0, mbt->width, -(mbt->zoom), mbt->zoom);
	mbt->cb = map(mbt->offsety, 0, mbt->height, -(mbt->zoom), mbt->zoom);
	if (mbt->set == 1)
		mandelbrot(mbt);
	else if (mbt->set == 2)
		julia(mbt);
	return ;
}

void	scroll(double a, double b, void *mbt)
{
	a++;
	((t_fract *)mbt)->zoom -= b * 0.01;
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
