/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diuox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:39:10 by xzhu              #+#    #+#             */
/*   Updated: 2018/08/03 13:39:12 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	setup_prefix(t_pf *p, uintmax_t ag, char *t_r[2], int inf[5])
{
	if ((ft_strchr("di", p->type)) && (inf[2] || p->plus || p->space))
	{
		if (inf[2])
			t_r[0] = ft_strjoin("-", p->temp);
		else if (p->plus)
			t_r[0] = ft_strjoin("+", p->temp);
		else if (p->space)
			t_r[0] = ft_strjoin(" ", p->temp);
		free(p->temp);
		p->temp = t_r[0];
	}
	if (p->hash && (ft_strchr("oxX", p->type)))
	{
		if (p->type == 'x' && ag > 0)
		{
			t_r[0] = ft_strjoin("0x", p->temp);
			free(p->temp);
			p->temp = t_r[0];
		}
		else if (p->type == 'X' && ag > 0)
		{
			t_r[0] = ft_strjoin("0X", p->temp);
			free(p->temp);
			p->temp = t_r[0];
		}
		else if (p->type == 'o' && p->temp[0] != '0')
		{
			t_r[0] = ft_strjoin("0", p->temp);
			free(p->temp);
			p->temp = t_r[0];
		}
	}
}

void	setup_zero(t_pf *p, char *t_r[2], int inf[5])
{
	if (p->pre > 0)
	{
		while (ft_strlen(p->temp) < (unsigned long) p->pre)
		{
			t_r[0] = ft_strjoin("0", p->temp);
			free(p->temp);
			p->temp = t_r[0];
		}
	}
	else if (!p->left && p->zero && p->min_w > 0)
	{
		while ((ft_strlen(p->temp) + inf[3]) < (unsigned long)p->min_w)
		{
			t_r[0] = ft_strjoin("0", p->temp);
			free(p->temp);
			p->temp = t_r[0];
		}
	}
}

void	setup_nbr(t_pf *p, uintmax_t ag_mx[2], int i[5], char *t_r[2])
{
	char next[2];

	next[1] = '\0';
	ag_mx[1] = (i[0] < 64) ? ((uintmax_t)1 << (i[0])) : 18446744073709551615U; // 不太想在這裡用上實際的數字，但是如果用bit shift會overflow...
	if (ft_strchr("di", p->type)) // signed numbers
	{
		if (ag_mx[1] * 2 && ag_mx[0] >= ag_mx[1] * 2) // 如果超過那個type的range
			ag_mx[0] = ag_mx[0] % ((uintmax_t)1 << (i[0] + 1)); // 不見得是負數
		if (ag_mx[0] >= ag_mx[1]) // 負數
		{
			i[2] = 1;
			if (i[0] + 1 < 64) // one's complement
				ag_mx[0] = ((uintmax_t)1 << (i[0] + 1)) - ag_mx[0];
			else // in case of overflow
				ag_mx[0] = (18446744073709551615U - ag_mx[0]) + 1;
		}
		if (i[2] || (!i[2] && (p->space || p->plus))) // padding for positive #
			i[3] = 1; // padding
	}
	else if (ag_mx[0] == 18446744073709551615U && ag_mx[0] == ag_mx[1])
	{ // only case where both argument and max are the largest possible
		ag_mx[2] = ag_mx[0]; //make a copy so prefix can use
		if (p->type == 'u')
			p->temp = ft_strjoin("18446744073709551615", "");
		else if (p->type == 'o')
			p->temp = ft_strjoin("1777777777777777777777", "");
		else if (p->type == 'x')
			p->temp = ft_strjoin("ffffffffffffffff", "");
		else if (p->type == 'X')
			p->temp = ft_strjoin("FFFFFFFFFFFFFFFF", "");
		return ;
	}
	else // for unsigned use mod to remove overflow part
		ag_mx[0] = ag_mx[0] % ag_mx[1];
	ag_mx[2] = ag_mx[0]; //make a copy so prefix can use
	p->temp = ft_strnew(1);
	if (!ag_mx[0])
	{
		p->temp[0] = '0';
		if (p->pre == 0)
			p->temp[0] = '\0'; // we can always represent 0 with 0 characters
	}
	while(ag_mx[0] > 0) // normal stuff
	{
		next[0] = t_r[1][ag_mx[0] % i[1]]; // temp = ref[num % base]
		t_r[0] = ft_strjoin(next, p->temp);
		free(p->temp);
		p->temp = t_r[0];
		if (p->type == 'X' && (ag_mx[0] % i[1] > 9)) // switching from x to X
			p->temp[0] -= 32;
		ag_mx[0] /= i[1];
	}
}

void	setup_pow_base_pad(t_pf *p, int i[5])
{
	// set up the power of the largest possible number to print
	if (p->len == 0)
		i[0] = 8 * (int)sizeof(int) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 2) //h
		i[0] = 8 * (int)sizeof(short) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 1) // hh
		i[0] = 8 * (int)sizeof(char) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 4) // l
		i[0] = 8 * (int)sizeof(long) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 5)// ll
		i[0] = 8 * (int)sizeof(long long) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 6) // j
		i[0] = 8 * (int)sizeof(intmax_t) - ((ft_strchr("di", p->type)) ? 1 : 0);
	else if (p->len == 7) // z
		i[0] = 8 * (int)sizeof(size_t) - ((ft_strchr("di", p->type)) ? 1 : 0);
	if (p->hash) // set up padding for oxX
		i[3] = (p->type == 'o') + 2 * (ft_strchr("xX", p->type) != NULL);
	if (ft_strchr("xX", p->type)) // set up base
		i[1] = 16;
	else if (p->type == 'o')
		i[1] = 8;
	else if (ft_strchr("diu", p->type))
		i[1] = 10;
}

void	ft_printf_diuox(t_pf *p, union u_type *t, va_list ap)
{
	uintmax_t	ag_mx[3]; // arg ; max ; copy of arg
	char		*t_r[2]; // temp; ref
	int			inf[6]; //pow; base; neg; padding; is_zero; to_ret

	(void) t;
	t_r[1] = "0123456789abcdef";		// r for reference string
	ag_mx[0] = va_arg(ap, uintmax_t);		// the next argument
	inf[0] = 1;		// the power of the result, depending on the length field
	inf[1] = 0;		// the base the result is going to be
	inf[2] = 0;		// if this is a negative or not(d or i only)
	inf[3] = 0;		// the number of prefix characters of this number(sign, 0x etc)
	setup_pow_base_pad(p, inf);			// set up the max power, base, and padding according to the flags set
	setup_nbr(p, ag_mx, inf, t_r);		// set up the number to print out(without signs)
	setup_zero(p, t_r, inf);				// add the zeros for the precision and the min_width
	setup_prefix(p, ag_mx[2], t_r, inf);  	// put on the prefix(+, - ,  , 0, 0x, 0X) b4 the number
	setup_padding(p);						// the universal padding function
	buf_s(p, p->temp, ft_strlen(p->temp));
	inf[5] = ft_strlen(p->temp);
	free(p->temp);
}
