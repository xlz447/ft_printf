/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:39:44 by xzhu              #+#    #+#             */
/*   Updated: 2018/08/03 13:39:45 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			calc_precision(wchar_t *str, int precision, size_t new_prec)
{
	if (*str == '\0' || precision == 0)
		return (new_prec);
	else if (*str <= 0x007F)
		return (calc_precision(str + 1, precision - 1, new_prec + 1));
	else if (*str <= 0x07FF && precision >= 2)
		return (calc_precision(str + 1, precision - 2, new_prec + 2));
	else if (*str <= 0xFFFF && precision >= 3)
		return (calc_precision(str + 1, precision - 3, new_prec + 3));
	else if (*str <= 0x10FFFF && precision >= 4)
		return (calc_precision(str + 1, precision - 4, new_prec + 4));
	else
		return (new_prec);
}

size_t	pf_wcharlen(wchar_t wc)
{
	if (wc <= 0x007F)
		return (1);
	else if (wc <= 0x07FF)
		return (2);
	else if (wc <= 0xFFFF)
		return (3);
	else if (wc <= 0x10FFFF)
		return (4);
	return (0);
}

size_t	pf_wstrlen(wchar_t *wstr)
{
	size_t	wlen;

	wlen = 0;
	while (*wstr != L'\0')
	{
		wlen += pf_wcharlen(*wstr);
		wstr++;
	}
	return (wlen);
}

void	ft_putnwstr(t_pf *p, wchar_t *str, size_t len)
{
	size_t	i;

	i = 0;
	while (*str && i < len)
	{
		if (*str <= 0x7F)
			i++;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		if (i <= len)
			ft_putwchar(p, *str++);
	}
}

void	ft_printf_s(t_pf *p, union u_type *t, va_list ap)
{
	int i;
	int len;

	i = -1;
	if (p->len == 4)
	{
		t->ls = va_arg(ap, wchar_t *);
		if (!t->ls)
			t->ls = L"(null)";
		len = (int)pf_wstrlen(t->ls);
		if (p->pre != -1)
			p->pre = (int)calc_precision(t->ls, p->pre, 0);
		if (p->pre < 0)
			p->pre = len;
		p->pre = (p->pre > len) ? len : p->pre;
		len = (p->pre > -1) ? p->pre : len;
		if (p->left == 1)
			ft_putnwstr(p, t->ls, len);
		while (++i < (int)(p->min_w - len))
		{
			if (p->zero == 1)
				buf_c(p, '0');
			else
				buf_c(p, ' ');
		}
		if (p->left != 1)
			ft_putnwstr(p, t->ls, len);
	}
	else
	{
		t->s = va_arg(ap, char*);
		if (!t->s && p->pre == -1)
			t->s = "(null)";
		else if (!t->s)
			t->s = "";
		else if (p->pre != -1)
		{
			t->s = ft_strsub(t->s, 0, p->pre);
		}
		if (p->left == 1)
			buf_s(p, t->s, ft_strlen(t->s));
		while (++i < (int)(p->min_w - ft_strlen(t->s)))
		{
			if (p->zero == 1)
				buf_c(p, '0');
			else
				buf_c(p, ' ');
		}
		if (p->left != 1)
			buf_s(p, t->s, ft_strlen(t->s));
	}
}
