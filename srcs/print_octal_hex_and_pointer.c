/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal_hex_and_pointer.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolabi <yolabi@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 22:13:11 by yolabi            #+#    #+#             */
/*   Updated: 2017/08/10 22:13:13 by yolabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_o(t_env *env, va_list ap)
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

void	print_cap_o(t_env *env, va_list ap)
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

void	print_x(t_env *env, va_list ap)
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

void	print_cap_x(t_env *env, va_list ap)
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
