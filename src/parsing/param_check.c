/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:53:08 by maballet          #+#    #+#             */
/*   Updated: 2025/08/26 06:53:00 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

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
	return (0);
}

static int	argv_check(int argc, char **argv)
{
	if (string_is_not_digit(argv[1])
			|| string_is_not_digit(argv[2])
			|| string_is_not_digit(argv[3])
			|| string_is_not_digit(argv[4]))
		return (print_return_int(NOT_DIGIT, ERR_PROMPT));
	if ((argc == 6 && string_is_not_digit(argv[5])))
		return (print_return_int(NOT_DIGIT, ERR_PROMPT));
	if (ft_atoi(argv[1]) > 200)
		return (print_return_int(PHILO_MAX, ERR_PROMPT));
	return (0);
}

static int	argc_check(int argc)
{
	if (argc > 6)
		return (print_return_int(TOO_MUCH_ARGC, ERR_PROMPT));
	if (argc < 5)
		return (print_return_int(TOO_FEW_ARGC, ERR_PROMPT));
	return (ALL_OK);
}

int	param_check(int argc, char **argv)
{
	if (argc_check(argc) != ALL_OK)
		return (ERR_PROMPT);
	if (argv_check(argc, argv) != ALL_OK)
		return (ERR_PROMPT);
	return (ALL_OK);
}
