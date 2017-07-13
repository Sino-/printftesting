#include "libftprintf.h"

/*
**	Allowed functions:
**	◦ write
**	◦ malloc
**	◦ free
**	◦ exit
**	◦ The functions of man 3 stdarg
**
**	You have to manage the following conversions: sSpdDioOuUxXcC
**	• You must manage %%
**	• You must manage the flags #0-+ and space
**	• You must manage the minimum field-width
**	• You must manage the precision
**	• You must manage the flags hh, h, l, ll, j, et z.
*/

char *ft_itoa_base(int value, int base, int upperCase)
{
	long	currval;
	int		neg = 0;
	int		size = 1;
	char	*ret;

	if (value == 0)
		return ("0");
	if (value < 0 && base == 10)
		neg = 1;
	if (neg)
		size++;
	currval = value;
	if (neg)
		currval = -currval;
	while (currval > 0)
	{
		size++;
		currval /= base;
	}
	char *digits = (upperCase == 1) ? "0123456789ABCDEF" : "0123456789abcdef";
	ret = (char *)malloc(sizeof(char) * size);
	size--;
	ret[size--] = '\0';
	if (neg)
		ret[0] = '-';
	currval = value;
	if (neg)
		currval = -currval;
	while (currval > 0)
	{
		ret[size] = digits[currval % base];
		currval /= base;
		size--;
	}
	return (ret);
}


char *ft_itoa_Ubase(unsigned int value, int base, int upperCase)
{
	unsigned long	currval;
	int		size = 1;
	char	*ret;

	if (value == 0)
		return ("0");
	currval = value;
	while (currval > 0)
	{
		size++;
		currval /= base;
	}
	char *digits = (upperCase == 1) ? "0123456789ABCDEF" : "0123456789abcdef";
	ret = (char *)malloc(sizeof(char) * size);
	size--;
	ret[size--] = '\0';
	currval = value;
	while (currval > 0)
	{
		ret[size] = digits[currval % base];
		currval /= base;
		size--;
	}
	return (ret);
}

void	reset_env(t_env *env)
{
	env->precision	= 0;
	env->octothorpe	= 0;
	env->zero		= 0;
	env->minus		= 0;
	env->plus		= 0;
	env->space		= 0;
	env->hh			= 0;
	env->h			= 0;
	env->l			= 0;
	env->ll			= 0;
	env->j			= 0;
	env->z			= 0;
}

void printPercent(t_env *env, const char * restrict format)
{
	while (format[(env->curr)] == '%')
    {
		write(1, "\%", 1);
		(env->bytes)++;
		(env->curr)++;
	}
}

void printc(t_env *env, va_list ap)
{
	char c = va_arg(ap, int);
	write(1, &c, 1);
	(env->bytes)++;
	(env->curr)++;
}

void printC(t_env *env, va_list ap)
{
	wchar_t c;
	c = va_arg(ap, long long);
	write(1, &c, 1);
	(env->bytes)++;
	(env->curr)++;
}


void prints(t_env *env, va_list ap)
{
	char *str;

	str = va_arg(ap, char *);
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}

void printNums(t_env *env, va_list ap, int base, int upperCase)
{
	int d;
	char *str;

	d = va_arg(ap, int);
	str = ft_itoa_base(d, base, upperCase);
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}

void printUNums(t_env *env, va_list ap, int base, int upperCase)
{
	unsigned int d;
	char *str;

	d = va_arg(ap, unsigned int);
	str = ft_itoa_Ubase(d, base, upperCase);
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}

void printp(t_env *env, va_list ap)
{
	write(1, "0x7fff", 6);
	(env->bytes) += 6;
	printNums(env, ap, 16, 0);
}


void parseFlag(t_env *env, const char * restrict format, va_list ap)
{
	(env->curr)++; //eat leading % sSpdDioOuUxXcC
    if (format[(env->curr)] == '%')
		printPercent(env, format);
	else if (format[(env->curr)] == 's')
		prints(env, ap);
	// else if (format[(env->curr)] == 'S')
	else if (format[(env->curr)] == 'p')
		printp(env, ap);
	else if (format[(env->curr)] == 'd' || format[(env->curr)] == 'i' )
		printNums(env, ap, 10, 0);
	else if (format[(env->curr)] == 'D')
		printUNums(env, ap, 10, 0);
// else if (format[(env->curr)] == 'i')  implemented above with 'd'
	else if (format[(env->curr)] == 'o')
		printNums(env, ap, 8, 0);
	else if (format[(env->curr)] == 'O')
		printUNums(env, ap, 8, 0);
	else if (format[(env->curr)] == 'u')
		printUNums(env, ap, 10, 0);
	// else if (format[(env->curr)] == 'U')
	else if (format[(env->curr)] == 'x')
		printNums(env, ap, 16, 0);
	else if (format[(env->curr)] == 'X')
		printNums(env, ap, 16, 1);
    else if (format[(env->curr)] == 'c')
		printc(env, ap);
    else if (format[(env->curr)] == 'C')
    	printC(env, ap);


}

int ft_printf(const char * restrict format, ...)
{
	t_env env;
	va_list ap;
	va_start(ap, format);

	env.curr		= 0;
	env.bytes		= 0;
  	reset_env(&env);
    while (format[(env.curr)])
    {
        if (format[(env.curr)] == '%')
            parseFlag(&env, format, ap);
        else
        {
            write(1, &(format[(env.curr)]), 1);
        	(env.bytes)++;
        	(env.curr)++;
        }
        
    }
	return (env.bytes);
}

