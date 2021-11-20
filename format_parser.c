/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:49:34 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 04:15:48 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char *process_type(const char *format, struct s_format_info *fi);
const char *end_process_type(const char *format, struct s_format_info *fi);
typedef const char *(*process_typef)(const char *format, struct s_format_info *fi);
static const process_typef process_type_next_function[2] = {process_type, end_process_type};
const char *process_type(const char *format, struct s_format_info *fi)
{
	int type;

	type = search_type(*format);
	fi->type = type;
	return process_type_next_function[type != 0](format + 1, fi);
}
const char *end_process_type(const char *format, struct s_format_info *fi)
{
	(void)fi;
	return (format - 1);
}

const char *atoi(const char *format, size_t *result);
const char *end_atoi(const char *format, size_t *result);
typedef const char *(*atoif)(const char *format, size_t *result);
static const atoif atoi_next_function[2] = {atoi, end_atoi};
const char *atoi(const char *format, size_t *result)
{
	*result = int_selector(*result, *result * 10 + (*format - '0'), is_digit(*format));
	return atoi_next_function[!is_digit(*format)](format + 1, result);
}
const char *end_atoi(const char *format, size_t *result)
{
	(void)result;
	return (format - 1);
}

const char *process_max_len(const char *format, struct s_format_info *fi)
{
	size_t max_len;

	max_len = 0;
	format++;
	format = atoi(format, &max_len);
	fi->max_len = max_len;
	fi->flag |= PRECISION;
	return (format);
}

const char *process_min_len(const char *format, struct s_format_info *fi)
{
	size_t min_len;

	min_len = 0;
	format = atoi(format, &min_len);
	fi->min_len = min_len;
	return format;
}

const char *process_flags(const char *format, struct s_format_info *fi);
const char *end_process_flags(const char *format, struct s_format_info *fi);
typedef const char *(*process_flagsf)(const char *format, struct s_format_info *fi);
static const process_flagsf process_flags_next_function[2] = {process_flags, end_process_flags};

const char *process_flags(const char *format, struct s_format_info *fi)
{
	unsigned int	flag;

	flag = search_flag_char(*format);
	fi->flag |= flag;
	return process_flags_next_function[flag == 0](format + 1, fi);
}

const char *end_process_flags(const char *format, struct s_format_info *fi)
{
	(void)fi;
	return (format - 1);
}

typedef const char *(*processf)(const char *format, struct s_format_info *fi);

const char *do_nothing(const char *format, struct s_format_info *fi)
{
	return (format);
}

static const processf is_max_len_exists[2] = {do_nothing, process_max_len};
const char *parse_format(const char *format, struct s_format_info *fi)
{
	
	fi->flag = 0;
	fi->max_len = 0;
	fi->min_len = 0;
	fi->type = 22;
	format = process_flags(format, fi);
	format = process_min_len(format, fi);
	format = is_max_len_exists[*format == '.'](format, fi);
	format = process_type(format, fi);
	return format;
}