/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chermist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 11:32:02 by chermist          #+#    #+#             */
/*   Updated: 2019/04/24 15:47:06 by chermist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		words;
	int		j;
	int		k;

	if (!s || !(str = (char**)malloc(sizeof(*str) *
			((words = ft_wcount(s, c)) + 1))))
		return (NULL);
	k = -1;
	while (++k < words)
	{
		while (*s == c)
			s++;
		j = 0;
		while (s[j] != c && s[j] != '\0')
			j++;
		if (!(str[k] = ft_strnew(j)))
			return (ft_arrdel((void**)str));
		else if (!(j = 0))
			while (*s != c && *s)
				str[k][j++] = *s++;
	}
	str[k] = 0;
	return (str);
}
