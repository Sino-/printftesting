/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolabi <yolabi@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 22:15:17 by yolabi            #+#    #+#             */
/*   Updated: 2017/08/10 22:17:08 by yolabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <wchar.h>
# include <locale.h>

typedef struct		s_env
{
	int				curr;
	int				bytes;
	char			conversion;
	unsigned int	width;
	unsigned int	precision;
	unsigned int	octothorpe	:1;
	unsigned int	zero		:1;
	unsigned int	minus		:1;
	unsigned int	plus		:1;
	unsigned int	space		:1;
	unsigned int	hh			:1;
	unsigned int	h			:1;
	unsigned int	l			:1;
	unsigned int	ll			:1;
	unsigned int	j			:1;
	unsigned int	z			:1;
}					t_env;

size_t				ft_strlen(char const *str);
char				*ft_strdup(char const *s);
int					ft_isdigit(int ascii_char);
int					ft_iswhitespace(char c);
void				find_width(t_env *env, const char *restrict format);
void				find_precision(t_env *env, const char *restrict format);
char				*ft_itoa_base(long long value, int base, int upper_case);
char				*ft_itoa_ubase(unsigned long long value, long base, \
					int upper_case);
void				reset_env(t_env *env);
void				init_env(t_env *env);
void				print_percent(t_env *env, const char *restrict format);
void				print_c(t_env *env, va_list ap);
void				print_string(t_env *env, char *str);
void				print_padding(t_env *env, char *str, char padding);
void				print_s(t_env *env, va_list ap);
void				print_number_padding(t_env *env, char *str);
void				print_number_string(t_env *env, char *str);
void				print_minus(t_env *env, char *str);
void				print_numbers(t_env *env, char *str);
void				print_nums(t_env *env, va_list ap, int base, \
					int upper_case);
void				print_u_nums(t_env *env, va_list ap, int base, \
					int upper_case);
void				print_p(t_env *env, va_list ap);
void				print_d(t_env *env, va_list ap);
void				print_cap_d(t_env *env, va_list ap);
void				print_o(t_env *env, va_list ap);
void				print_cap_o(t_env *env, va_list ap);
void				print_x(t_env *env, va_list ap);
void				print_cap_x(t_env *env, va_list ap);
void				set_octothorpe(t_env *env);
void				set_zero(t_env *env);
void				set_minus(t_env *env);
void				set_plus(t_env *env);
void				set_space(t_env *env);
void				set_h(t_env *env, const char *restrict format);
void				set_l(t_env *env, const char *restrict format);
void				parse_flags(t_env *env, const char *restrict format, \
					char fnd, int esc);
void				parse_conversion(t_env *env, const char *restrict format, \
					va_list ap);
int					ft_printf(const char *restrict format, ...);

#endif
