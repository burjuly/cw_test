/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdraugr- <cdraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:42:23 by cdraugr-          #+#    #+#             */
/*   Updated: 2019/10/20 22:00:16 by cdraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_error(char *message)
{
	ft_putstr_fd("\033[1;31m", 2);
	ft_putstr_fd(message, 2);
	ft_putendl_fd("\033[0m", 2);
	exit(1);
}

void	syntax_error(int32_t row, int32_t column)
{
	ft_putstr_fd("\033[1;31m", 2);
	ft_putstr_fd("ERROR: Invalid syntax at line #", 2);
	ft_putnbr_fd(row + 1, 2);
	ft_putstr_fd(" column #", 2);
	ft_putnbr_fd(column + 1, 2);
	ft_putendl_fd(".\033[0m", 2);
	exit(1);
}
