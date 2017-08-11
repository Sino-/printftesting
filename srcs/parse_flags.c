#include "ft_printf.h"

void	parse_flags(t_env *env, const char *restrict format, char found, int esc)
{
	while (found || esc < 4)
	{
		found = 1;
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
			found = 0;
			esc++;
		}
	}
}
