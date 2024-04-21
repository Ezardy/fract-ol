/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_setting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:10:33 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/21 19:04:20 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	choose_fractal(int argc, char **argv, t_render *r)
{
	(void)argc;
	(void)argv;
	r->f.r = 4;
	r->f.scale = 0.005;
	r->f.zn = burning_ship;
	r->f.cx = -WIN_WIDTH * 0.5;
	r->f.cy = -WIN_HEIGHT * 0.5;
	r->f.ox = 0;
	r->f.oy = 0;
	return (1);
}
