/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolabi <yolabi@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 22:12:11 by yolabi            #+#    #+#             */
/*   Updated: 2017/08/10 22:12:12 by yolabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_conversion(t_env *env, const char *restrict format, va_list ap)
{
	(env->curr)++;
	parse_flags(env, format, 1, 1);
	find_width(env, format);
	find_precision(env, format);
	if (format[(env->curr)] == '%')
		print_percent(env, format);
	else if (format[(env->curr)] == 's')
		print_s(env, ap);
	else if (format[(env->curr)] == 'p')
		print_p(env, ap);
	else if (format[(env->curr)] == 'd' || format[(env->curr)] == 'i')
		print_d(env, ap);
	else if (format[(env->curr)] == 'D')
		print_cap_d(env, ap);
	else if (format[(env->curr)] == 'o' || format[(env->curr)] == 'O')
		format[(env->curr)] == 'o' ? print_o(env, ap) : print_cap_o(env, ap);
	else if (format[(env->curr)] == 'u' || format[(env->curr)] == 'U')
		print_u_nums(env, ap, 10, 0);
	else if (format[(env->curr)] == 'X' || format[(env->curr)] == 'x')
		format[(env->curr)] == 'x' ? print_x(env, ap) : print_cap_x(env, ap);
	else if (format[(env->curr)] == 'c' || format[(env->curr)] == 'C')
		print_c(env, ap);
	reset_env(env);
}
