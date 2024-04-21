/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:17:21 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/21 14:38:26 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	shift(t_render *r, int shx, int shy);

int	key_hook(int keycode, t_render *r)
{
	if (keycode == kVK_Escape)
		exit_program(r);
	else if (keycode == kVK_UpArrow)
		shift(r, 0, 1);
	else if (keycode == kVK_DownArrow)
		shift(r, 0, -1);
	else if (keycode == kVK_RightArrow)
		shift(r, 1, 0);
	else if (keycode == kVK_LeftArrow)
		shift(r, -1, 0);
	return (0);
}

static void	shift(t_render *r, int shx, int shy)
{
	r->f.ox += 10 * shx;
	r->f.oy += 10 * shy;
	render_image(r);
}

int	exit_program(t_render *r)
{
	mlx_destroy_image(r->mlx, r->img);
	mlx_destroy_window(r->mlx, r->win);
	exit(0);
}

void	set_pixel_color(size_t x, size_t y, int color, t_render *r)
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

int	choose_fractal(int argc, char **argv, t_render *r)
{
	(void)argc;
	(void)argv;
	r->f.r = 4;
	r->f.scale = 0.005;
	r->f.zn = burning_ship;
	r->f.cx = 0;
	r->f.cy = 0;
	r->f.ox = WIN_WIDTH * 0.75;
	r->f.oy = -WIN_HEIGHT * 0.75;
	return (1);
}
