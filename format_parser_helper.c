/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:52:10 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 05:41:21 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const static char	*g_valid_flags = "# +0-";
const static char	*g_valid_types = "cspdiuxX%";

unsigned int	search_flag_char(char c)
{
	return ((c == g_valid_flags[0]) \
			+ ((c == g_valid_flags[1]) << 1) \
			+ ((c == g_valid_flags[2]) << 2) \
			+ ((c == g_valid_flags[3]) << 3) \
			+ ((c == g_valid_flags[4]) << 4));
}

int	search_type(char c)
{
	return (c * (c == g_valid_types[0]) \
		+ c * (c == g_valid_types[1]) \
		+ c * (c == g_valid_types[2]) \
		+ c * (c == g_valid_types[3]) \
		+ c * (c == g_valid_types[4]) \
		+ c * (c == g_valid_types[5]) \
		+ c * (c == g_valid_types[6]) \
		+ c * (c == g_valid_types[7]) \
		+ c * (c == g_valid_types[8]));
}

const char	*do_nothing(const char *format, struct s_format_info *fi)
{
	(void)fi;
	return (format);
}
