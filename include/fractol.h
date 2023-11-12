/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:28:14 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/12 17:33:25 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/ft_printf.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 350
# define HEIGHT 350
# define MAX_ITERATIONS 100
# define LIMIT 16

typedef struct s_fract
{
	mlx_image_t	*img;
	double		zoom;
	mlx_t		*mlx;
	double		ca;
	double		cb;
	int			set;
	int			width;
	int			height;
	double		offsetx;
	double		offsety;
	double		mouse_x;
	double		mouse_y;
}				t_fract;

typedef struct s_helper
{
	double		a;
	double		b;
	double		ca;
	double		cb;
	double		aa;
	double		bb;
	double		ab;
	int			n;
	int			x;
	int			y;
}				t_helper;

void			print_usage(void);
void			julia(void *param);
void			mandelbrot(void *param);
void			scroll(double a, double b, void *mbt);
void			quit(mlx_key_data_t keydata, void *param);
int				get_rgba(int r, int g, int b, int a);
double			strtodo(const char *str);
void			resize(int a, int b, void *param);
void			mouse_event(double xpos, double ypos, void *param);
void			burning_ship(void *param);
void 			sierpinski_triangle(void *param);

#endif