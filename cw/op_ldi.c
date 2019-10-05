/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waddam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:53:44 by waddam            #+#    #+#             */
/*   Updated: 2019/10/05 15:55:18 by waddam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_init_ldi(t_op *op)
{
	ft_init_arg1(op);
	ft_init_arg2(op);
	op->arg_nbrs = 3;
	op->ccl_cost = 25;
	op->need_arg_code = 1;
	op->low_tdir = 1;
}
