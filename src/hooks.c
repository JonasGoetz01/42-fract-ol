/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:20:51 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/07 10:41:26 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	quit(mlx_key_data_t keydata, void *param)
{
	t_fract	*fract;

	fract = (t_fract *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keydata.key == MLX_KEY_UP)
		fract->offsetY -= 0.1;
	if (keydata.key == MLX_KEY_DOWN)
		fract->offsetY += 0.1;
	if (keydata.key == MLX_KEY_LEFT)
		fract->offsetX -= 0.1;
	if (keydata.key == MLX_KEY_RIGHT)
		fract->offsetX += 0.1;
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
