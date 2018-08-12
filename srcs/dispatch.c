/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:17:07 by xzhu              #+#    #+#             */
/*   Updated: 2018/08/11 23:49:13 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_pick_me	dispatch_table(char c)
{
	static t_pick_me	*f;

	if (!f)
		f = ft_memalloc(sizeof(*f) * 123);
	f['d'] = &ft_printf_diuoxb;
	f['i'] = &ft_printf_diuoxb;
	f['u'] = &ft_printf_diuoxb;
	f['o'] = &ft_printf_diuoxb;
	f['x'] = &ft_printf_diuoxb;
	f['c'] = &ft_printf_c;
	f['s'] = &ft_printf_s;
	f['p'] = &ft_printf_p;
	f['X'] = &ft_printf_diuoxb;
	f['D'] = &ft_printf_diuoxb;
	f['U'] = &ft_printf_diuoxb;
	f['O'] = &ft_printf_diuoxb;
	f['C'] = &ft_printf_c;
	f['S'] = &ft_printf_ls;
	f['b'] = &ft_printf_diuoxb;
	f['B'] = &ft_printf_diuoxb;
	return (f[(int)c]);
}

static void			clearall(t_pf *p)
{
	p->type = 0;
	p->len = 0;
	p->zero = 0;
	p->left = 0;
	p->plus = 0;
	p->hash = 0;
	p->space = 0;
	p->apos = 0;
	p->pre = -1;
	p->min_w = -1;
	p->dollor = -1;
	p->temp = "";
}

/*
**	printf("After parsing i is now:%i \ntype: %c\nlen: %c\nzero: %i\nleft: %i\n
**	plus: %i\nhash: %i\nspace: %i\nprecision: %i\nmin_width: %i\ndollor: %i\n
**	temp: %s\n", i, p.type, p.len, p.zero, p.left, p.plus, p.hash, p.space,
**	p.pre, p.min_w, p.dollor, p.temp);
*/

static int			check_color(t_pf *p, char *s, int i)
{
	if (!ft_strncmp(s + i, "{noc}", strlen("{noc}")))
		buf_s(p, KNRM, strlen(KNRM));
	else if (!ft_strncmp(s + i, "{red}", strlen("{red}")))
		buf_s(p, KRED, strlen(KRED));
	else if (!ft_strncmp(s + i, "{green}", strlen("{green}")))
		buf_s(p, KGRN, strlen(KGRN));
	else if (!ft_strncmp(s + i, "{yellow}", strlen("{yellow}")))
		buf_s(p, KYEL, strlen(KYEL));
	else if (!ft_strncmp(s + i, "{blue}", strlen("{blue}")))
		buf_s(p, KBLU, strlen(KBLU));
	else if (!ft_strncmp(s + i, "{magenta}", strlen("{magenta}")))
		buf_s(p, KMAG, strlen(KMAG));
	else if (!ft_strncmp(s + i, "{cyan}", strlen("{cyan}")))
		buf_s(p, KCYN, strlen(KCYN));
	else if (!ft_strncmp(s + i, "{white}", strlen("{white}")))
		buf_s(p, KWHT, strlen(KWHT));
	else
		p->col[0] = 0;
	p->col[1] |= p->col[0];
	while (p->col[0] && s[i] && s[i] != '}')
		i++;
	return (i);
}

static int			dispatch_helper(t_pf *p, char *s, va_list ap[2], int i)
{
	t_pick_me		f;

	clearall(p);
	i = setup(p, s, i + 1, ap[0]);
	if (!s[i])
		return (-42);
	f = dispatch_table(p->type);
	if (p->dollor != -1)
	{
		va_end(ap[0]);
		va_copy(ap[0], ap[1]);
		while (p->dollor-- > 1)
			va_arg(ap[0], int);
	}
	if (f != NULL)
		f(p, &(p->t), ap[0]);
	else
		ft_printf_c(p, &(p->t), ap[0]);
	return (i);
}

int					dispatch(t_pf *p, char *s, va_list ap[2], int fd)
{
	int				i;

	i = -1;
	p->fd = fd;
	while (s[++i])
	{
		if (s[i] == '%')
		{
			i = dispatch_helper(p, s, ap, i);
			if (i == -42)
				break ;
		}
		else
		{
			p->col[0] = (s[i] == '{') ? 1 : 0;
			if (s[i] == '{')
				i = check_color(p, s, i);
			if (!(p->col[0]))
				buf_c(p, s[i]);
		}
	}
	if (p->col[1])
		buf_s(p, KNRM, strlen(KNRM));
	buf_flush(p);
	return (p->totallen);
}
