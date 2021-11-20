/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 04:52:39 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 05:43:34 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_parser			g_with_end_state_normal[2] = \
	{parse_normal_string, end_parse_string};
static const t_parser			g_with_end_state_format[2] = \
	{parse_format_string, end_parse_string};
static const t_find_normal_end	g_find_normal_end_next_function[2] = \
	{find_normal_end, end_find_normal_end};

size_t	find_normal_end(const char *format)
{
	size_t	result;

	result = (*format && *format != '%');
	return (g_find_normal_end_next_function[!result](format + 1) + result);
}

size_t	end_find_normal_end(const char *format)
{
	(void)format;
	return (0);
}

ssize_t	parse_normal_string(const char *format, va_list *va)
{
	ssize_t	result;
	size_t	word_len;

	word_len = find_normal_end(format);
	result = write(1, format, word_len);
	format += word_len;
	return (g_with_end_state_format[*format == '\0'](format + 1, va) + result);
}

ssize_t	parse_format_string(const char *format, va_list *va)
{
	ssize_t					result;
	struct s_format_info	fi;

	format = parse_format(format, &fi);
	result = print_arg_with_format(&fi, va);
	return (g_with_end_state_normal[*format == '\0'](format + 1, va) + result);
}

ssize_t	end_parse_string(const char *format, va_list *va)
{
	(void)format;
	(void)va;
	return (0);
}
