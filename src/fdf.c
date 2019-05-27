/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 20:18:42 by chermist          #+#    #+#             */
/*   Updated: 2019/05/05 00:18:05 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_action(int key, t_mlx *mlx)
{
	if (key == KEY_RIGHT)
		mlx->view->offsetx += 10;
	if (key == KEY_LEFT)
		mlx->view->offsetx -= 10;
	if (key == KEY_P && (mlx->proj != parallel))
		mlx->proj = parallel;
	if (key == KEY_I && (mlx->proj != iso))
		mlx->proj = iso;
	if (key == KEY_D && (mlx->view->line != dot_draw))
		mlx->view->line = dot_draw;
	if (key == KEY_X && (mlx->view->line != draw_line))
		mlx->view->line = draw_line;
	if (key == KEY_MINUS)
		mlx->view->scale += 0.005;
	if (key == KEY_EQUAL && mlx->view->scale > 0.010)
		mlx->view->scale -= 0.005;
	if (key == KEY_PAD_SUB)
		mlx->view->hz -= 0.05;
	if (key == KEY_PAD_ADD)
		mlx->view->hz += 0.05;
	if (key == KEY_C)
		mlx->view->clr *= -1;
	if (key == KEY_R)
		set_default(mlx);
}

int		key_press(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
	{
		purge(mlx);
		ft_iarrdel((void**)mlx->mtx->map, mlx->mtx->height);
		ft_iarrdel((void**)mlx->mtx->color, mlx->mtx->height);
		exit(1);
	}
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_RIGHT || key == KEY_LEFT
		|| key == KEY_P || key == KEY_I || key == KEY_D || key == KEY_X
		|| key == KEY_MINUS || key == KEY_EQUAL || key == KEY_PAD_SUB
		|| key == KEY_PAD_ADD || key == KEY_C || key == KEY_R)
	{
		if (key == KEY_UP)
			mlx->view->offsety -= 10;
		if (key == KEY_DOWN)
			mlx->view->offsety += 10;
		key_action(key, mlx);
		draw(mlx->mtx, mlx);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_mtx	mtx;
	t_mlx	mlx;

	if (ac == 2)
	{
		parse(&mtx, av[1]);
		do_init(&mlx);
		mtx.scale = 10;
		mlx.mtx = &mtx;
		draw(&mtx, &mlx);
		mlx_hook(mlx.wptr, 2, 0, key_press, &mlx);
		mlx_loop(mlx.iptr);
	}
	else
		err_handle("Usage: ./fdf *.fdf\n");
	return (0);
}
