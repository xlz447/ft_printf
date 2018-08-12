/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:21:04 by xzhu              #+#    #+#             */
/*   Updated: 2018/08/10 14:21:06 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	buf_flush(t_pf *p)
{
	write(p->fd, p->buf, p->bufsize);
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
