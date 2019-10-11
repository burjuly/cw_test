/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: draudrau <draudrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:34:26 by waddam            #+#    #+#             */
/*   Updated: 2019/10/11 20:44:49 by draudrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_init_st(t_op *op)
{
	op->arg_nbrs = 2;
	op->bef_op = 5;
	op->need_arg_code = 1;
	op->t_dir = 4;

	op->code_args[0] = REG_REG;
	op->code_args[1] = REG_IND;
	op->code_args[2] = '\0';
}

void	op_st(t_cw *cw, t_crg *crg)
{
	t_args args;

	ft_bzero(&args, sizeof(args));
	args.code_args = crg->code_args;
	args.pc_arg1 = (PC + OP_NAME + CODE_ARGS) % MEM_SIZE;
	args.pc_arg2 = (args.pc_arg1 + REG_NUM_SIZE) % MEM_SIZE;
	ft_REG(cw, crg, &args, 1);
	if (args.code_args == REG_REG)
	{
		args.arg2 = cw->map[args.pc_arg2];
		//ft_REG(cw, crg, &args, 2);
		crg->reg[args.arg2 - 1] = args.arg1;
		//crg->step = 4;
	}
	else if (args.code_args == REG_IND)
	{
		args.arg2 = ft_reverse_2(cw, args.pc_arg2) % IDX_MOD;
		args.arg2 = ft_MOD_IND(args.arg2);
		args.address = (PC + args.arg2) % MEM_SIZE;
		ft_write_int_in_map(cw, args.address, args.arg1);
		//crg->step = 5;
	}
	ft_print_args(&args);
	//PC = (PC + crg->step) % MEM_SIZE;
	//crg->step = 0;
}
