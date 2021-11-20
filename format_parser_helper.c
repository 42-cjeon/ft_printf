/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:52:10 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 07:02:20 by cjeon            ###   ########.fr       */
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

void	init_si(struct s_string_info *si)
{
	si->left_sign = 0;
	si->prefix[0] = '\0';
	si->prefix[1] = '\0';
	si->prefix[2] = '\0';
	si->mid_padding = 0;
	si->total_len = 0;
	si->main_part = NULL;
}
