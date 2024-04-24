/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:34:18 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/24 18:43:31 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	choose_fractal(int argc, char **argv, t_render *r);
static void	julia(long double *x, long double *y, t_fract *f);
static void	burning_ship(long double *x, long double *y, t_fract *fract);
static void	mandel(long double *x, long double *y, t_fract *f);

int	main(int argc, char **argv)
{
	t_render	r;

	if (argc > 1 && choose_fractal(argc - 1, argv + 1, &r))
	{
		r.mlx = mlx_init();
		r.win = mlx_new_window(r.mlx, WIN_WIDTH, WIN_HEIGHT, "fract-ol");
		r.img = mlx_new_image(r.mlx, WIN_WIDTH, WIN_HEIGHT);
		r.img_buff = mlx_get_data_addr(r.img, &r.pixel_bits, &r.line_bytes,
				&r.endian);
		mlx_do_key_autorepeaton(r.mlx);
		mlx_hook(r.win, KeyPress, 0, key_hook, &r);
		mlx_mouse_hook(r.win, mouse_hook, &r);
		mlx_hook(r.win, DestroyNotify, 0, exit_program, &r);
		render_image(&r);
		mlx_loop(r.mlx);
	}
	ft_putstr_fd("Usage:\nfractol mandel|julia cx cy|ship\nWhere cx and cy", 1);
	ft_putstr_fd(" - floats, real and imaginary parts of c\n", 1);
	return (1);
}

static int	choose_fractal(int argc, char **argv, t_render *r)
{
	int	chosen;

	chosen = 1;
	r->f.scale = 0.005;
	r->f.r = 4;
	r->f.ox = 0;
	r->f.oy = 0;
	r->f.cx = -WIN_WIDTH * 0.5;
	r->f.cy = -WIN_HEIGHT * 0.5;
	r->lcolor = 0.1;
	r->rcolor = 0.7;
	if (argc == 1 && !ft_strncmp(argv[0], "ship", 4))
		r->f.zn = burning_ship;
	else if (argc == 3 && !ft_strncmp(argv[0], "julia", 5)
		&& ft_fatol(argv[1], &r->f.cx) && ft_fatol(argv[2], &r->f.cy))
		r->f.zn = julia;
	else if (argc == 1 && !ft_strncmp(argv[0], "mandel", 6))
		r->f.zn = mandel;
	else
		chosen = 0;
	return (chosen);
}

static void	burning_ship(long double *x, long double *y, t_fract *f)
{
	long double	tmp;

	tmp = *x * *x - *y * *y + (f->cx + f->px) * f->scale + f->ox;
	*y = fabsl(2 * *x * *y) + (f->cy + f->py) * f->scale + f->oy;
	*x = tmp;
}

static void	julia(long double *x, long double *y, t_fract *f)
{
	long double	tmp;

	tmp = *x * *x - *y * *y;
	*y = 2 * *x * *y + f->cy;
	*x = tmp + f->cx;
}

static void	mandel(long double *x, long double *y, t_fract *f)
{
	long double	tmp;

	tmp = *x * *x - *y * *y + (f->cx + f->px) * f->scale + f->ox;
	*y = 2 * *x * *y + (f->cy + f->py) * f->scale + f->oy;
	*x = tmp;
}
