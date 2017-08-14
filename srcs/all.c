#include "ft_printf.h"

#define CAP_HEX "0123456789ABCDEF"
#define LOW_HEX "0123456789abcdef"
#define FT_ITOA_BASE_VARS long long currval;int neg,size;char *ret,*digits

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




int		ft_printf(const char *restrict format, ...)
{
	t_env	env;
	va_list	ap;

	va_start(ap, format);
	init_env(&env);
	while (format[(env.curr)])
	{
		if (format[(env.curr)] == '%')
		{
			if (format[(env.curr + 1)] == ' ')
			{
				while (format[(env.curr + 1)] == ' ')
					(env.curr)++;
				env.space = 1;
			}
			parse_conversion(&env, format, ap);
		}
		else
		{
			write(1, &(format[(env.curr)++]), 1);
			(env.bytes)++;
		}
	}
	return (env.bytes);
}


char	*ft_itoa_base(long long value, int base, int upper_case)
{
	FT_ITOA_BASE_VARS;
	digits = (upper_case) ? ft_strdup(CAP_HEX) : ft_strdup(LOW_HEX);
	if (value == 0)
		return ("0");
	neg = (value < 0 && base == 10) ? 1 : 0;
	size = 1 + neg;
	currval = (neg) ? -value : value;
	while (currval > 0)
	{
		size++;
		currval /= base;
	}
	ret = (char *)malloc(sizeof(char) * size--);
	ret[size--] = '\0';
	if (neg)
		ret[0] = '-';
	currval = (neg) ? -value : value;
	while (currval > 0)
	{
		ret[size--] = digits[currval % base];
		currval /= base;
	}
	return (ret);
}

char	*ft_itoa_ubase(unsigned long long value, long base, int upper_case)
{
	unsigned long long	currval;
	int					size;
	char				*ret;
	char				*digits;

	size = 1;
	if (value == 0)
		return ("0");
	currval = value;
	while (currval > 0)
	{
		size++;
		currval /= base;
	}
	digits = (upper_case) ? ft_strdup(CAP_HEX) : ft_strdup(LOW_HEX);
	ret = (char *)malloc(sizeof(char) * size--);
	ret[size--] = '\0';
	currval = value;
	while (currval > 0)
	{
		ret[size--] = digits[currval % base];
		currval /= base;
	}
	return (ret);
}
