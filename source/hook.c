/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:17:21 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/24 18:35:49 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	shift(t_render *r, int shx, int shy);
static void	color_shift(t_render *r, float l, float rb);

int	mouse_hook(int button, int x, int y, t_render *r)
{
	if (button == Button4 || button == Button5)
	{
		if (button == Button4)
			r->f.scale *= 0.98;
		else
			r->f.scale *= 1.02;
		r->f.ox -= (WIN_WIDTH / 2 - x) * 0.25 * r->f.scale;
		r->f.oy -= (WIN_HEIGHT / 2 - y) * 0.25 * r->f.scale;
		render_image(r);
	}
	return (0);
}

int	key_hook(int keycode, t_render *r)
{
	if (keycode == kVK_Escape)
		exit_program(r);
	else if (keycode == kVK_UpArrow)
		shift(r, 0, -1);
	else if (keycode == kVK_DownArrow)
		shift(r, 0, 1);
	else if (keycode == kVK_RightArrow)
		shift(r, -1, 0);
	else if (keycode == kVK_LeftArrow)
		shift(r, +1, 0);
	else if (keycode == kVK_ANSI_Comma)
		color_shift(r, 1, 0.95);
	else if (keycode == kVK_ANSI_Period)
		color_shift(r, 1, 1.05);
	else if (keycode == kVK_ANSI_Minus)
		color_shift(r, 0.95, 1);
	else if (keycode == kVK_ANSI_Equal)
		color_shift(r, 1.05, 1);
	return (0);
}

static void	shift(t_render *r, int shx, int shy)
{
	r->f.ox -= 10 * shx * r->f.scale;
	r->f.oy += 10 * shy * r->f.scale;
	render_image(r);
}

int	exit_program(t_render *r)
{
	mlx_destroy_image(r->mlx, r->img);
	mlx_destroy_window(r->mlx, r->win);
	exit(0);
}

static void	color_shift(t_render *r, float l, float rb)
{
	float	ncolor;

	if (l != 1.0f)
	{
		ncolor = r->lcolor * l;
		if (ncolor < r->rcolor && ncolor > 0.01)
		{
			r->lcolor = ncolor;
			render_image(r);
		}
	}
	if (rb != 1.0f)
	{
		ncolor = r->rcolor * rb;
		if (ncolor > r->lcolor && ncolor < 1.0f)
		{
			r->rcolor = ncolor;
			render_image(r);
		}
	}
}
