#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <wchar.h>
# include <locale.h>
#endif

int ft_printf(const char * restrict format, ...);

typedef struct		s_env
{
	int				curr;
	int				bytes;
	char			conversion;
	int				width;
	unsigned int	precision;
	unsigned int	octothorpe	:1;
	unsigned int	zero		:1;
	unsigned int	minus		:1;
	unsigned int	plus		:1;
	unsigned int	space		:1;
	unsigned int	hh			:1;
	unsigned int	h			:1;
	unsigned int	l			:1;
	unsigned int	ll			:1;
	unsigned int	j			:1;
	unsigned int	z			:1;
}					t_env;