/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <chermist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 15:32:37 by chermist          #+#    #+#             */
/*   Updated: 2019/05/04 23:37:31 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define NLL	18446744073709551616.0
#define NL	(1LL << 56)

void	line(t_pt *p1, t_pt *p2, t_img *img)
{
	unsigned long long	d;
	unsigned long long	df;
	int					i;

	d = 0;
	i = (p2->y < p1->y) ? -1 : 1;
	df = floor((double)(p2->y - p1->y) / (p2->x - p1->x) * NLL * i + 0.5);
	put_pixel_to_img(img, p1->x++, p1->y, p1->color.mono);
	put_pixel_to_img(img, p2->x--, p2->y, p1->color.mono);
	while (p1->x <= p2->x)
	{
		if ((d += df) < df)
		{
			p1->y += i;
			p2->y -= i;
		}
		(p1->color.rgb)[3] = d / NL;
		put_pixel_to_img(img, p1->x, p1->y, p1->color.mono);
		put_pixel_to_img(img, p2->x, p2->y, p1->color.mono);
		(p1->color.rgb)[3] = ~(p1->color.rgb)[3];
		put_pixel_to_img(img, p1->x, (p1->y + i), p1->color.mono);
		put_pixel_to_img(img, p2->x, (p2->y - i), p1->color.mono);
		++p1->x;
		--p2->x;
	}
}

void	steep_line(t_pt *p1, t_pt *p2, t_img *img)
{
	unsigned long long	d;
	unsigned long long	df;
	int					i;

	d = 0;
	i = (p2->x < p1->x) ? -1 : 1;
	df = floor((double)(p2->x - p1->x) / (p2->y - p1->y) * NLL * i + 0.5);
	put_pixel_to_img(img, p1->x, p1->y++, p1->color.mono);
	put_pixel_to_img(img, p2->x, p2->y--, p1->color.mono);
	while (p1->y <= p2->y)
	{
		if ((d += df) < df)
		{
			p1->x += i;
			p2->x -= i;
		}
		(p1->color.rgb)[3] = d / NL;
		put_pixel_to_img(img, p1->x, p1->y, p1->color.mono);
		put_pixel_to_img(img, p2->x, p2->y, p1->color.mono);
		(p1->color.rgb)[3] = ~(p1->color.rgb)[3];
		put_pixel_to_img(img, (p1->x + i), p1->y, p1->color.mono);
		put_pixel_to_img(img, (p2->x - i), p2->y, p1->color.mono);
		++p1->y;
		--p2->y;
	}
}

void	diagonal(t_pt *p1, t_pt *p2, t_img *img)
{
	int	df;

	df = (p2->y < p1->y) ? -1 : 1;
	while (p1->x <= p2->x)
	{
		put_pixel_to_img(img, p1->x, p1->y, p1->color.mono);
		put_pixel_to_img(img, p2->x, p2->y, p1->color.mono);
		++p1->x;
		--p2->x;
		p1->y += df;
		p2->y -= df;
	}
}

void	draw_line(t_pt p1, t_pt p2, t_img *img)
{
	int	dy;
	int	dx;

	dy = abs(p2.y - p1.y);
	dx = abs(p2.x - p1.x);
	if (dy > dx)
	{
		if (p2.y < p1.y)
			steep_line(&p2, &p1, img);
		else
			steep_line(&p1, &p2, img);
	}
	else
	{
		if (p2.x < p1.x)
			(dy != dx ? line : diagonal)(&p2, &p1, img);
		else
			(dy != dx ? line : diagonal)(&p1, &p2, img);
	}
}
