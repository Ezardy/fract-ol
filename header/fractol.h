/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:32:14 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/20 19:11:10 by zanikin          ###   ########.fr       */
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
#  define MAX_ITER 200
# endif
# define ESC_BTN 53
# define CLOSE_WIN_EVENT 17
# include "mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <math.h>

typedef struct s_fract
{
	size_t		r;
	size_t		px;
	size_t		py;
	long double	cx;
	long double	cy;
	long double	scale;
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

int		key_hook(int keycode, t_render *r);
int		exit_program(t_render *r);
void	burning_ship(long double *x, long double *y, t_fract *fract);
void	set_pixel_color(t_render *r, size_t x, size_t y, int color);
int		choose_fractal(int argc, char **argv, t_fract *fract);
#endif
