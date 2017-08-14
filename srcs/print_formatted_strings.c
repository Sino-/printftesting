/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted_strings.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolabi <yolabi@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 22:12:49 by yolabi            #+#    #+#             */
/*   Updated: 2017/08/10 22:12:50 by yolabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_string(t_env *env, char *str)
{
	unsigned int	precision;

	precision = (env->precision);
	if (precision)
	{
		while (precision)
		{
			write(1, str++, 1);
			(env->bytes)++;
			precision--;
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
	unsigned int len;

	len = (env->precision) < ft_strlen(str) ? (env->precision) : ft_strlen(str);
	if (env->width)
	{
		while (((env->width)-- - len) > 0)
		{
			write(1, &padding, 1);
			(env->bytes)++;
		}
	}
}

void	print_s(t_env *env, va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (str)
	{
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
	else
	{
		write(1, "(null)", 6);
		(env->bytes) += 6;
	}
}
