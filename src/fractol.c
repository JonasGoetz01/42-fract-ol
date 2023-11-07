/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:33:48 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/07 03:31:09 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_usage(void)
{
	ft_printf("Usage: ./fractol [mandelbrot | julia]\n");
	exit(-1);
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
		mbt.set = 2;
	else
		print_usage();
	mbt.zoom = 2.5;
	mlx = mlx_init(WIDTH, HEIGHT, "fract'ol", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_key_hook(mlx, quit, NULL);
	mlx_scroll_hook(mlx, scroll, &mbt);
	mbt.img = img;
	mbt.mlx = mlx;
	scroll(0, 0, &mbt);
	mlx_loop(mlx);
	return (0);
}
