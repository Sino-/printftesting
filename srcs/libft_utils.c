#include "ft_printf.h"

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
