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


//

//Flag		Meaning
//-			The output is left justified in its field, not right justified (the default).
//+	    	Signed numbers will always be printed with a leading sign (+ or -).
//space		Positive numbers are preceded by a space (negative numbers by a - sign).
//0	    	For numeric conversions, pad with leading zeros to the field width.
//#	    	An alternative output form. For o, the first digit will be '0'. For x or X, "0x" or "0X" will be prefixed to a non-zero result. For e, E, f, F, g and G, the output will always have a decimal point; for g and G, trailing zeros will not be removed.

int	ft_isdigit(int ascii_char)
{
	if ((ascii_char) >= '0' && (ascii_char <= '9'))
		return (1);
	return (0);
}

int	ft_iswhitespace(char c)
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

void	find_width(t_env *env, const char * restrict format)
{
	while (ft_isdigit(format[(env->curr)]) == 1)
	{
		(env->width) = ((env->width) * 10) + (format[(env->curr)] - 48);
		(env->curr)++;
	}
	//printf("\n\n\n\n\nWIDTH IS |%i|\n\n\n\n\n\n", env->width);
}
void	find_precision(t_env *env, const char * restrict format)
{
	if (format[(env->curr)] == '.')
	{
		(env->curr)++;
		while (ft_isdigit(format[(env->curr)]) == 1)
		{
			(env->precision) = ((env->precision) * 10) + (format[(env->curr)] - 48);
			(env->curr)++;
		}
	}
			//printf("\n\n\n\n\nPRECISION IS |%i|\n\n\n\n\n\n", env->precision);
}


size_t	ft_strlen(char const *str)
{
	size_t	curr;

	curr = 0;
	while (str[curr])
		curr++;
	return (curr);
}


char *ft_itoa_base(long long value, int base, int upperCase)
{
	long long	currval;
	int			neg = 0;
	int			size = 1;
	char		*ret;

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


char *ft_itoa_Ubase(unsigned long long value, long base, int upperCase)
{
	unsigned long long	currval;
	int					size = 1;
	char				*ret;

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
	env->width		= 0;
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

void printString(t_env *env, char *str)
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

void printPadding(t_env *env, char *str, char padding)
{
	if (env->width)
	{
		while(((env->width) - ft_strlen(str)) > 0)
		{
			write(1, &padding, 1);
			(env->bytes)++;
			(env->width)--;
		}
	}
}

void prints(t_env *env, va_list ap)
{
	char *str;

	str = va_arg(ap, char *);
	if (env->minus)
	{
		printString(env, str);
		printPadding(env, str, ' ');
	}
	else
	{
		printPadding(env, str, ' ');
		printString(env, str);
	}
	(env->curr)++;
}


void printNums(t_env *env, va_list ap, int base, int upperCase)
{
	int d;
	char *str;

	d = va_arg(ap, int);
	str = ft_itoa_base(d, base, upperCase);
	if (env->plus && d >= 0)
	{
		write(1, "+", 1);
		(env->bytes)++;
		if(env->width)
			(env->width)--;
	}
	if (env->minus)
	{
		printString(env, str);
		printPadding(env, str, ' ');
	}
	else if (env->zero)
	{
		printPadding(env, str, '0');
		printString(env, str);
	}
	else
	{
		printPadding(env, str, ' ');
		printString(env, str);
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
	unsigned int d;
	char *str;
	//int bytes = 12;

	d = va_arg(ap, unsigned int);
	str = ft_itoa_Ubase(d, 16, 0);
	write(1, "0x", 2);
	(env->bytes)+=2;
	//while ((int)sizeof(str) < --bytes)
	// {
	// 	write(1, "f", 1);
	// 	(env->bytes)++;
	// }
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}

void printd(t_env *env, va_list ap)
{
	env->bytes += env->space == 1 ? 1 : 0;
	printNums(env, ap, 10, 0);
}

void printD(t_env *env, va_list ap)
{
	printUNums(env, ap, 10, 0);
}

void printo(t_env *env, va_list ap)
{
	env->bytes += env->octothorpe == 1 ? write(1, "0", 1) : 0;
	printNums(env, ap, 8, 0);
}

void printO(t_env *env, va_list ap)
{
	env->bytes += env->octothorpe == 1 ? write(1, "0", 1) : 0;
	printUNums(env, ap, 8, 0);
}

void printx(t_env *env, va_list ap)
{
	env->bytes += env->octothorpe == 1 ? write(1, "0x", 2) : 0;
	printNums(env, ap, 16, 0);
}

void printX(t_env *env, va_list ap)
{
	env->bytes += env->octothorpe == 1 ? write(1, "0X", 2) : 0;
	printNums(env, ap, 16, 1);
}

void parseFlag(t_env *env, const char * restrict format)
{
    char flagFound;

    flagFound = 1;
    while (flagFound)
    {
        flagFound = 1;
        if (format[(env->curr)] == '#')
        {
            env->octothorpe = 1;
            (env->curr)++;
        }
        else if (format[(env->curr)] == '0')
        {
            env->zero = 1;
            (env->curr)++;

        }
        else if (format[(env->curr)] == '-')
        {
            env->minus = 1;
            (env->curr)++;

        }
        else if (format[(env->curr)] == '+')
        {
            env->plus = 1;
            (env->curr)++;

        }
        else if (format[(env->curr)] == ' ')
        {
            env->space = 1;
            (env->curr)++;
        }
        else if (format[(env->curr)] == 'l')
        {
        	env->l = 1;
            (env->curr)++;
            if (format[(env->curr)] == 'l')
            {
            	env->ll = 1;
            	(env->curr)++;
            }
        }
        else
            flagFound = 0;
    }
}
void parseConversion(t_env *env, const char * restrict format, va_list ap)
{
	(env->curr)++; //eat leading % sSpdDioOuUxXcC
	parseFlag(env, format);
	find_width(env, format);
	find_precision(env, format);
	if (format[(env->curr)] == '%')
		printPercent(env, format);
	else if (format[(env->curr)] == 's')
		prints(env, ap);
	// else if (format[(env->curr)] == 'S')
	else if (format[(env->curr)] == 'p')
		printp(env, ap);
	else if (format[(env->curr)] == 'd' || format[(env->curr)] == 'i' )
		printd(env, ap);
	else if (format[(env->curr)] == 'D')
		printD(env, ap);
// else if (format[(env->curr)] == 'i')  implemented above with 'd'
	else if (format[(env->curr)] == 'o')
		printo(env, ap);
	else if (format[(env->curr)] == 'O')
		printO(env, ap);
	else if (format[(env->curr)] == 'u')
		printUNums(env, ap, 10, 0);
	// else if (format[(env->curr)] == 'U')
	else if (format[(env->curr)] == 'x')
		printx(env, ap);
	else if (format[(env->curr)] == 'X')
		printX(env, ap);
	else if (format[(env->curr)] == 'c')
		printc(env, ap);
	else if (format[(env->curr)] == 'C')
		printC(env, ap);
	reset_env(env);
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
		 {
			 if(format[(env.curr + 1)] == ' ')
			 {
				 while (format[(env.curr + 1)] == ' ')
					 (env.curr)++;
				 write(1, " ", 1);
				 (env.bytes)++;

			 }
			 parseConversion(&env, format, ap);
		 }
		else
		{
			write(1, &(format[(env.curr)]), 1);
			(env.bytes)++;
			(env.curr)++;
		}
		
	}
	return (env.bytes);
}



