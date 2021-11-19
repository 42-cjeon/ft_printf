/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:52:10 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/19 01:57:13 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const static char *valid_flags = "# +0-";
const static char *valid_types = "cspdiuxX%";

unsigned int search_flag_char(char c)
{
	int i;

	i = 0;
	while (valid_flags[i] && valid_flags[i] != c)
		i++;
	return ((1>>(i==5))<<i);
}

int search_type(char c)
{
	int i;

	i = 0;
	while (valid_types[i] && valid_types[i] != c)
		i++;
	return valid_types[i];
}