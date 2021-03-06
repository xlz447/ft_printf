# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xzhu <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/11 18:18:47 by xzhu              #+#    #+#              #
#    Updated: 2018/07/11 18:23:13 by xzhu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CFLAGS +=	-Wall -Werror -Wextra
CFLAGS +=	-I includes/

NOC		=	\033[0m
GREEN	=	\033[0;32m
BLUE	=	\033[0;34m
RED		=	\033[0;31m

PRINTFFILES=ft_printf.c \
			set_flags.c \
			dispatch.c \
			buffer.c \
			ft_printf_diuoxb.c \
			ft_printf_c.c \
			ft_printf_s.c \
			ft_printf_p.c \
			diuoxb_setup.c

LIBFTFILES =ft_putchar.c \
			ft_memset.c \
			ft_putstr.c \
			ft_putnbr.c \
			ft_putendl.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_itoa.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstaddback.c \
			ft_lstsize.c \
			ft_lstrev.c \
			ft_lstsort.c \
			ft_lstat.c \
			ft_errorexit.c

PRINTFSRCS	= $(addprefix srcs/, $(PRINTFFILES))
LIBSRCS		= $(addprefix libft/, $(LIBFTFILES))

PRINTFOBJ	= $(PRINTFSRCS:.c=.o)
LIBFTOBJ	= $(LIBSRCS:.c=.o)

all: $(NAME)

test: all
	@gcc test.c $(PRINTFSRCS) $(LIBSRCS) -I includes -g
	@echo "$(GREEN)testing ✓ Created a.out$(NOC)"

$(PRINTFOBJ): %.o:%.c
	@gcc -c $(CFLAGS) $< -o $@

$(LIBFTOBJ): %.o:%.c
	@gcc -c $(CFLAGS) $< -o $@

$(NAME): $(LIBFTOBJ) $(PRINTFOBJ)
	@ar rcs $(NAME) $(PRINTFOBJ) $(LIBFTOBJ)
	@ranlib $(NAME)
	@echo "$(GREEN)LIBFTPRINTF ✓ Created libftprintf.a$(NOC)"

clean:
	@rm -f $(PRINTFOBJ) $(LIBFTOBJ)
	@echo "$(BLUE)LIBFTPRINTF ✓ Removed .o files$(NOC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)LIBFTPRINTF ✓ Removed libftprintf.a$(NOC)"

testclean: fclean
	@rm -f a.out
	@rm -rf a.out.dSYM
	@echo "$(RED)testing ✓ Removed a.out.dSYM$(NOC)"
	@echo "$(RED)testing ✓ Removed a.out$(NOC)"

re: fclean all

.PHONY: all clean fclean re
