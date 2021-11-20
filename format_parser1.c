/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:49:34 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 05:45:27 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_process_type		g_process_type_next_function[2] = \
	{process_type, end_process_type};
static const t_process_flags	g_process_flags_next_function[2] = \
	{process_flags, end_process_flags};
static const t_process			g_is_max_len_exists[2] = \
	{do_nothing, process_max_len};

const char	*process_type(const char *format, struct s_format_info *fi)
{
	int	type;

	type = search_type(*format);
	fi->type = type;
	return (g_process_type_next_function[type != 0](format + 1, fi));
}

const char	*end_process_type(const char *format, struct s_format_info *fi)
{
	(void)fi;
	return (format - 1);
}

const char	*process_flags(const char *format, struct s_format_info *fi)
{
	unsigned int	flag;

	flag = search_flag_char(*format);
	fi->flag |= flag;
	return (g_process_flags_next_function[flag == 0](format + 1, fi));
}

const char	*end_process_flags(const char *format, struct s_format_info *fi)
{
	(void)fi;
	return (format - 1);
}

const char	*parse_format(const char *format, struct s_format_info *fi)
{
	fi->flag = 0;
	fi->max_len = 0;
	fi->min_len = 0;
	fi->type = 22;
	format = process_flags(format, fi);
	format = process_min_len(format, fi);
	format = g_is_max_len_exists[*format == '.'](format, fi);
	format = process_type(format, fi);
	return (format);
}
