/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <chermist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 20:09:53 by chermist          #+#    #+#             */
/*   Updated: 2019/05/04 22:50:34 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pt	*iso(t_pt *pt, t_view *view)
{
	float previous_x;
	float previous_y;

	previous_x = pt->x;
	previous_y = pt->y;
	pt->x = view->offsetx + ((previous_x - previous_y) *
			cos(M_PI / 6) / view->scale);
	pt->y = view->offsety + (((previous_x + previous_y) *
				sin(M_PI / 6) - (pt->z * view->hz)) / view->scale);
	return (pt);
}

t_pt	*parallel(t_pt *pt, t_view *view)
{
	pt->x = view->offsetx + (pt->x - pt->z * view->hz) / view->scale;
	pt->y = view->offsety + (pt->y - pt->z * view->hz) / view->scale;
	return (pt);
}

t_pt	*get_pt(t_pt *pt, t_mlx *mlx, int x, int y)
{
	pt->x = x;
	pt->y = y;
	pt->z = mlx->mtx->map[y][x];
	if (mlx->view->clr == -1)
	{
		if (ceil(pt->z * mlx->view->hz) > 0)
			pt->color.mono = 0xff0000;
		else if ((pt->z * mlx->view->hz) < 0)
			pt->color.mono = 0x0000ff;
		else if (ceil(pt->z * mlx->view->hz) == 0)
			pt->color.mono = 0x00ffff;
	}
	else
		pt->color.mono = mlx->mtx->color[y][x];
	return (pt);
}

void	dot_draw(t_pt p1, t_pt p2, t_img *img)
{
	put_pixel_to_img(img, p1.x, p1.y, p1.color.mono);
	put_pixel_to_img(img, p2.x, p2.y, p2.color.mono);
}

void	draw(t_mtx *mtx, t_mlx *mlx)
{
	int			x;
	int			y;
	t_pt		st;
	t_pt		end;

	flush_img(mlx->img);
	mlx_clear_window(mlx->iptr, mlx->wptr);
	y = -1;
	while (++y < mtx->height)
	{
		x = -1;
		while (++x < mtx->width)
		{
			st = *mlx->proj(get_pt(&st, mlx, x, y), mlx->view);
			if (x + 1 < mtx->width)
				mlx->view->line(st, *mlx->proj(get_pt(&end, mlx, x + 1, y),
							mlx->view), mlx->img);
			if (y + 1 < mtx->height)
				mlx->view->line(st, *mlx->proj(get_pt(&end, mlx, x, y + 1),
							mlx->view), mlx->img);
		}
	}
	mlx_put_image_to_window(mlx->iptr, mlx->wptr, mlx->img->ptr, 0, 0);
}
