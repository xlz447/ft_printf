/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 22:37:25 by xzhu              #+#    #+#             */
/*   Updated: 2018/07/29 22:37:27 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	buf_flush(t_pf *p)
{
	write(1, p->buf, p->bufsize);
	p->bufsize = 0;
}

void	buf_s(t_pf *p, const void *s, short n)
{
	unsigned char	*src;
	short			empty;

	src = (unsigned char *)s;
	while (p->bufsize + n > BUFF_SIZE)
	{
		empty = BUFF_SIZE - p->bufsize;
		while (empty-- && n--)
		{
			p->buf[p->bufsize++] = *src++;
			p->totallen++;
		}
		buf_flush(p);
	}
	while (n--)
	{
		p->buf[p->bufsize++] = *src++;
		p->totallen++;
	}
}

void	buf_c(t_pf *p, const char c)
{
	if (p->bufsize + 1 > BUFF_SIZE)
		buf_flush(p);
	p->buf[p->bufsize++] = c;
	p->totallen++;
}

void	setup_padding(t_pf *p)
{
	char	*tmp;
	while ((int)ft_strlen(p->temp) < p->min_w)
	{
		if (p->left == 1)
			tmp = ft_strjoin(p->temp, " ");
		else
			tmp = ft_strjoin(" ", p->temp);
		free(p->temp);
		p->temp = tmp;
	}
}

pick_me		dispatch_table(char c)
{
	static pick_me	*f;

	if (!f)
		f = ft_memalloc(sizeof(*f) * 123);
	f['d'] = &ft_printf_diuox;
	f['i'] = &ft_printf_diuox;
	f['u'] = &ft_printf_diuox;
	f['o'] = &ft_printf_diuox;
	f['x'] = &ft_printf_diuox;
	f['c'] = &ft_printf_c;
	f['s'] = &ft_printf_s;
	f['p'] = &ft_printf_p;
	f['X'] = &ft_printf_diuox;
	f['D'] = &ft_printf_diuox;
	f['U'] = &ft_printf_diuox;
	f['O'] = &ft_printf_diuox;
	f['C'] = &ft_printf_c;
	f['S'] = &ft_printf_s;
	return (f[(int)c]);
}

static void	clearall(t_pf *p)
{
	p->type = 0;
	p->len = 0;
	p->zero = 0;
	p->left = 0;
	p->plus = 0;
	p->hash = 0;
	p->space = 0;
	p->pre = -1;
	p->min_w = -1;
	p->temp = "";
}

int dispatch(char *s, va_list ap)
{
	t_pf			p;
	union u_type	t;
	pick_me			f;
	int				i;

	i = 0;
	ft_bzero(&p, sizeof(p));
	while (s[i])
	{
		if (s[i] == '%')
		{
			clearall(&p);
			i = setup(&p, s, i + 1);
			//printf("After parsing i is now:%i \ntype: %c\nlen: %c\nzero: %i\nleft: %i\nplus: %i\nhash: %i\nspace: %i\nprecision: %i\nmin_width: %i\ntemp: %s\n", i, p.type, p.len, p.zero, p.left, p.plus, p.hash, p.space, p.pre, p.min_w, p.temp);
			if (!s[i])
				break ;
			f = dispatch_table(p.type);
			if (f != NULL)
				f(&p, &t, ap);
			else
				ft_printf_c(&p, &t, ap);
		}
		else
			buf_c(&p, s[i]);
		i++;
	}
	buf_flush(&p);
	return (p.totallen);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		out;

	va_start(ap, format);
	out = dispatch((char*)format, ap);
	va_end(ap);
	return (out);
}
