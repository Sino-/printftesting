#include "ft_printf.h"

void	print_nums(t_env *env, va_list ap, int base, int upper_case)
{
	long long	d;
	char		*str;

	d = va_arg(ap, int);
	str = ft_itoa_base(d, base, upper_case);
	if (env->plus && d >= 0)
	{
		write(1, "+", 1);
		(env->bytes)++;
		if (env->width)
			(env->width)--;
	}
	if (env->space)
		if (d > 0)
		{
			write(1, " ", 1);
			(env->bytes)++;
			if (env->width)
				(env->width)--;
		}
	if (env->minus)
		print_minus(env, str);
	else
		print_numbers(env, str);
	(env->curr)++;
}

void	print_u_nums(t_env *env, va_list ap, int base, int upper_case)
{
	uintmax_t	d;
	char		*str;

	d = va_arg(ap, uintmax_t);
	str = ft_itoa_ubase(d, base, upper_case);
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}
