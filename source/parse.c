/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:56:43 by zanikin           #+#    #+#             */
/*   Updated: 2024/04/22 16:23:22 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	read_int(char *s, long double *n);
static int	ft_isspace(unsigned char c);

int	ft_fatol(char *s, long double *n)
{
	char		sign;
	long double	frac;
	int			prec;

	prec = 0;
	while (ft_isspace(*s))
		s++;
	sign = *s;
	if (*s == '+' || *s == '-')
		s++;
	s += read_int(s, n);
	if (*s == '.')
	{
		prec = read_int(++s, &frac);
		*n += frac / powl(10, prec);
	}
	*n *= 1 - 2 * (sign == '-');
	return (*(s + prec) == '\0');
}

static int	read_int(char *s, long double *n)
{
	int	c;

	c = 0;
	*n = 0;
	while (ft_isdigit(*s))
	{
		*n = *n * 10 + *s - '0';
		c++;
		s++;
	}
	return (c);
}

static int	ft_isspace(unsigned char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}
