#include "libftprintf.h"
#define CAP_HEX "0123456789ABCDEF"
#define LOW_HEX "0123456789abcdef"
#define FT_ITOA_BASE_VARS long long currval;int neg,size;char *ret,*digits

size_t	ft_strlen(char const *str)
{
	size_t	curr;

	curr = 0;
	while (str[curr])
		curr++;
	return (curr);
}

char	*ft_strdup(char const *s)
{
	char	*dup;
	size_t	len;
	char	*s_ptr;
	size_t	curr;

	curr = 0;
	s_ptr = (char *)s;
	len = ft_strlen((char *)s);
	dup = (char *)malloc((sizeof(char) * len) + 1);
	if (!dup)
		return (0);
	while (s[curr])
	{
		dup[curr] = s_ptr[curr];
		curr++;
	}
	dup[curr] = '\0';
	return (dup);
}

int		ft_isdigit(int ascii_char)
{
	if ((ascii_char) >= '0' && (ascii_char <= '9'))
		return (1);
	return (0);
}

int		ft_iswhitespace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	else
		return (0);
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

void	print_percent(t_env *env, const char *restrict format)
{
	while (format[(env->curr)] == '%')
	{
		write(1, "\%", 1);
		(env->bytes)++;
		(env->curr)++;
	}
}

void	printc(t_env *env, va_list ap)
{
	char c;

	c = va_arg(ap, int);
	write(1, &c, 1);
	(env->bytes)++;
	(env->curr)++;
}

void	print_string(t_env *env, char *str)
{
	if (env->precision)
	{
		while ((env->precision)--)
		{
			write(1, str++, 1);
			(env->bytes)++;
		}
	}
	else
	{
		while (*str)
		{
			write(1, str++, 1);
			(env->bytes)++;
		}
	}
}

void	print_padding(t_env *env, char *str, char padding)
{
	if (env->width)
	{
		printf("\n\n WIDTH BEFORE LOOP IS |%lu|", (env->width));

		while (((env->width) - ft_strlen(str)) > 0 || ((env->width) - (env->precision)) > 0)
		{
			write(1, &padding, 1);
			(env->bytes)++;
			(env->width)--;
		}
		printf("\n\n WIDTH IS |%lu|", (env->width));
		// while ((env->precision) > 0)
		// {
		// 	write(1, &padding, 1);
		// 	(env->bytes)++;
		// 	(env->precision)--;
		// }
	}
}

void	prints(t_env *env, va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (env->minus)
	{
		print_string(env, str);
		print_padding(env, str, ' ');
	}
	else
	{
		print_padding(env, str, ' ');
		print_string(env, str);
	}
	(env->curr)++;
}

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
	{
		print_string(env, str);
		print_padding(env, str, ' ');
	}
	else if (env->zero)
	{
		print_padding(env, str, '0');
		print_string(env, str);
	}
	else
	{
		print_padding(env, str, ' ');
		print_string(env, str);
	}
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

void	print_p(t_env *env, va_list ap)
{
	uintmax_t	d;
	char		*str;

	d = va_arg(ap, uintmax_t);
	str = ft_itoa_ubase(d, 16, 0);
	write(1, "0x", 2);
	(env->bytes) += 2;
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}

void	printd(t_env *env, va_list ap)
{
	env->bytes += env->space == 1 ? 1 : 0;
	print_nums(env, ap, 10, 0);
}

void	print_capital_d(t_env *env, va_list ap)
{
	print_u_nums(env, ap, 10, 0);
}

void	printo(t_env *env, va_list ap)
{
	uintmax_t	d;
	char		*str;

	d = va_arg(ap, uintmax_t);
	str = ft_itoa_ubase(d, 8, 0);
	if (str[0] != '0')
		env->bytes += env->octothorpe == 1 ? write(1, "0", 1) : 0;
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}

void	print_capital_o(t_env *env, va_list ap)
{
	uintmax_t	d;
	char		*str;

	d = va_arg(ap, uintmax_t);
	print_u_nums(env, ap, 8, 0);
	str = ft_itoa_ubase(d, 8, 0);
	if (str[0] != '0')
		env->bytes += env->octothorpe == 1 ? write(1, "0", 1) : 0;
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}

void	printx(t_env *env, va_list ap)
{
	uintmax_t	d;
	char		*str;

	d = va_arg(ap, uintmax_t);
	str = ft_itoa_ubase(d, 16, 0);
	env->bytes += env->octothorpe == 1 ? write(1, "0x", 2) : 0;
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}

void	print_capital_x(t_env *env, va_list ap)
{
	uintmax_t	d;
	char		*str;

	d = va_arg(ap, uintmax_t);
	str = ft_itoa_ubase(d, 16, 1);
	env->bytes += env->octothorpe == 1 ? write(1, "0X", 2) : 0;
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}

void	set_octothorpe(t_env *env)
{
	env->octothorpe = 1;
	(env->curr)++;
}

void	set_zero(t_env *env)
{
	env->zero = 1;
	(env->curr)++;
}

void	set_minus(t_env *env)
{
	env->minus = 1;
	(env->curr)++;
}

void	set_plus(t_env *env)
{
	env->plus = 1;
	(env->curr)++;
}

void	set_space(t_env *env)
{
	env->space = 1;
	(env->curr)++;
}

void	set_h(t_env *env, const char *restrict format)
{
	env->h = 1;
	(env->curr)++;
	if (format[(env->curr)] == 'h')
	{
		env->hh = 1;
		(env->curr)++;
	}
}

void	set_l(t_env *env, const char *restrict format)
{
	env->l = 1;
	(env->curr)++;
	if (format[(env->curr)] == 'l')
	{
		env->ll = 1;
		(env->curr)++;
	}
}

void	parse_flag(t_env *env, const char *restrict format, char found, int esc)
{
	while (found || esc < 4)
	{
		found = 1;
		if (format[(env->curr)] == '#')
			set_octothorpe(env);
		else if (format[(env->curr)] == '0')
			set_zero(env);
		else if (format[(env->curr)] == '-')
			set_minus(env);
		else if (format[(env->curr)] == '+')
			set_plus(env);
		else if (format[(env->curr)] == ' ')
			set_space(env);
		else if (format[(env->curr)] == 'z' || format[(env->curr)] == 'j')
			(env->curr)++;
		else if (format[(env->curr)] == 'l')
			set_l(env, format);
		else if (format[(env->curr)] == 'h')
			set_h(env, format);
		else
		{
			found = 0;
			esc++;
		}
	}
}

void	parse_conversion(t_env *env, const char *restrict format, va_list ap)
{
	(env->curr)++;
	parse_flag(env, format, 1, 1);
	find_width(env, format);
	find_precision(env, format);
	if (format[(env->curr)] == '%')
		print_percent(env, format);
	else if (format[(env->curr)] == 's')
		prints(env, ap);
	//else if (format[(env->curr)] == 'S')
	//printS(env, ap);
	else if (format[(env->curr)] == 'p')
		print_p(env, ap);
	else if (format[(env->curr)] == 'd' || format[(env->curr)] == 'i')
		printd(env, ap);
	else if (format[(env->curr)] == 'D')
		print_capital_d(env, ap);
	else if (format[(env->curr)] == 'o' || format[(env->curr)] == 'O')
		format[(env->curr)] == 'o' ? printo(env, ap) : print_capital_o(env, ap);
	else if (format[(env->curr)] == 'u' || format[(env->curr)] == 'U')
		print_u_nums(env, ap, 10, 0);
	else if (format[(env->curr)] == 'X' || format[(env->curr)] == 'x')
		format[(env->curr)] == 'x' ? printx(env, ap) : print_capital_x(env, ap);
	else if (format[(env->curr)] == 'c' || format[(env->curr)] == 'C')
		printc(env, ap);
	reset_env(env);
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