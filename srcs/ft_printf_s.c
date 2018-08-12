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

static void	ft_putnwstr(t_pf *p, wchar_t *str, int len)
{
	int	i;

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

static int	ls_pre(wchar_t *str, int pre, int temp)
{
	if (*str == '\0' || pre == 0)
		return (temp);
	else if (*str <= 0x007F)
		return (ls_pre(str + 1, pre - 1, temp + 1));
	else if (*str <= 0x07FF && pre >= 2)
		return (ls_pre(str + 1, pre - 2, temp + 2));
	else if (*str <= 0xFFFF && pre >= 3)
		return (ls_pre(str + 1, pre - 3, temp + 3));
	else if (*str <= 0x10FFFF && pre >= 4)
		return (ls_pre(str + 1, pre - 4, temp + 4));
	else
		return (temp);
}

static int	ls_size(wchar_t *ls)
{
	int	len;

	len = 0;
	while (*ls != L'\0')
	{
		if (*ls <= 0x007F)
			len += 1;
		else if (*ls <= 0x07FF)
			len += 2;
		else if (*ls <= 0xFFFF)
			len += 3;
		else if (*ls <= 0x10FFFF)
			len += 4;
		ls++;
	}
	return (len);
}

void		ft_printf_ls(t_pf *p, union u_type *t, va_list ap)
{
	int i;
	int len;

	i = -1;
	t->ls = va_arg(ap, wchar_t *);
	if (!t->ls)
		t->ls = L"(null)";
	len = (int)ls_size(t->ls);
	if (p->pre != -1)
		p->pre = (int)ls_pre(t->ls, p->pre, 0);
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

void		ft_printf_s(t_pf *p, union u_type *t, va_list ap)
{
	int i;

	i = -1;
	t->s = va_arg(ap, char*);
	if (!t->s && p->pre == -1)
		t->s = "(null)";
	else if (!t->s)
		t->s = "";
	else if (p->pre > -1)
		t->s = ft_strsub(t->s, 0, p->pre);
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
