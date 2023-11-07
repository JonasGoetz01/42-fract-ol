/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:33:48 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/07 18:52:05 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	print_usage(void)
{
	ft_printf("Usage: ./fractol [mandelbrot | julia]\n");
	exit(-1);
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

int	main(int argc, char **argv)
{
	t_fract		mbt;
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (argc < 2)
		print_usage();
	if (!ft_strncmp(argv[1], "mandelbrot", 11))
		mbt.set = 1;
	else if (!ft_strncmp(argv[1], "julia", 6))
	{
		mbt.set = 2;
		if (argc == 4)
		{
			mbt.ca = argv[2];
			mbt.cb = argv[3];
		}
	}
	else
		print_usage();
	mbt.zoom = 2.5;
	mbt.width = WIDTH;
	mbt.height = HEIGHT;
	mbt.offsetx = 0.0;
	mbt.offsety = 0.0;
	mbt.ca = -0.8;
	mbt.cb = 0.156;
	mlx = mlx_init(WIDTH, HEIGHT, "fract'ol", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_key_hook(mlx, quit, NULL);
	mlx_scroll_hook(mlx, scroll, &mbt);
	mlx_resize_hook(mlx, resize, &mbt);
	mbt.img = img;
	mbt.mlx = mlx;
	scroll(0, 0, &mbt);
	mlx_loop(mlx);
	return (0);
}
