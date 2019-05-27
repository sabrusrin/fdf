/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 21:18:33 by chermist          #+#    #+#             */
/*   Updated: 2019/05/04 21:37:41 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	del_img(t_mlx *mlx)
{
	if (mlx->img->ptr != NULL)
		mlx_destroy_image(mlx->iptr, mlx->img->ptr);
	ft_memdel((void**)&(mlx->img));
}

void	flush_img(t_img *img)
{
	ft_bzero(img->px, WIDTH * HEIGHT * sizeof(unsigned int));
}

t_img	*create_img(t_mlx *mlx)
{
	int bpp;
	int endi;

	if (!(mlx->img = malloc(sizeof(t_img))))
		return (NULL);
	if (!(mlx->img->ptr = mlx_new_image(mlx->iptr, WIDTH, HEIGHT)))
	{
		del_img(mlx);
		return (NULL);
	}
	mlx->img->px = mlx_get_data_addr(mlx->img->ptr, \
						&bpp, &mlx->img->lsize, &endi);
	mlx->img->lsize = mlx->img->lsize / sizeof(unsigned int);
	return (mlx->img);
}

void	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	((int*)img->px)[x + (y * img->lsize)] = color;
}
