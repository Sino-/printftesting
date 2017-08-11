#include "ft_printf.h"

void	print_percent(t_env *env, const char *restrict format)
{
	while (format[(env->curr)] == '%')
	{
		write(1, "\%", 1);
		(env->bytes)++;
		(env->curr)++;
	}
}

void	print_c(t_env *env, va_list ap)
{
	char c;

	c = va_arg(ap, int);
	write(1, &c, 1);
	(env->bytes)++;
	(env->curr)++;
}
