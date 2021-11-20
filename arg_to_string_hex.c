/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_string_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:48:10 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 06:40:01 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const static char	*g_hex_low_digits = "0123456789abcdef";
const static char	*g_hex_high_digits = "0123456789ABCDEF";

struct s_string_info	pointer_to_string(char *buf, union u_arg *arg, \
											struct s_format_info *fi)
{
	struct s_string_info	si;

	(void)fi;
	init_si(&si);
	buf[0] = '0';
	buf[1] = 'x';
	si.total_len = 2 + itoa_ulong(buf + 2, arg->p, 16, g_hex_low_digits);
	si.main_part = buf;
	return (si);
}

struct s_string_info	uhex_low_to_string(char *buf, union u_arg *arg, \
											struct s_format_info *fi)
{
	size_t					main_len;
	size_t					prefix_len;
	struct s_string_info	si;

	init_si(&si);
	si.prefix[0] = int_selector('\0', '0', \
									(fi->flag & ALT_MOD) && (arg->u != 0));
	si.prefix[1] = int_selector('\0', 'x', \
									(fi->flag & ALT_MOD) && (arg->u != 0));
	prefix_len = (fi->flag & ALT_MOD) * (arg->u != 0) * 2;
	main_len = itoa_ulong(buf, arg->u, 16, g_hex_low_digits);
	main_len -= ((fi->flag & PRECISION) && arg->u == 0);
	si.mid_padding = ((fi->flag & PRECISION) != 0) \
						* (main_len < fi->max_len) \
						* (fi->max_len - main_len);
	si.main_part = buf;
	si.total_len = main_len + prefix_len + si.mid_padding;
	return (si);
}

struct s_string_info	uhex_high_to_string(char *buf, union u_arg *arg, \
												struct s_format_info *fi)
{
	size_t					main_len;
	size_t					prefix_len;
	struct s_string_info	si;

	init_si(&si);
	si.prefix[0] = int_selector('\0', '0', \
									(fi->flag & ALT_MOD) && (arg->u != 0));
	si.prefix[1] = int_selector('\0', 'X', \
									(fi->flag & ALT_MOD) && (arg->u != 0));
	prefix_len = (fi->flag & ALT_MOD) * (arg->u != 0) * 2;
	main_len = itoa_ulong(buf, arg->u, 16, g_hex_high_digits);
	main_len -= ((fi->flag & PRECISION) && arg->u == 0);
	si.mid_padding = ((fi->flag & PRECISION) != 0) \
						* (main_len < fi->max_len) \
						* (fi->max_len - main_len);
	si.main_part = buf;
	si.total_len = main_len + prefix_len + si.mid_padding;
	return (si);
}
