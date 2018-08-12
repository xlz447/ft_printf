/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:26:49 by xzhu              #+#    #+#             */
/*   Updated: 2018/08/10 14:26:50 by xzhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include "libft.h"

# define BUFF_SIZE	2048
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

union						u_type
{
	int						di;
	short int				hdi;
	signed char				hhdi;
	long int				ldi;
	long long int			lldi;
	intmax_t				jdi;
	unsigned int			uox;
	unsigned short int		huox;
	unsigned char			hhuox;
	unsigned long int		luox;
	unsigned long long int	lluox;
	uintmax_t				juox;
	size_t					zdiuox;
	unsigned char			c;
	wchar_t					lc;
	char					*s;
	wchar_t					*ls;
	unsigned long long int	p;
}							;

/*
** for len 0=none, 1=hh, 2=h, 3=l, 4=ll, 5=z, 6=j
*/

typedef struct				s_pf
{
	char					type;
	char					len;
	char					zero;
	char					left;
	char					plus;
	char					hash;
	char					space;
	char					apos;
	short					pre;
	short					min_w;
	short					dollor;
	char					*temp;
	char					buf[BUFF_SIZE];
	short					bufsize;
	short					totallen;
	int						fd;
	int						col[2];
	union u_type			t;
}							t_pf;

typedef void	(*t_pick_me)(t_pf *p, union u_type *t, va_list ap);

int							ft_printf(const char *format, ...);
int							dispatch(t_pf *p, char *s, va_list ap[2], int fd);
int							setup(t_pf *p, char *s, int i, va_list ap);
void						ft_printf_diuoxb(t_pf *p,
											union u_type *t, va_list ap);
void						ft_printf_c(t_pf *p, union u_type *t, va_list ap);
void						ft_printf_lc(t_pf *p, union u_type *t, va_list ap);
void						ft_printf_s(t_pf *p, union u_type *t, va_list ap);
void						ft_printf_ls(t_pf *p, union u_type *t, va_list ap);
void						ft_printf_p(t_pf *p, union u_type *t, va_list ap);
void						ft_putwchar(t_pf *p, wchar_t c);
void						buf_s(t_pf *p, const void *s, short n);
void						buf_c(t_pf *p, const char c);
void						buf_flush(t_pf *p);
void						setup_padding(t_pf *p);
void						setup_prefix(t_pf *p, uintmax_t ag,
											char *t_r[2], int inf[5]);
void						setup_zero(t_pf *p, char *t_r[2], int inf[5]);
#endif
