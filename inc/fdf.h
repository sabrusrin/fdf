/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:05:00 by chermist          #+#    #+#             */
/*   Updated: 2019/05/04 22:50:37 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "./mlx_keys.h"

# define ABS(Value) (Value < 0) ? (-Value) : (Value)
# define WIDTH  	2560
# define HEIGHT 	1480

typedef struct		s_mtx
{
	int				**map;
	int				**color;
	int				width;
	int				height;
	int				scale;
}					t_mtx;

typedef struct		s_img
{
	void			*ptr;
	void			*px;
	int				lsize;
}					t_img;

typedef	union		u_color
{
	int				mono;
	unsigned char	rgb[4];
}					t_color;

typedef	struct		s_pt
{
	int				x;
	int				y;
	int				z;
	t_color			color;
}					t_pt;

typedef struct		s_view
{
	float			offsetx;
	float			offsety;
	float			hz;
	float			scale;
	int				clr;
	void			(*line)(t_pt st, t_pt end, t_img *img);
}					t_view;

typedef struct		s_bres
{
	int				signx;
	int				signy;
	int				dx;
	int				dy;
	int				err[2];
}					t_bres;

typedef struct		s_mlx
{
	void			*iptr;
	void			*wptr;
	t_img			*img;
	t_view			*view;
	t_mtx			*mtx;
	t_pt			*(*proj)(t_pt *pt, t_view *view);
}					t_mlx;

double				percent(int start, int end, int current);
void				err_handle(char *reason);
void				set_default(t_mlx *mlx);
void				draw_line(t_pt p1, t_pt p2, t_img *img);
void				dot_draw(t_pt p1, t_pt p2, t_img *img);
void				parse(t_mtx *mtx, const char *f_name);
int					atoi_move(char **str);
unsigned long		atoi_move_hex(char **str);
void				draw(t_mtx *mtx, t_mlx *mlx);
void				flush_img(t_img *img);
void				del_img(t_mlx *mlx);
void				do_init(t_mlx *mlx);
void				purge(t_mlx *mlx);
t_pt				*iso(t_pt *pt, t_view *view);
void				put_pixel_to_img(t_img *img, int x, int y, int color);
void				bresenham(t_pt start, t_pt end, t_img *img);
t_img				*create_img(t_mlx *mlx);
t_pt				*parallel(t_pt *pt, t_view *view);
void				set_default(t_mlx *mlx);
void				*ft_iarrdel(void **res, int y);

#endif
