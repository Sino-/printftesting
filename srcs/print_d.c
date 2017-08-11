#include "ft_printf.h"

void	print_d(t_env *env, va_list ap)
{
	env->bytes += env->space == 1 ? 1 : 0;
	print_nums(env, ap, 10, 0);
}

void	print_cap_d(t_env *env, va_list ap)
{
	print_u_nums(env, ap, 10, 0);
}
