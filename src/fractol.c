/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:33:48 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/12 17:38:01 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	print_usage(void)
{
	ft_printf("Usage: ./fractol [mandelbrot | julia | burning-ship]\n");
	ft_printf("\t-julia\n");
	ft_printf("\t-julia [ca] [cb]\n");
	ft_printf("\t-mandelbrot\n");
	ft_printf("\t-burning-ship\n");
	exit(-1);
}

void	routines(int argc, char **argv, t_fract *mbt)
{
	if (!ft_strncmp(argv[1], "mandelbrot", 11))
	{
		if (argc == 2)
			mbt->set = 1;
		else
			print_usage();
	}
	else if (!ft_strncmp(argv[1], "julia", 6))
	{
		mbt->set = 2;
		if (argc == 4)
		{
			mbt->ca = strtodo(argv[2]);
			mbt->cb = strtodo(argv[3]);
		}
		else if (argc == 2)
		{
			mbt->ca = -0.8;
			mbt->cb = 0.156;
		}
		else
			print_usage();
	}
	else if (!ft_strncmp(argv[1], "burning-ship", 13))
	{
		if (argc == 2)
			mbt->set = 3;
		else
			print_usage();
	}
	else
		print_usage();
}

int	main(int argc, char **argv)
{
	t_fract		mbt;
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (argc < 2)
		print_usage();
	routines(argc, argv, &mbt);
	img = NULL;
	mlx = NULL;
	mbt.zoom = 2.5;
	mbt.width = WIDTH;
	mbt.height = HEIGHT;
	mbt.offsetx = 0.0;
	mbt.offsety = 0.0;
	mlx = mlx_init(WIDTH, HEIGHT, "fract'ol", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_key_hook(mlx, quit, &mbt);
	mlx_scroll_hook(mlx, scroll, &mbt);
	mlx_resize_hook(mlx, resize, &mbt);
	mlx_cursor_hook(mlx, mouse_event, &mbt);
	mbt.img = img;
	mbt.mlx = mlx;
	scroll(0, 0, &mbt);
	mlx_loop(mlx);
	return (0);
}
