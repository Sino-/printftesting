#include "ft_printf.h"
#define CAP_HEX "0123456789ABCDEF"
#define LOW_HEX "0123456789abcdef"
#define FT_ITOA_BASE_VARS long long currval;int neg,size;char *ret,*digits

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
