/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:28:14 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/06 10:54:41 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/ft_printf.h"
# include <math.h>

typedef struct s_mandelbrot
{
	mlx_image_t	*img;
	double		*zoom;
	mlx_t		*mlx;
}				t_mandelbrot;

typedef struct s_helper
{
	double		a;
	double		b;
	double		ca;
	double		cb;
	double		aa;
	double		bb;
	int			n;
	int			x;
	int			y;
}				t_helper;

#endif