/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_string_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:48:37 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 05:32:00 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

struct s_string_info	char_to_string(char *buf, union u_arg *arg, \
										struct s_format_info *fi)
{
	struct s_string_info	si;

	(void)fi;
	init_si(&si);
	*buf = arg->c;
	si.main_part = buf;
	si.total_len = 1;
	return (si);
}

struct s_string_info	percent_sign_to_string(char *buf, union u_arg *arg, \
												struct s_format_info *fi)
{
	struct s_string_info	si;

	(void)arg;
	(void)fi;
	init_si(&si);
	*buf = '%';
	si.main_part = buf;
	si.total_len = 1;
	return (si);
}

struct s_string_info	string_to_string(char *buf, union u_arg *arg, \
											struct s_format_info *fi)
{
	size_t					max_len;
	struct s_string_info	si;

	init_si(&si);
	copy_null(buf);
	si.main_part = pointer_selector(arg->s, buf, arg->s == NULL);
	max_len = size_selector(~0U, fi->max_len, fi->flag & PRECISION);
	si.total_len = strnlen(si.main_part, max_len);
	return (si);
}
