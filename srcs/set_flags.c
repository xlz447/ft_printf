/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:38:04 by xzhu              #+#    #+#             */
/*   Updated: 2018/08/03 13:38:09 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_flags(t_pf *p, char c)
{
	if (c == '-')
	{
		p->zero = 0;
		p->left = 1;
	}
	else if (c == '+')
	{
		p->space = 0;
		p->plus = 1;
	}
	else if (c == ' ' && p->plus != 1)
		p->space = 1;
	else if (c == '0' && p->left != 1)
		p->zero = 1;
	else if (c == '#')
		p->hash = 1;
	else if (c == '\'')
		p->apos = 1;
}

static int	check_length(t_pf *p, char *s, int i)
{
	if (s[i] == 'h' && s[i + 1] == 'h' && p->len <= 1)
		p->len = 1;
	else if (s[i] == 'h' && s[i + 1] != 'h' && p->len <= 2)
		p->len = 2;
	else if (s[i] == 'l' && s[i + 1] != 'l' && p->len <= 4)
		p->len = 4;
	else if (s[i] == 'l' && s[i + 1] == 'l' && p->len <= 5)
		p->len = 5;
	else if (s[i] == 'j' && p->len <= 6)
		p->len = 6;
	else if (s[i] == 'z' && p->len <= 7)
		p->len = 7;
	if (p->len == 1 || p->len == 5)
		i++;
	return (i);
}

static int	check_pre_minw(t_pf *p, char *s, int i, va_list ap)
{
	short nb;

	if (s[i] == '.')
	{
		i++;
		if (s[i] == '*')
			p->pre = va_arg(ap, int);
		else
			p->pre = ft_atoi(s + i);
		while (s[i] && ((s[i] >= '0' && s[i] <= '9') || s[i] == '*'))
			i++;
	}
	else
	{
		nb = ft_atoi(s + i);
		while (s[i] && (s[i] >= '0' && s[i] <= '9'))
			i++;
		if (s[i] == '$')
			p->dollor = nb;
		else
			p->min_w = nb;
	}
	return (i);
}

/*
**	到这里有两种可能，1。碰到了一个不是任何flag的char，测试后的结果是：
**	把这个char放到buf里
**	已经拿到的flag做可以做的事把这个char算进去，直接return这个i；
**	2.碰到了一个type，这个时候就按照正常的去做
*/

static int	check_special(t_pf *p, char *s, int i)
{
	if (s[i] == '\0')
		return (i);
	else if (!ft_strchr("sSpdDioOuUxXcCbB", s[i]))
		p->temp = &s[i];
	else if (ft_strchr("DOU", s[i]))
	{
		p->type = s[i] + 32;
		p->len = 4;
	}
	else
		p->type = s[i];
	if ((p->type == 'c' || p->type == 's') && p->len == 4)
		p->type = p->type - 32;
	if (p->type && ft_strchr("diouxX", p->type) && p->pre > -1)
		p->zero = 0;
	return (i);
}

int			setup(t_pf *p, char *s, int i, va_list ap)
{
	while (s[i] && ft_strchr("*-+ 0#.hlzj123456789$\'", s[i])
				&& !ft_strchr("sSpdDioOuUxXcCbB%", s[i]))
	{
		if (ft_strchr("-+ 0#\'", s[i]))
			check_flags(p, s[i]);
		else if (ft_strchr("hlzj", s[i]))
			i = check_length(p, s, i);
		else if (ft_strchr("123456789.", s[i]))
		{
			i = check_pre_minw(p, s, i, ap);
			continue ;
		}
		else if (s[i] == '*')
		{
			p->min_w = va_arg(ap, int);
			if (p->min_w < 0)
			{
				p->min_w *= -1;
				p->left = 1;
			}
		}
		i++;
	}
	return (check_special(p, s, i));
}
