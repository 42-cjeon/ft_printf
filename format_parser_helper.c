/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:52:10 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 03:36:01 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const static char *valid_flags = "# +0-";
const static char *valid_types = "cspdiuxX%";

typedef unsigned int (*search_flag_charf)(char c);

unsigned int search_flag_char(char c)
{
	return ((c == valid_flags[0]) + ((c == valid_flags[1]) << 1) + ((c == valid_flags[2]) << 2) + ((c == valid_flags[3]) << 3) + ((c == valid_flags[4]) << 4));
}

int search_type(char c)
{
	return (c * (c == valid_types[0])
			+ c * (c == valid_types[1])
			+ c * (c == valid_types[2])
			+ c * (c == valid_types[3])
			+ c * (c == valid_types[4])
			+ c * (c == valid_types[5])
			+ c * (c == valid_types[6])
			+ c * (c == valid_types[7])
			+ c * (c == valid_types[8]));
}