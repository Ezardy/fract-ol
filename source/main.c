/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:34:18 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/21 19:11:11 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		mlx_key_hook(r.win, key_hook, &r);
		mlx_mouse_hook(r.win, mouse_hook, &r);
		mlx_hook(r.win, DestroyNotify, 0, exit_program, &r);
		render_image(&r);
		mlx_loop(r.mlx);
	}
	ft_putstr_fd("Usage:\nfractol mandel|julia cx cy|ship\nWhere cx and cy", 1);
	ft_putstr_fd(" - floats, real and imaginary parts of c\n", 1);
	return (1);
}

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
			x = (r->f.px + r->f.cx) * r->f.scale + r->f.ox;
			y = (r->f.py + r->f.cy) * r->f.scale + r->f.oy;
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

void	burning_ship(long double *x, long double *y, t_fract *f)
{
	long double	tmp;

	tmp = *x * *x - *y * *y + (f->cx + f->px) * f->scale + f->ox;
	*y = fabsl(2 * *x * *y) + (f->cy + f->py) * f->scale + f->oy;
	*x = tmp;
}
