/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diuoxb_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:11:36 by xzhu              #+#    #+#             */
/*   Updated: 2018/08/11 21:11:37 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		setup_padding(t_pf *p)
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

static void	prefix_helper(t_pf *p, uintmax_t ag, char *t_r[2])
{
	if (p->hash && (ft_strchr("bBoxX", p->type)))
	{
		if (p->type == 'x' && ag > 0)
			t_r[0] = ft_strjoin("0x", p->temp);
		else if (p->type == 'X' && ag > 0)
			t_r[0] = ft_strjoin("0X", p->temp);
		else if (p->type == 'b' && ag > 0)
			t_r[0] = ft_strjoin("0b", p->temp);
		else if (p->type == 'B' && ag > 0)
			t_r[0] = ft_strjoin("0B", p->temp);
		else if (p->type == 'o' && p->temp[0] != '0')
			t_r[0] = ft_strjoin("0", p->temp);
		if ((ft_strchr("bBxX", p->type) && ag > 0) ||
			(p->type == 'o' && p->temp[0] != '0'))
		{
			free(p->temp);
			p->temp = t_r[0];
		}
	}
}

void		setup_prefix(t_pf *p, uintmax_t ag, char *t_r[2], int inf[5])
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
	prefix_helper(p, ag, t_r);
}

void		setup_zero(t_pf *p, char *t_r[2], int inf[5])
{
	if (p->pre > 0)
	{
		while (ft_strlen(p->temp) < (unsigned long)p->pre)
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
