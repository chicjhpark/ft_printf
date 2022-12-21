/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_di.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 08:20:00 by jaehpark          #+#    #+#             */
/*   Updated: 2021/03/01 00:11:06 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_nbr2(t_tag *tag)
{
	if (tag->nbr < 0)
		tag->res += ft_putchar('-');
	while (tag->lspace-- > 0)
		tag->res += ft_putchar('0');
	if (*tag->fmt == 'p')
		tag->res += write(1, "0x", 2);
	while (tag->prec-- > 0)
		tag->res += ft_putchar('0');
	if (*tag->fmt == 'x' || *tag->fmt == 'X' || *tag->fmt == 'p')
		tag->res += ft_putstr(ft_xtoa_sign(tag));
	else
		tag->res += ft_putstr(ft_itoa_sign(tag));
	while (tag->rspace-- > 0)
		tag->res += ft_putchar(' ');
}

void	ft_printf_nbr(t_tag *tag)
{
	if (tag->nbr < 0)
	{
		tag->lspace -= 1;
		tag->rspace -= 1;
	}
	if (tag->zero != 1)
		while (tag->lspace-- > 0)
			tag->res += ft_putchar(' ');
	if (tag->nbr == 0 && tag->pnbr == 0 && tag->dot == 1 && tag->prec == 0)
	{
		if (*tag->fmt == 'p')
		{
			if (tag->pnbr == 0 && tag->minus == 0 && tag->width > 0)
				tag->res += ft_putchar(' ');
			tag->res += write(1, "0x", 2);
			while (tag->minus == 1 && tag->width > 0 &&
					(tag->rspace-- > 0 || tag->size-- > 0))
				tag->res += ft_putchar(' ');
		}
		else if (tag->width > 0)
			while (tag->rspace-- > 0 || tag->size-- > 0)
				tag->res += ft_putchar(' ');
		return ;
	}
	ft_printf_nbr2(tag);
}

void	ft_printf_char(t_tag *tag)
{
	if (tag->minus == 0)
		tag->lspace = tag->width - tag->size;
	else
		tag->rspace = tag->width - tag->size;
	if (tag->zero == 1)
		while (tag->lspace-- > 0)
			tag->res += ft_putchar('0');
	while (tag->lspace-- > 0)
		tag->res += ft_putchar(' ');
	tag->res += ft_putchar(tag->c);
	while (tag->rspace-- > 0)
		tag->res += ft_putchar(' ');
}

void	ft_printf_str(t_tag *tag)
{
	if (tag->dot == 1 && tag->prec <= 0 && tag->width <= 0)
		return ;
	else if (tag->dot == 1 && tag->size > tag->prec)
	{
		if (tag->prec >= 0)
			tag->size = tag->prec;
		else
			tag->size = 0;
	}
	if (tag->width > 0 || *tag->str == '\0')
	{
		if (tag->minus == 1)
			tag->rspace = tag->width - tag->size;
		else
			tag->lspace = tag->width - tag->size;
	}
	if (tag->zero == 1)
		while (tag->lspace-- > 0)
			tag->res += ft_putchar('0');
	while (tag->lspace-- > 0)
		tag->res += ft_putchar(' ');
	while (tag->size-- > 0)
		tag->res += ft_putchar(*tag->str++);
	while (tag->rspace-- > 0)
		tag->res += ft_putchar(' ');
}
