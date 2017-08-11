/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolabi <yolabi@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 22:13:49 by yolabi            #+#    #+#             */
/*   Updated: 2017/08/10 22:13:52 by yolabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_octothorpe(t_env *env)
{
	env->octothorpe = 1;
	(env->curr)++;
}

void	set_zero(t_env *env)
{
	env->zero = 1;
	(env->curr)++;
}

void	set_minus(t_env *env)
{
	env->minus = 1;
	(env->curr)++;
}

void	set_plus(t_env *env)
{
	env->plus = 1;
	(env->curr)++;
}
