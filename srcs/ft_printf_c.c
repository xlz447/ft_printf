/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:39:32 by xzhu              #+#    #+#             */
/*   Updated: 2018/08/11 23:48:49 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putwchar(t_pf *p, wchar_t c)
{
	if (c <= 0x7F)
		buf_c(p, c);
	else if (c <= 0x7FF)
	{
		buf_c(p, (c >> 6) + 0xC0);
		buf_c(p, (c & 0x3F) + 0x80);
	}
	else if (c <= 0xFFFF)
	{
		buf_c(p, (c >> 12) + 0xE0);
		buf_c(p, ((c >> 6) & 0x3F) + 0x80);
		buf_c(p, (c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		buf_c(p, (c >> 18) + 0xF0);
		buf_c(p, ((c >> 12) & 0x3F) + 0x80);
		buf_c(p, ((c >> 6) & 0x3F) + 0x80);
		buf_c(p, (c & 0x3F) + 0x80);
	}
}

static int	lc_size(wchar_t lc)
{
	int len;

	if (lc <= 0x7F)
		len = 1;
	else if (lc <= 0x7FF)
		len = 2;
	else if (lc <= 0xFFFF)
		len = 3;
	else if (lc <= 0x10FFFF)
		len = 4;
	else
		len = 0;
	return (len);
}

void		ft_printf_lc(t_pf *p, union u_type *t, va_list ap)
{
	int	len;
	int i;

	i = -1;
	t->lc = (wchar_t)va_arg(ap, wint_t);
	len = lc_size(t->lc);
	if (p->left == 1)
		ft_putwchar(p, t->lc);
	while (++i < p->min_w - 1)
	{
		if (p->zero == 1)
			buf_c(p, '0');
		else
			buf_c(p, ' ');
	}
	if (p->left != 1)
		ft_putwchar(p, t->lc);
}

void		ft_printf_c(t_pf *p, union u_type *t, va_list ap)
{
	int i;

	i = -1;
	if (p->type == 'c' || p->type == 'C')
		t->c = (unsigned char)va_arg(ap, int);
	else
		t->c = p->temp[0];
	if (p->left == 1)
		buf_c(p, t->c);
	while (++i < p->min_w - 1)
	{
		if (p->zero == 1)
			buf_c(p, '0');
		else
			buf_c(p, ' ');
	}
	if (p->left != 1)
		buf_c(p, t->c);
}
