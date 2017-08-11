#include "ft_printf.h"

void	find_width(t_env *env, const char *restrict format)
{
	while (ft_isdigit(format[(env->curr)]) == 1)
	{
		(env->width) = ((env->width) * 10) + (format[(env->curr)] - 48);
		(env->curr)++;
	}
}

void	find_precision(t_env *env, const char *restrict format)
{
	if (format[(env->curr)] == '.')
	{
		(env->curr)++;
		while (ft_isdigit(format[(env->curr)]) == 1)
		{
			(env->precision) = (env->precision * 10) + format[(env->curr)] - 48;
			(env->curr)++;
		}
	}
}
