/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:53:08 by maballet          #+#    #+#             */
/*   Updated: 2025/08/07 17:13:28 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static int	argc_check(int argc)
{
	if (argc > 6)
		return (print_return_int(TOO_MUCH_ARGC, ERR_PROMPT));
	if (argc < 5)
		return (print_return_int(TOO_FEW_ARGC, ERR_PROMPT));
	return (ALL_OK);
}

static int	argv_check(char **argv)
{
	if (ft_atoi(argv[1]) > 200)
		return (print_return_int(TOO_FEW_ARGC, ERR_PROMPT));
	
}

int	param_check(int argc, char **argv)
{
	if (argc_check(argc) != ALL_OK)
		return (ERR_PROMPT);
	if (argv_check(argv) != ALL_OK)
		return (ERR_PROMPT);
	return (ALL_OK);
}