/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolabi <yolabi@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 22:11:34 by yolabi            #+#    #+#             */
/*   Updated: 2017/08/10 22:11:36 by yolabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
