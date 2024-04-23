/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:41:36 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/23 21:57:23 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	render_image(t_render *r)
{
	int			i;
	long double	x;
	long double	y;

	r->f.py = 0;
	while (r->f.py < WIN_HEIGHT)
	{
		r->f.px = 0;
		while (r->f.px < WIN_WIDTH)
		{
			x = (r->f.px - WIN_WIDTH / 2) * r->f.scale + r->f.ox;
			y = (r->f.py - WIN_HEIGHT / 2) * r->f.scale + r->f.oy;
			i = 0;
			while (x * x + y * y < r->f.r && i++ < MAX_ITER)
				r->f.zn(&x, &y, &r->f);
			if (i > MAX_ITER)
				set_pixel_color(r->f.px++, r->f.py, 0, r);
			else
				set_pixel_color(r->f.px++, r->f.py, 0x00FFFFFF, r);
		}
		r->f.py++;
	}
	mlx_put_image_to_window(r->mlx, r->win, r->img, 0, 0);
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
