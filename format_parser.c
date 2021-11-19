/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:49:34 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/19 01:54:22 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char *process_type(const char *format, struct s_format_info *fi)
{
	int type;

	type = search_type(*format);
	while (!type && *format)
	{
		format++;
		type = search_type(*format);
	}
	fi->type = type;
	return format;
}

const char *process_max_len(const char *format, struct s_format_info *fi)
{
	size_t max;

	max = 0;
	while (*format && is_digit(*format))
	{
		max = max * 10 + (*format - '0');
		format++;
	}
	fi->max_len = max;
	return format;
}

const char *process_min_len(const char *format, struct s_format_info *fi)
{
	size_t min;

	min = 0;
	while (*format && is_digit(*format))
	{
		min = min * 10 + (*format - '0');
		format++;
	}
	fi->min_len = min;
	return format;
}

const char *process_flags(const char *format, struct s_format_info *fi)
{

	unsigned int	flags;
	unsigned int	flag;

	flags = 0;
	flag = search_flag_char(*format);
	while (flag)
	{
		flags |= flag;
		format++;
		flag = search_flag_char(*format);
	}
	fi->flag = flags;
	return format;
}

const char *parse_format(const char *format, struct s_format_info *fi)
{
	fi->flag = 0;
	fi->max_len = (1UL<<63);
	fi->min_len = 0;
	fi->type = 22;
	format = process_flags(format, fi);
	format = process_min_len(format, fi);
	format = process_max_len(format, fi);
	format = process_type(format, fi);
	return format;
}