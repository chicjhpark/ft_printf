/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_calc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 04:53:10 by jaehpark          #+#    #+#             */
/*   Updated: 2021/03/01 01:53:48 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_xtoa_sign(t_tag *tag)
{
	char	*s;
	int		upp;

	if (!(s = (char *)malloc(sizeof(char) * (tag->size + 1))))
		return (NULL);
	s[tag->size] = '\0';
	upp = 7;
	if (*tag->fmt == 'x' || *tag->fmt == 'p')
		upp += 32;
	while (tag->size-- > 0)
	{
		if (tag->pnbr % 16 >= 10)
			s[tag->size] = (tag->pnbr % 16) + '0' + upp;
		else
			s[tag->size] = (tag->pnbr % 16) + '0';
		tag->pnbr /= 16;
	}
	return (s);
}

void	dot_check(t_tag *tag)
{
	tag->dot = 1;
	tag->prec = 0;
}

void	hex_check(t_tag *tag)
{
	unsigned long long	n;

	n = tag->pnbr;
	while (n >= 16)
	{
		n /= 16;
		tag->size++;
	}
}
