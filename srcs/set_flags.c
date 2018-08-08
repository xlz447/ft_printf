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

int	setup(t_pf *p, char *s, int i)
{
	while (s[i] && ft_strchr("-+ 0#.hlzj123456789", s[i]) && !ft_strchr("sSpdDioOuUxXcC%", s[i]))
	{
		if (ft_strchr("-+ 0#", s[i]))
		{
			if (s[i] == '-')
			{
				p->zero = 0;
				p->left = 1;
			}
			else if (s[i] == '+')
			{
				p->space = 0;
				p->plus = 1;
			}
			else if (s[i] == ' ' && p->plus != 1)
				p->space = 1;
			else if (s[i] == '0' && p->left != 1)
				p->zero = 1;
			else if (s[i] == '#')
				p->hash = 1;
		}
		else if (ft_strchr("hlzj", s[i]))
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
		}
		else if (s[i] == '.')
		{
			i++;
			p->pre = ft_atoi(s + i);
			while (s[i] && ((s[i] >= '0' && s[i] <= '9')))
				i++;
			continue ;
		}
		else if (ft_strchr("123456789", s[i]))
		{
			p->min_w = ft_atoi(s + i);
			while (s[i] && ((s[i] >= '0' && s[i] <= '9')))
				i++;
			continue ;
		}
		i++;
	}
//到这里有两种可能，1。碰到了一个不是任何flag的char，测试后的结果是：
//把这个char放到buf里
//已经拿到的flag做可以做的事把这个char算进去，直接return这个i；
//2.碰到了一个type，这个时候就按照正常的去做
	if (!s[i])
		return (i);
	else if (!ft_strchr("sSpdDioOuUxXcC", s[i]))
		p->temp = &s[i];
	else if (ft_strchr("SDOUC", s[i]))
	{
		p->type = s[i] + 32;
		p->len = 4;
	}
	else
		p->type = s[i]; // 我有在想DOU可不可以在這裡一併處理（len = "l", type = 'd'之類的;
	if (p->type && ft_strchr("diouX", p->type) && p->pre != -1)
		p->zero = 0;
	return (i);
}
