#include "ft_printf.h"

void	print_number_padding(t_env *env, char *str)
{
	if ((env->zero) && (ft_strlen(str) + env->precision) < env->width)
	{
		while ((env->width)-- > ft_strlen(str))
		{
			write(1, "0", 1);
			(env->bytes)++;
		}
	}
	else if (env->precision > ft_strlen(str) ||
		((env->zero) && (ft_strlen(str) - env->precision) < env->width))
	{
		while ((env->width)-- > (env->precision))
		{
			write(1, " ", 1);
			(env->bytes)++;
		}
	}
	else
	{
		while ((env->width)-- > (ft_strlen(str) + (env->precision)))
		{
			write(1, " ", 1);
			(env->bytes)++;
		}
	}
}

void	print_number_string(t_env *env, char *str)
{
	unsigned int	precision;

	precision = (env->precision);
	if (precision)
	{
		while (precision - ft_strlen(str) > 0)
		{
			write(1, "0", 1);
			(env->bytes)++;
			precision--;
		}
	}
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
}

void	print_minus(t_env *env, char *str)
{
	print_number_string(env, str);
	print_number_padding(env, str);
}

void	print_numbers(t_env *env, char *str)
{
	print_number_padding(env, str);
	print_number_string(env, str);
}