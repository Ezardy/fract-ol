/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:34:18 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/20 19:00:40 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	render_image(t_render *r, t_fract *fract);

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
		mlx_hook(r.win, CLOSE_WIN_EVENT, 0, exit_program, &r);
		render_image(&r, &fract);
		mlx_loop(r.mlx);
	}
	ft_putstr_fd("Usage:\nfractol mandel|julia cx cy|ship\nWhere cx and cy", 1);
	ft_putstr_fd(" - real and imaginary parts of c in Zn = Zn-1 + c", 1);
	return (1);
}

static void	render_image(t_render *r, t_fract *fract)
{
	int			i;
	long double	x;
	long double	y;

	fract->py = 0;
	while (fract->py < WIN_HEIGHT)
	{
		fract->px = 0;
		while (fract->px < WIN_WIDTH)
		{
			x = fract->px * fract->scale;
			y = fract->py * fract->scale;
			i = 0;
			while (x * x + y * y < fract->r && i++ < MAX_ITER)
				fract->zn(&x, &y, fract);
			if (i > MAX_ITER)
				set_pixel_color(r, fract->px++, fract->py, 0);
			else
				set_pixel_color(r, fract->px++, fract->py, 0x00FFFFFF);
		}
		fract->py++;
	}
	mlx_put_image_to_window(r->mlx, r->win, r->img, 0, 0);
}

void	burning_ship(long double *x, long double *y, t_fract *fract)
{
	long double	tmp;

	tmp = *x * *x - *y * *y + fract->cx + fract->px * fract->scale;
	*y = fabsl(2 * *x * *y) + fract->cy + fract->py * fract->scale;
	*x = tmp;
}
