/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:32:14 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/19 20:33:03 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# ifndef WIN_WIDTH
#  define WIN_WIDTH 640
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 480
# endif
# ifndef MAX_ITER
#  define MAX_ITER 64
# endif
# include "mlx.h"
# include "libft/libft.h"
# include <Carbon/Carbon.h>
# include <math.h>

typedef struct s_fract
{
	size_t		r;
	long double	cx;
	long double	cy;
	void		(*zn)(long double *x, long double *y, struct s_fract *fract);
}	t_fract;

typedef struct s_render
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_buff;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	int		lcolor;
	int		rcolor;
}	t_render;

void	burning_ship(long double *x, long double *y, struct s_fract *fract);
#endif
