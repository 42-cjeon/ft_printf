/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_stringf2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:48:37 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 03:16:19 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

struct s_string_info	char_to_string(char *buf, union u_arg *arg, struct s_format_info *fi)
{
	struct s_string_info si;

	init_si(&si);
	*buf = arg->c;
	si.main_part = buf;
	si.total_len = 1;
	return (si);
}

struct s_string_info	percent_sign_to_string(char *buf, union u_arg *arg, struct s_format_info *fi)
{
	struct s_string_info si;

	init_si(&si);
	*buf = '%';
	si.main_part = buf;
	si.total_len = 1;
	return (si);
}

void copy_null(char *buf)
{
	*buf++ = '(';
	*buf++ = 'n';
	*buf++ = 'u';
	*buf++ = 'l';
	*buf++ = 'l';
	*buf++ = ')';
}

size_t	strnlen(const char *str, size_t max_len);
size_t	end_strnlen(const char *str, size_t max_len);
typedef size_t (*strnlenf)(const char *str, size_t max_len);
static const strnlenf strnlen_next_function[2] = {strnlen, end_strnlen};
size_t	strnlen(const char *str, size_t max_len)
{
	return strnlen_next_function[(max_len < 1) || (*str == '\0')](str + 1, max_len - 1) + ((0 < max_len) && (*str != '\0'));
}

size_t	end_strnlen(const char *str, size_t max_len)
{
	(void)str;
	(void)max_len;
	return (0);
}
struct s_string_info	string_to_string(char *buf, union u_arg *arg, struct s_format_info *fi)
{
	size_t max_len;
	struct s_string_info si;

	init_si(&si);
	copy_null(buf);
	si.main_part = pointer_selector(arg->s, buf, arg->s == NULL);
	max_len = size_selector(~0U, fi->max_len, fi->flag & PRECISION);
	si.total_len = strnlen(si.main_part, max_len);
	return (si);
}