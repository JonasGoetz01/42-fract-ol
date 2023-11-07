/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:20:51 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/07 14:34:42 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	quit(mlx_key_data_t keydata, void *param)
{
	t_fract	*mbt;

	mbt = (t_fract *)param;
	if (keydata.key == 65361)
		mbt->offsetx -= 10;
	else if (keydata.key == 65362)
		mbt->offsety -= 10;
	else if (keydata.key == 65363)
		mbt->offsetx += 10;
	else if (keydata.key == 65364)
		mbt->offsety += 10;
	else if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
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
