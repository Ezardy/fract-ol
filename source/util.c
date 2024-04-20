/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:17:21 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/20 19:18:01 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_render *r)
{
	if (keycode == ESC_BTN)
		exit_program(r);
	return (0);
}

int	exit_program(t_render *r)
{
	mlx_destroy_image(r->mlx, r->img);
	mlx_destroy_window(r->mlx, r->win);
	exit(0);
}

void	set_pixel_color(t_render *r, size_t x, size_t y, int color)
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

int	choose_fractal(int argc, char **argv, t_fract *fract)
{
	(void)argc;
	(void)argv;
	fract->r = 4;
	fract->scale = 0.001;
	fract->zn = burning_ship;
	fract->cx = 0;
	fract->cy = 0;
	return (1);
}
