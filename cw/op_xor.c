/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waddam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:51:23 by waddam            #+#    #+#             */
/*   Updated: 2019/10/05 15:51:30 by waddam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_init_xor(t_op *op)
{
	ft_init_arg1(op);
	ft_init_arg2(op);
	op->arg_nbrs = 3;
	op->ccl_cost = 6;
	op->need_arg_code = 1;
	op->low_tdir = 0;
}
