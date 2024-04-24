/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:41:36 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/24 17:00:53 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		hsv_to_hex(int c, float l, float r);
static float	saturate(float v, float l, float r);

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
				set_pixel_color(r->f.px++, r->f.py,
					hsv_to_hex(i, r->lcolor, r->rcolor), r);
		}
		r->f.py++;
	}
	mlx_put_image_to_window(r->mlx, r->win, r->img, 0, 0);
}

static int	hsv_to_hex(int c, float l, float r)
{
	float	hsv;
	int		hex;
	float	i;
	int		ii;

	hex = 0;
	hsv = saturate((float)c / (MAX_ITER + 1), l, r);
	i = floorf(hsv * 6);
	ii = (int)i % 6;
	if (ii == 1)
		hex = (int)(255 * (1 - hsv * 6 + i)) << 16 | 255 << 8;
	else if (ii == 2)
		hex = 255 << 8 | (int)(255 * (hsv * 6 - i));
	else if (ii == 3)
		hex = (int)(255 * (1 - hsv * 6 + i)) << 8 | 255;
	else if (ii == 4)
		hex = (int)(255 * (hsv * 6 - i)) << 16 | 255;
	else if (ii == 5)
		hex = 255 << 16 | (int)(255 * (1 - hsv * 6 + i));
	else
		hex = 255 << 16 | (int)(255 * (hsv * 6 - i)) << 8
			| (int)(255 * (1 - hsv * 6 + i));
	return (hex);
}

static float	saturate(float v, float l, float r)
{
	if (v < l)
		v = l;
	else if (v > r)
		r = l;
	return (v);
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
