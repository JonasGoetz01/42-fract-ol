/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:20:51 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/13 12:03:08 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	else if (mbt->set == 3)
		burning_ship(mbt);
}

void	scroll(double a, double b, void *mbt)
{
	t_fract	*fract;
	double	cursor_rel_x;
	double	cursor_rel_y;
	double	zoom_factor;

	a++;
	fract = (t_fract *)mbt;
	cursor_rel_x = (fract->mouse_x) / fract->width;
	cursor_rel_y = (fract->mouse_y) / fract->height;
	if (b > 0)
		zoom_factor = 1.1;
	else
		zoom_factor = 0.9;
	fract->zoom *= zoom_factor;
	fract->offsetx += (cursor_rel_x - 0.5) * (1.0 - zoom_factor);
	fract->offsety += (cursor_rel_y - 0.5) * (1.0 - zoom_factor);
	if (fract->set == 1)
		mandelbrot(fract);
	else if (fract->set == 2)
		julia(fract);
	else if (fract->set == 3)
		burning_ship(fract);
}

void	mouse_event(double xpos, double ypos, void *param)
{
	t_fract	*fract;

	fract = (t_fract *)param;
	fract->mouse_x = xpos;
	fract->mouse_y = ypos;
	if (fract->mouse_clicked)
	{
		fract->ca = ((double)xpos / fract->width) * (fract->zoom * 2)
			- fract->zoom + fract->offsetx;
		fract->cb = ((double)ypos / fract->height) * (fract->zoom * 2)
			- fract->zoom + fract->offsety;
		if (fract->set == 2)
			julia(fract);
	}
}

void	mouse_click_event(enum mouse_key mouse_key, enum action action,
		enum modifier_key modifier_key, void *param)
{
	t_fract	*fract;

	fract = (t_fract *)param;
	(void)modifier_key;
	if (mouse_key == 0 && action == 1)
		fract->mouse_clicked = 1;
	else if (mouse_key == 0 && action == 0)
		fract->mouse_clicked = 0;
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
	else if (fract->set == 3)
		burning_ship(fract);
}
