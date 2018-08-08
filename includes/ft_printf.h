
#ifndef FTPRINTF_H
# define FTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include "libft.h"

# include <stdio.h> //delete this

# define BUFF_SIZE	2048

typedef struct		s_pf
{

	char			type;
	char			len;  //0=none, 1=hh, 2=h, 3=l, 4=ll, 5=z, 6=j
	char			zero;
	char			left;
	char			plus;
	char			hash;
	char			space;
	short			pre;
	short			min_w;
	char			*temp;
	char			buf[BUFF_SIZE];
	short			bufsize;
	short			totallen;

}					t_pf;

union u_type
{
	int						di;
	short int				hdi;
	signed char				hhdi;
	long int				ldi;
	long long int			lldi;
	intmax_t				jdi;
	unsigned int			uox; //they all use ui and converts later
	unsigned short int		huox;
	unsigned char			hhuox;
	unsigned long int		luox;
	unsigned long long int	lluox;
	uintmax_t				juox;
	size_t					zdiuox;
	unsigned char			c; //defult no l unsigned char
	wchar_t					lc;   //fk this shit
	char					*s;
	wchar_t					*ls; //and fk this
	unsigned long long int	p;
};

typedef void (*pick_me)(t_pf *p, union u_type *t, va_list ap);

int	ft_printf(const char *format, ...);
//int	setup_flag(t_pf	*p, char *s, int i);
int	setup(t_pf *p, char *s, int i);

void	ft_printf_diuox(t_pf *p, union u_type *t, va_list ap);
void	ft_printf_c(t_pf *p, union u_type *t, va_list ap);
void	ft_printf_s(t_pf *p, union u_type *t, va_list ap);
void	ft_printf_p(t_pf *p, union u_type *t, va_list ap);
void	ft_putwchar(t_pf *p, wchar_t c);
void	setup_padding(t_pf *p);
void	buf_s(t_pf *p, const void *s, short n);
void	buf_c(t_pf *p, const char c);
void	buf_flush(t_pf *p);

#endif
