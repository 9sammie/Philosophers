/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:53:08 by maballet          #+#    #+#             */
/*   Updated: 2025/08/31 20:15:40 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static int	argv_check(int argc, char **argv)
{
	if (negative_check(argc, argv) != ALL_OK)
		return(ERR_PROMPT);
	if (digit_check(argc, argv) != ALL_OK)
		return(ERR_PROMPT);
	if (overflow_and_empty_check(argv) != ALL_OK)
		return(ERR_PROMPT);
	if (ft_atoi(argv[1]) > 200)
		return (p_ret_int(PHILO_MAX, ERR_PROMPT, NULL, 0));
	if (argv[5])
		if (ft_atoi(argv[5]) > 100)
			return (p_ret_int(MEAL_MAX, ERR_PROMPT, NULL, 0));
	return (0);
}

static int	argc_check(int argc)
{
	if (argc > 6)
		return (p_ret_int(TOO_MUCH_ARGC, ERR_PROMPT, NULL, 0));
	if (argc < 5)
		return (p_ret_int(TOO_FEW_ARGC, ERR_PROMPT, NULL, 0));
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
