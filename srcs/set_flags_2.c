/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolabi <yolabi@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 22:13:57 by yolabi            #+#    #+#             */
/*   Updated: 2017/08/10 22:13:59 by yolabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_space(t_env *env)
{
	env->space = 1;
	(env->curr)++;
}

void	set_h(t_env *env, const char *restrict format)
{
	env->h = 1;
	(env->curr)++;
	if (format[(env->curr)] == 'h')
	{
		env->hh = 1;
		(env->curr)++;
	}
}

void	set_l(t_env *env, const char *restrict format)
{
	env->l = 1;
	(env->curr)++;
	if (format[(env->curr)] == 'l')
	{
		env->ll = 1;
		(env->curr)++;
	}
}
