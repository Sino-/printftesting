#include "ft_printf.h"

void	reset_env(t_env *env)
{
	env->width = 0;
	env->precision = 0;
	env->octothorpe = 0;
	env->zero = 0;
	env->minus = 0;
	env->plus = 0;
	env->space = 0;
	env->hh = 0;
	env->h = 0;
	env->l = 0;
	env->ll = 0;
	env->j = 0;
	env->z = 0;
}

void	init_env(t_env *env)
{
	env->curr = 0;
	env->bytes = 0;
	reset_env(env);
}
