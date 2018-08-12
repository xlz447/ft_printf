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

int	ft_printf(const char *format, ...)
{
	t_pf	p;
	va_list	ap[2];
	int		out;

	ft_bzero(&p, sizeof(p));
	va_start(ap[0], format);
	va_copy(ap[1], ap[0]);
	out = dispatch(&p, (char*)format, ap, 1);
	va_end(ap[0]);
	va_end(ap[1]);
	return (out);
}
