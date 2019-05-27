/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 22:47:53 by chermist          #+#    #+#             */
/*   Updated: 2019/05/04 23:30:11 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		low_alpha(char c)
{
	if (c >= 'a' && c <= 'f')
		return (1);
	else
		return (0);
}

static int		big_alpha(char c)
{
	if (c >= 'A' && c <= 'F')
		return (1);
	else
		return (0);
}

static int		is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

unsigned long	atoi_move_hex(char **str)
{
	unsigned long a;

	a = 0;
	while ((**str >= 9 && **str <= 13) || **str == ' ')
		(*str)++;
	if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X'))
		(*str) += 2;
	if (!is_number(**str) && !low_alpha(**str) && !big_alpha(**str))
		return (0);
	while (is_number(**str) || low_alpha(**str) || big_alpha(**str))
	{
		if (low_alpha(**str))
			a = (is_number(**str)) ? \
				a * 16 + (*(*str)++ - 48) : a * 16 + (*(*str)++ + 10 - 'a');
		else
			a = (is_number(**str)) ? \
				a * 16 + (*(*str)++ - 48) : a * 16 + (*(*str)++ + 10 - 'A');
	}
	return (a);
}

int				atoi_move(char **str)
{
	int					sign;
	int					len;
	unsigned long long	num;

	num = 0;
	while (!(len = 0) && ft_isspace(**str))
		(*str)++;
	sign = (**str == '-') ? -1 : 1;
	(**str == '-' || **str == '+') ? (*str)++ : *str;
	while (**str == '0')
		(*str)++;
	while (ft_isdigit(**str) && (++len < 21))
		num = num * 10 + (*((*str)++) - '0');
	if (sign > 0 && (len > 19 || num > 9223372036854775807))
		return (-1);
	if (sign < 0 && (len > 19 || num > 9223372036854775808ULL))
		return (0);
	return (sign * num);
}
