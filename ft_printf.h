/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 08:21:04 by jaehpark          #+#    #+#             */
/*   Updated: 2021/03/01 01:55:54 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef unsigned long long	t_ulint;
typedef long long			t_lint;

typedef struct	s_tag
{
	va_list		ap;
	char		*fmt;
	char		*str;
	char		c;
	int			minus;
	int			zero;
	int			width;
	int			prec;
	int			size;
	int			dot;
	int			res;
	t_lint		nbr;
	t_ulint		pnbr;
	int			lspace;
	int			rspace;
}				t_tag;

int				ft_printf(const char *format, ...);
int				ft_putchar(char c);
int				ft_putstr(char *s);
int				ft_isdigit(char c);
int				strchr_spec(char c);
char			*ft_itoa_sign(t_tag *tag);
char			*ft_xtoa_sign(t_tag *tag);
void			digits_size(t_tag *tag);
void			digits_size_str(t_tag *tag);
void			dot_check(t_tag *tag);
void			hex_check(t_tag *tag);
void			sort_width_prec(t_tag *tag);
void			init_tag(t_tag *tag);
void			check_tag(t_tag *tag);
void			ft_printf_nbr(t_tag *tag);
void			ft_printf_nbr2(t_tag *tag);
void			ft_printf_char(t_tag *tag);
void			ft_printf_str(t_tag *tag);

#endif
