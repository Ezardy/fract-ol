/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:17:21 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/21 19:39:47 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	shift(t_render *r, int shx, int shy);

int	mouse_hook(int button, int x, int y, t_render *r)
{
	if (button == Button4 || button == Button5)
	{
		r->f.ox -= (WIN_WIDTH / 2 - x) * 0.25 * r->f.scale;
		r->f.oy -= (WIN_HEIGHT / 2 - y) * 0.25 * r->f.scale;
		if (button == Button4)
			r->f.scale *= 0.98;
		else
			r->f.scale *= 1.02;
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

