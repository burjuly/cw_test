/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: draudrau <draudrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:02:45 by waddam            #+#    #+#             */
/*   Updated: 2019/10/05 18:42:22 by draudrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../corewar.h"

void	ft_init_lfork(t_op *op)
{
	op->arg_nbrs = 1;
	op->ccl_cost = 1000;
	op->need_arg_code = 0;
	op->low_tdir = 1;

	op->code_args[0] = 128; //  DIR
	op->code_args[1] = '\0';
}
