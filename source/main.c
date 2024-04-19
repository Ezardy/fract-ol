/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:34:18 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/19 20:33:51 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	key_hook(int keycode, t_render *r);
static void	render_image(t_render *r, t_fract *fract);
static void	set_pixel_color(t_render *r, size_t x, size_t y, int color);
static int	choose_fractal(int argc, char **argv, t_fract *fract);

int	main(int argc, char **argv)
{
	t_render	r;
	t_fract		fract;

	if (argc > 1 && choose_fractal(argc - 1, argv + 1, &fract))
	{
		r.mlx = mlx_init();
		r.win = mlx_new_window(r.mlx, WIN_WIDTH, WIN_HEIGHT, "fract-ol");
		r.img = mlx_new_image(r.mlx, WIN_WIDTH, WIN_HEIGHT);
		r.img_buff = mlx_get_data_addr(r.img, &r.pixel_bits, &r.line_bytes,
				&r.endian);
		mlx_key_hook(r.win, key_hook, &r);
		mlx_loop(r.mlx);
	}
	ft_putstr_fd("Usage:\nfractol mandel|julia cx cy|ship\nWhere cx and cy", 1);
	ft_putstr_fd(" - real and imaginary parts of c in Zn = Zn-1 + c", 1);
	return (1);
}

void	render_image(t_render *r, t_fract *fract)
{
	size_t	px;
	size_t	py;
	int		i;
	long	x;
	long	y;

	py = 0;
	while (py++ < WIN_HEIGHT)
	{
		px = 0;
		while (px++ < WIN_WIDTH)
		{
			x = px;
			y = py;
			i = 0;
			while (x * x + y * y < fract->r && i++ < MAX_ITER)
				fract->zn(&x, &y, fract);
			if (i == MAX_ITER)
				set_pixel_color(r, px++, py++, 0);
			else
				set_pixel_color(r, px++, py++, 0x00FFFFFF);
		}
	}
}

static void	set_pixel_color(t_render *r, size_t x, size_t y, int color)
{
	size_t	pixel;

	color = mlx_get_color_value(r->mlx, color);
	pixel = y * r->line_bytes + x * 4;
	if (r->endian)
	{
		r->img_buff[pixel] = color >> 24;
		r->img_buff[pixel + 1] = color >> 16 & 0xFF;
		r->img_buff[pixel + 2] = color >> 8 & 0xFF;
		r->img_buff[pixel + 3] = color & 0xFF;
	}
	else
	{
		r->img_buff[pixel] = color & 0xFF;
		r->img_buff[pixel + 1] = color >> 8 & 0xFF;
		r->img_buff[pixel + 2] = color >> 16 & 0xFF;
		r->img_buff[pixel + 3] = color >> 24;
	}
}

static int	choose_fractal(int argc, char **argv, t_fract *fract)
{
	fract->r = 2;
	fract->zn = burning_ship;
	fract->cx = -1.762;
	fract->cy = -0.028;
	return (1);
}

static int	key_hook(int keycode, t_render *r)
{
	if (keycode == kVK_Escape)
	{
		mlx_destroy_image(r->mlx, r->img);
		mlx_destroy_window(r->mlx, r->win);
		exit(0);
	}
	return (0);
}
