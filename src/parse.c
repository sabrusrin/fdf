/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <chermist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:48:25 by chermist          #+#    #+#             */
/*   Updated: 2019/05/04 18:24:36 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_size(t_mtx *mtx, int fd)
{
	char	*line;
	int		len;
	int		gnl;

	len = 0;
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl == -1)
			err_handle("Invalid file.\n");
		(mtx->height)++;
		len += ft_wcount(line, ' ');
		free(line);
	}
	if (!len)
		err_handle("Invalid file.\n");
	mtx->width += len / mtx->height;
}

void	save_data(t_mtx *mtx, char **line)
{
	int		*itmp;
	int		*ctmp;

	itmp = *(mtx->map);
	ctmp = *(mtx->color);
	while (**line)
	{
		**mtx->map = atoi_move(line);
		(*(mtx->map))++;
		if (**line == ',')
		{
			(*line)++;
			**mtx->color = (int)atoi_move_hex(line);
		}
		else if (**line != ',')
			**mtx->color = 0xffffff;
		(*(mtx->color))++;
	}
	*(mtx->map) = itmp;
	*(mtx->color) = ctmp;
}

void	parse_file(t_mtx *mtx, int fd)
{
	char	*line;
	char	*tmp;
	int		gnl;

	while ((gnl = get_next_line(fd, &line)))
	{
		tmp = line;
		if (gnl == -1)
			err_handle("Invalid file.\n");
		if (!(*(mtx->map) = (int*)malloc(sizeof(int) * mtx->width)))
		{
			ft_arrdel((void**)(mtx->map));
			exit(1);
		}
		if (!(*(mtx->color) = (int*)malloc(sizeof(int) * mtx->width)))
		{
			ft_arrdel((void**)(mtx->color));
			err_handle("Usage: ./fdf *.fdf\n");
		}
		save_data(mtx, &line);
		free(tmp);
		(mtx->map)++;
		(mtx->color)++;
	}
}

void	parse(t_mtx *mtx, const char *f_name)
{
	int		fd;
	int		**tmp;
	int		**ctmp;

	if ((fd = open(f_name, O_RDONLY)) < 0)
		err_handle("Error opennig file\n");
	mtx->height = 0;
	mtx->width = 0;
	get_size(mtx, fd);
	close(fd);
	if (!(mtx->map = (int**)malloc(sizeof(int *) * mtx->height)))
		exit(1);
	if (!(mtx->color = (int**)malloc(sizeof(int *) * mtx->height)))
		exit(1);
	tmp = mtx->map;
	ctmp = mtx->color;
	if ((fd = open(f_name, O_RDONLY)) < 0)
		err_handle("Error openning file\n");
	parse_file(mtx, fd);
	close(fd);
	mtx->map = tmp;
	mtx->color = ctmp;
}
