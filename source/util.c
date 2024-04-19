/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:17:21 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/19 20:32:35 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	burning_ship(long double *x, long double *y, struct s_fract *fract)
{
	long double	tmp;

	tmp = *x * *x - *y * *y + fract->cx;
	*y = fabsl(2 * *x * *y) + fract->cy;
	*x = tmp;
}
