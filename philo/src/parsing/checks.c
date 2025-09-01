/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:33:41 by maballet          #+#    #+#             */
/*   Updated: 2025/09/01 19:12:06 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	string_is_not_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (ALL_OK);
}

int	digit_check(int argc, char **argv)
{
	if (string_is_not_digit(argv[1])
		|| string_is_not_digit(argv[2])
		|| string_is_not_digit(argv[3])
		|| string_is_not_digit(argv[4]))
		return (p_ret_int(NOT_DIGIT, ERR_PROMPT, NULL, 0));
	if ((argc == 6 && string_is_not_digit(argv[5])))
		return (p_ret_int(NOT_DIGIT, ERR_PROMPT, NULL, 0));
	return (ALL_OK);
}

int	negative_check(int argc, char **argv)
{
	if (argv[1][0] == '-'
		|| argv[2][0] == '-'
		|| argv[3][0] == '-'
		|| argv[4][0] == '-')
		return (p_ret_int(NOT_POSITIVE, ERR_PROMPT, NULL, 0));
	if ((argc == 6 && argv[5][0] == '-'))
		return (p_ret_int(NOT_POSITIVE, ERR_PROMPT, NULL, 0));
	return (ALL_OK);
}

int	overflow_and_empty_check(char **argv)
{
	if (ft_atouint_overflow(argv[2]) == UINT_MAX
		|| ft_atouint_overflow(argv[3]) == UINT_MAX
		|| ft_atouint_overflow(argv[4]) == UINT_MAX)
		return (p_ret_int(OVERFLOW, ERR_PROMPT, NULL, 0));
	if (ft_atouint_overflow(argv[2]) == UINT_MAX -1
		|| ft_atouint_overflow(argv[3]) == UINT_MAX -1
		|| ft_atouint_overflow(argv[4]) == UINT_MAX -1)
		return (p_ret_int(EMPTY_PARAM, ERR_PROMPT, NULL, 0));
	if (argv[5])
	{
		if (ft_atouint_overflow(argv[5]) == UINT_MAX)
			return (p_ret_int(OVERFLOW, ERR_PROMPT, NULL, 0));
		if (ft_atouint_overflow(argv[5]) == UINT_MAX -1)
			return (p_ret_int(EMPTY_PARAM, ERR_PROMPT, NULL, 0));
	}
	return (ALL_OK);
}
