#include /**/ "libftprintf.h" /**///"ft_printf.h"

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
	unsigned int d;
	char *str;
	int bytes = 12;

	d = va_arg(ap, unsigned int);
	str = ft_itoa_Ubase(d, 16, 0);
	write(1, "0x", 2);
	(env->bytes)+=2;
	while ((int)sizeof(str) < --bytes)
	{
		write(1, "f", 1);
		(env->bytes)++;
	}
	while (*str)
	{
		write(1, str++, 1);
		(env->bytes)++;
	}
	(env->curr)++;
}

void printd(t_env *env, va_list ap)
{
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
	printNums(env, ap, 16, 0);
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
        else
            flagFound = 0;
    }
}
void parseConversion(t_env *env, const char * restrict format, va_list ap)
{
	(env->curr)++; //eat leading % sSpdDioOuUxXcC
	parseFlag(env, format);
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
/*
int main(void)
{
	int ret;

	ft_printf("\n");
	ft_printf(" %%%% test\n");
	ret = ft_printf("printing |%%|");
	ft_printf("\n");
	printf("ret is=|%i|\n", ret);

	ft_printf("\n");
	ft_printf("\n");

	ft_printf("Char test\n");
	ft_printf("\n");
	char c;

	c = 'x';

	char d;

	d = 'y';

	ret = ft_printf("printing |%c| |%c|", c, d);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);


	ft_printf("\n");
	ft_printf("\n");


	ft_printf("String test\n");
	ft_printf("\n");
	char *strng = "Hello";

	ret = ft_printf("printing |%s|", strng);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);


	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("d test\n");
	ft_printf("\n");
	int dtest = 1234567890;

	ret = ft_printf("printing |%d|", dtest);	
	ft_printf("\n");
	
	ft_printf("ret is=|%i|\n", ret);
	////////////////////////



	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("x test\n");
	ft_printf("\n");
	int xtest = 1234567890;

	ret = ft_printf("printing |%x|", xtest);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////


		////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("X test\n");
	ft_printf("\n");
	int Xtest = 1234567890;

	ret = ft_printf("printing |%X|", Xtest);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////



	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("o test\n");
	ft_printf("\n");
	int otest = 1234567890;

	ret = ft_printf("printing |%o|", otest);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////

	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("O test\n");
	ft_printf("\n");
	int Otest = 1234567890;

	ret = ft_printf("printing |%O|", Otest);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////


	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("u test\n");
	ft_printf("\n");
	unsigned int utest = 1234567890;

	ret = ft_printf("printing |%u|", utest);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////




	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("p test\n");
	ft_printf("\n");
	unsigned int ptest = 1234567890;

	ret = ft_printf("printing |%p|", &ptest);	
	printf("\nprintfs: |%p|\n", &ptest);
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////



	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("p test\n");
	ft_printf("\n");
	wchar_t wtest = L'Ω';
	setlocale(LC_CTYPE, "");

	ret = ft_printf("printing |%C|", wtest);	
	printf("\nprintfs: |%C|\n", wtest);
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////


	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("o test with #\n");
	ft_printf("\n");
	int oOcttest = 1234567890;

	ret = ft_printf("printing |%#o|", oOcttest);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////

	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("O test with #\n");
	ft_printf("\n");
	int OOcttest = 1234567890;

	ret = ft_printf("printing |%#O|", OOcttest);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////


	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("x test with #\n");
	ft_printf("\n");
	int oxtest = 1234567890;

	ret = ft_printf("printing |%#x|", oxtest);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////

	////////////////////////
	ft_printf("\n");
	ft_printf("\n");


	ft_printf("X test with #\n");
	ft_printf("\n");
	int oXtest = 1234567890;

	ret = ft_printf("printing |%#X|", oXtest);	
	ft_printf("\n");
	
	printf("ret is=|%i|\n", ret);
	////////////////////////



	printf("\n\nnormal printf: printing |%#x|, |%#X|\n\n", oxtest, oXtest);	

	printf("\n\nnormal printf: printing |%#o|, |%#O|\n\n", oOcttest, OOcttest);	

	printf("\n\n\n\nAssorted Printf experiments below\n");

	int test = 100;
	printf("\n100 with %%o =|%o|", test);
	printf("\nusing ft_itoa_base: %s", ft_itoa_base(test, 8, 0));
	printf("\nBelow will \"print Hello right justified in a group of 25 spaces.\"");
	printf("\n|%25.4s|","Hello");
	printf("\n%lu", strlen("Hello"));
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	return (0);
}

*/
