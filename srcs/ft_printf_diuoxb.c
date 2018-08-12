/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diuoxb.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:39:10 by xzhu              #+#    #+#             */
/*   Updated: 2018/08/03 13:39:12 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	nbr_helper2(t_pf *p, uintmax_t ag_mx[2], int i[5], char *t_r[2])
{
	char	next[3];
	int		digits;

	p->temp = ft_strnew(1);
	if (!ag_mx[0])
	{
		p->temp[0] = '0';
		if (p->pre == 0)
			p->temp[0] = '\0';
	}
	digits = 0;
	next[2] = '\0';
	while (ag_mx[0] > 0)
	{
		next[0] = t_r[1][ag_mx[0] % i[1]];
		next[1] = '\0';
		if (ft_strchr("diuob", p->type) && p->apos && digits % 3 == 0 && digits)
			next[1] = ',';
		t_r[0] = ft_strjoin(next, p->temp);
		free(p->temp);
		p->temp = t_r[0];
		if (p->type == 'X' && (ag_mx[0] % i[1] > 9))
			p->temp[0] -= 32;
		(ag_mx[0] /= i[1]) && (digits++);
	}
}

static void	nbr_helper1(t_pf *p, uintmax_t ag_mx[2], int i[5])
{
	if (ag_mx[1] * 2 && ag_mx[0] >= ag_mx[1] * 2)
		ag_mx[0] = ag_mx[0] % ((uintmax_t)1 << (i[0] + 1));
	if (ag_mx[0] >= ag_mx[1])
	{
		i[2] = 1;
		if (i[0] + 1 < 64)
			ag_mx[0] = ((uintmax_t)1 << (i[0] + 1)) - ag_mx[0];
		else
			ag_mx[0] = (18446744073709551615U - ag_mx[0]) + 1;
	}
	if (i[2] || (!i[2] && (p->space || p->plus)))
		i[3] = 1;
}

void		setup_nbr(t_pf *p, uintmax_t ag_mx[2], int i[5], char *t_r[2])
{
	ag_mx[1] = (i[0] < 64) ? ((uintmax_t)1 << (i[0])) : 18446744073709551615U;
	if (ft_strchr("di", p->type))
		nbr_helper1(p, ag_mx, i);
	else if (ag_mx[0] == 18446744073709551615U && ag_mx[0] == ag_mx[1])
	{
		ag_mx[2] = ag_mx[0];
		if (p->type == 'u' && !p->apos)
			p->temp = ft_strjoin("18446744073709551615", "");
		else if (p->type == 'u' && p->apos)
			p->temp = ft_strjoin("18,446,744,073,709,551,615", "");
		else if (p->type == 'o')
			p->temp = ft_strjoin("1777777777777777777777", "");
		else if (p->type == 'x')
			p->temp = ft_strjoin("ffffffffffffffff", "");
		else if (p->type == 'X')
			p->temp = ft_strjoin("FFFFFFFFFFFFFFFF", "");
		else if (p->type == 'b')
			p->temp = ft_strjoin(
		"1111111111111111111111111111111111111111111111111111111111111111", "");
		return ;
	}
	else
		ag_mx[0] = ag_mx[0] % ag_mx[1];
	ag_mx[2] = ag_mx[0];
	nbr_helper2(p, ag_mx, i, t_r);
}

/*
**	set up the power of the largest possible number to print
**	2-> h, 1 -> hh, 4 ->l, 5 ->ll ,6->j, 7->z
*/

void		setup_pow_base_pad(t_pf *p, int i[5])
{
	if (p->len == 0)
		i[0] = 8 * (int)sizeof(int) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 2)
		i[0] = 8 * (int)sizeof(short) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 1)
		i[0] = 8 * (int)sizeof(char) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 4)
		i[0] = 8 * (int)sizeof(long) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 5)
		i[0] = 8 * (int)sizeof(long long) -
		((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 6)
		i[0] = 8 * (int)sizeof(intmax_t) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 7)
		i[0] = 8 * (int)sizeof(size_t) - ((ft_strchr("di", p->type)) ? 1 : 0);
	if (p->hash)
		i[3] = (p->type == 'o') + 2 * (ft_strchr("xX", p->type) != NULL);
	if (ft_strchr("xX", p->type))
		i[1] = 16;
	else if (p->type == 'o')
		i[1] = 8;
	else if (ft_strchr("diu", p->type))
		i[1] = 10;
	else if (p->type == 'b' || p->type == 'B')
		i[1] = 2;
}

/*
**	ag_mx[3] arg ; max ; copy of arg
**	t_r[2] temp; reference
**	inf[6] pow; base; neg; padding; is_zero; to_ret
**	inf[0] the power of the result, depending on the length field
**	inf[1] the base the result is going to be
**	inf[2] if this is a negative or not(d or i only)
**	inf[3] the number of prefix characters of this number(sign, 0x etc)
**	pow_base_pad set up the max power, base, and padding according to the flags
**	setup_nbr set up the number to print out(without signs)
**	setup_zero add the zeros for the precision and the min_width
**	setup_prefix put on the prefix(+, - ,  , 0, 0x, 0X) b4 the number
*/

void		ft_printf_diuoxb(t_pf *p, union u_type *t, va_list ap)
{
	uintmax_t	ag_mx[3];
	char		*t_r[2];
	int			inf[6];

	(void)t;
	t_r[1] = "0123456789abcdef";
	ag_mx[0] = va_arg(ap, uintmax_t);
	inf[0] = 1;
	inf[1] = 0;
	inf[2] = 0;
	inf[3] = 0;
	setup_pow_base_pad(p, inf);
	setup_nbr(p, ag_mx, inf, t_r);
	setup_zero(p, t_r, inf);
	setup_prefix(p, ag_mx[2], t_r, inf);
	setup_padding(p);
	buf_s(p, p->temp, ft_strlen(p->temp));
	inf[5] = ft_strlen(p->temp);
	free(p->temp);
}
