/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:12:54 by chermist          #+#    #+#             */
/*   Updated: 2019/05/04 23:45:56 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		get_color(t_pt current, t_pt start, t_pt end, t_bres br)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (current.color.mono == end.color.mono)
		return (current.color.mono);
	percentage = (br.dx > br.dy) ? percent(start.x, end.x, current.x) :
		percent(start.y, end.y, current.y);
	red = get_light((start.color.mono >> 16) & 0xFF, \
			(end.color.mono >> 16) & 0xFF, percentage);
	green = get_light((start.color.mono >> 8) & 0xFF, \
			(end.color.mono >> 8) & 0xFF, percentage);
	blue = get_light(start.color.mono & 0xFF, \
			end.color.mono & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void	br_init(t_pt start, t_pt end, t_bres *br, t_pt *current)
{
	br->dy = ABS(end.y - start.y);
	br->dx = ABS(end.x - start.x);
	br->signx = (start.x < end.x) ? 1 : -1;
	br->signy = (start.y < end.y) ? 1 : -1;
	br->err[0] = (br->dx > br->dy ? br->dx : -br->dy) / 2;
	current->x = start.x;
	current->y = start.y;
}

void	bresenham(t_pt start, t_pt end, t_img *img)
{
	t_bres	br;
	t_pt	current;

	br_init(start, end, &br, &current);
	put_pixel_to_img(img, end.x, end.y, end.color.mono);
	while (current.x != end.x || current.y != end.y)
	{
		if (current.x < 0 || current.x >= WIDTH
			|| current.y < 0 || current.y >= HEIGHT)
			break ;
		put_pixel_to_img(img, current.x, current.y, \
				get_color(current, start, end, br));
		br.err[1] = br.err[0];
		if (br.err[1] > -br.dx)
		{
			br.err[0] -= br.dy;
			current.x += br.signx;
		}
		if (br.err[1] < br.dy)
		{
			br.err[0] += br.dx;
			current.y += br.signy;
		}
	}
}
