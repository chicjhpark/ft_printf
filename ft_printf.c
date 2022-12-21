/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 08:20:16 by jaehpark          #+#    #+#             */
/*   Updated: 2021/02/28 23:47:16 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	sort_spec(t_tag *tag)
{
	if (*tag->fmt == 'd' || *tag->fmt == 'i' || *tag->fmt == 'u' ||
		*tag->fmt == 'x' || *tag->fmt == 'X' || *tag->fmt == 'p')
		ft_printf_nbr(tag);
	else if (*tag->fmt == 'c')
		ft_printf_char(tag);
	else if (*tag->fmt == 's')
		ft_printf_str(tag);
	else if (*tag->fmt == '%')
		ft_printf_char(tag);
}

void	sort_tag(t_tag *tag)
{
	if (tag->minus == 1 || (tag->dot == 1 && *tag->fmt != 'c' &&
				*tag->fmt != '%'))
		tag->zero = 0;
	if (tag->width > tag->prec && tag->width > tag->size)
	{
		if (tag->prec > tag->size)
		{
			if (tag->minus == 1)
				tag->rspace = tag->width - tag->prec;
			else
				tag->lspace = tag->width - tag->prec;
		}
		else
		{
			if (tag->minus == 1)
				tag->rspace = tag->width - tag->size;
			else
				tag->lspace = tag->width - tag->size;
		}
	}
	if (tag->size >= tag->prec && tag->prec != 0 && *tag->fmt != 's')
		tag->prec = -1;
	else if (tag->prec > tag->size && *tag->fmt != 's')
		tag->prec -= tag->size;
}

void	check_type(t_tag *tag)
{
	if (*tag->fmt == 'd' || *tag->fmt == 'i')
		tag->nbr = va_arg(tag->ap, int);
	else if (*tag->fmt == 'x' || *tag->fmt == 'X')
		tag->pnbr = (unsigned int)va_arg(tag->ap, int);
	else if (*tag->fmt == 'u')
		tag->nbr = (unsigned int)va_arg(tag->ap, int);
	else if (*tag->fmt == 'c')
		tag->c = (char)va_arg(tag->ap, int);
	else if (*tag->fmt == 's')
	{
		tag->str = (char *)va_arg(tag->ap, const char *);
		digits_size_str(tag);
	}
	else if (*tag->fmt == 'p')
	{
		tag->pnbr = (unsigned long long)va_arg(tag->ap, void *);
		tag->width -= 2;
	}
	else if (*tag->fmt == '%')
		tag->c = '%';
	if (*tag->fmt != 's')
		digits_size(tag);
}

void	sort_format(t_tag *tag)
{
	tag->res = 0;
	while (*tag->fmt != '\0')
	{
		while (*tag->fmt != '%' && *tag->fmt != '\0')
			tag->res += ft_putchar(*tag->fmt++);
		if (*tag->fmt == '%')
		{
			init_tag(tag);
			while (*++tag->fmt != '\0' && strchr_spec(*tag->fmt) == 0)
				check_tag(tag);
			if (strchr_spec(*tag->fmt) != 0)
			{
				check_type(tag);
				sort_tag(tag);
				sort_spec(tag);
			}
			if (*tag->fmt != '\0')
				tag->fmt++;
		}
	}
}

int		ft_printf(const char *format, ...)
{
	t_tag	tag;

	if (format == NULL)
		return (-1);
	va_start(tag.ap, format);
	tag.fmt = (char *)format;
	sort_format(&tag);
	va_end(tag.ap);
	return (tag.res);
}
