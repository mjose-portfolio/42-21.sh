/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_keys_adv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 06:46:36 by mjose             #+#    #+#             */
/*   Updated: 2019/03/29 11:02:21 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh21.h"

void	exp_key_altern(char **str, t_expand *expand)
{
	t_analyzer	to_analy;

	init_analyzer(&to_analy, str, expand);
	if (!to_analy.wlcd_len && (!to_analy.varvalue
			|| ft_strequ(to_analy.varname, "")))
	{
		if (!to_analy.varvalue && to_analy.wildcard)
			print_exp_error(*str + 1);
		else
			print_exp_str_error(*str);
		ft_strdel(str);
		*str = ft_strdup(" ");
		end_analyzer(to_analy);
		return ;
	}
	reassign_str_altern(str, &to_analy);
	end_analyzer(to_analy);
}

void	exp_key_double_hash(char **str, t_expand *expand)
{
	t_analyzer	to_analy;
	char		*run_varvalue;
	char		*run_wildcard;

	init_analyzer(&to_analy, str, expand);
	run_varvalue = to_analy.varvalue;
	run_wildcard = to_analy.wildcard;
	if (to_analy.start_astrsk)
		run_wildcard++;
	if (to_analy.varvalue && !to_analy.asterisk)
		asign_vrvlufnd(&to_analy, &run_varvalue, &run_wildcard, str);
	else if (to_analy.varvalue && to_analy.start_astrsk && !to_analy.end_astrsk)
		asgnvrvluastrk(&to_analy, &run_varvalue, &run_wildcard, str);
	else if (to_analy.varvalue && to_analy.end_astrsk && !to_analy.start_astrsk)
	{
		run_wildcard[to_analy.wlcd_len] = '\0';
		ft_strdel(str);
		if (ft_strnstr(run_varvalue, run_wildcard, to_analy.vvlu_len))
			*str = ft_strdup("");
		else
			*str = ft_strdup(to_analy.varvalue);
	}
	else
		rmv_str(str);
	end_analyzer(to_analy);
}

void	exp_key_double_percent(char **str, t_expand *expand)
{
	t_analyzer	to_analy;
	char		*run_wildcard;
	int			i;

	i = 0;
	init_analyzer(&to_analy, str, expand);
	if (!to_analy.varname[0])
	{
		print_exp_error(*str + 1);
		end_analyzer(to_analy);
		ft_strdel(str);
		*str = ft_strdup(" ");
		return ;
	}
	if (to_analy.start_astrsk)
		run_wildcard = to_analy.wildcard + 2;
	if (to_analy.varvalue && !to_analy.asterisk)
		ass_str_wout_ast(&to_analy, str);
	else if (to_analy.varvalue && to_analy.start_astrsk && !to_analy.end_astrsk)
		ass_str_wstrt_ast(&to_analy, str);
	else if (to_analy.varvalue && to_analy.end_astrsk && !to_analy.start_astrsk)
		ass_str_wend_ast(&to_analy, str);
	else
		rmv_str(str);
	end_analyzer(to_analy);
}
