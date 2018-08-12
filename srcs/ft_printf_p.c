/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:42:33 by xzhu              #+#    #+#             */
/*   Updated: 2018/08/03 13:42:38 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	p_helper(t_pf *p, union u_type *t, char out[], int *i)
{
	int digits;

	digits = 0;
	if (t->p == 0 && p->pre == -1)
		out[--(*i)] = '0';
	while (t->p > 0 && --(*i) > 1)
	{
		if (p->apos && digits && !(digits % 3))
			out[(*i)--] = ',';
		if (t->p % 16 == 15)
			out[*i] = 'f';
		else if (t->p % 16 == 14)
			out[*i] = 'e';
		else if (t->p % 16 == 13)
			out[*i] = 'd';
		else if (t->p % 16 == 12)
			out[*i] = 'c';
		else if (t->p % 16 == 11)
			out[*i] = 'b';
		else if (t->p % 16 == 10)
			out[*i] = 'a';
		else
			out[*i] = t->p % 16 + '0';
		(t->p /= 16) && (digits++);
	}
}

void		ft_printf_p(t_pf *p, union u_type *t, va_list ap)
{
	char	out[19];
	int		i;
	int		j;

	t->p = va_arg(ap, unsigned long long int);
	out[0] = '0';
	out[1] = 'x';
	out[18] = '\0';
	i = 18;
	p_helper(p, t, out, &i);
	while ((17 - --i) < p->pre)
		out[i] = '0';
	while (p->zero && 17 - i < p->min_w - 2)
		out[i--] = '0';
	j = 2;
	if (i != 1)
		while (++i < 19)
			out[j++] = out[i];
	if (p->left == 1)
		buf_s(p, out, ft_strlen(out));
	i = -1;
	while (++i < p->min_w - (j - 1))
		buf_c(p, ' ');
	if (p->left != 1)
		buf_s(p, out, ft_strlen(out));
}
