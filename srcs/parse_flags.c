/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolabi <yolabi@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 22:12:20 by yolabi            #+#    #+#             */
/*   Updated: 2017/08/10 22:17:51 by yolabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_flags(t_env *env, const char *restrict format, char fnd, int esc)
{
	while (fnd || esc < 4)
	{
		fnd = 1;
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
			fnd = 0;
			esc++;
		}
	}
}
