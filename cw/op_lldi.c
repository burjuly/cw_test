/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: draudrau <draudrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:08:26 by draudrau          #+#    #+#             */
/*   Updated: 2019/10/20 19:26:45 by draudrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_init_lldi(t_op *op)
{
	op->arg_nbrs = 3;
	op->bef_op = 50;
	op->need_arg_code = 1;
	op->t_dir = 2;
	op->code_args[0] = REG_REG_REG;
	op->code_args[1] = REG_DIR_REG;
	op->code_args[2] = IND_REG_REG;
	op->code_args[3] = IND_DIR_REG;
	op->code_args[4] = DIR_REG_REG;
	op->code_args[5] = DIR_DIR_REG;
	op->code_args[6] = '\0';
}

void	ft_lldi_REG(t_cw *cw, t_crg *crg, t_args *args)
{
	ft_REG(cw, crg, args, 1);
	if (args->code_args == REG_REG_REG)
	{
		args->pc_arg2 = args->pc_arg1 + REG_NUM_SIZE;
		args->pc_arg3 = args->pc_arg2 + REG_NUM_SIZE;
		ft_REG(cw, crg, args, 2);
	}
	else if (args->code_args == REG_DIR_REG)
	{
		args->pc_arg2 = args->pc_arg1 + REG_NUM_SIZE;
		args->pc_arg3 = args->pc_arg2 + DIR_2;
		ft_DIR_2(cw, args, 2);
	}
}

void	ft_lldi_IND(t_cw *cw, t_crg *crg, t_args *args)
{
	ft_IND_with_IDX_MOD(cw, crg, args, 1);
	args->pc_arg2 = args->pc_arg1 + IND;
	if (args->code_args == IND_REG_REG)
	{
		ft_REG(cw, crg, args, 2);
		args->pc_arg3 = args->pc_arg2 + REG_NUM_SIZE;
	}
	else if (args->code_args == IND_DIR_REG)
	{
		ft_DIR_2(cw, args, 2);
		args->pc_arg3 = args->pc_arg2 + DIR_2;
	}
}

void	ft_lldi_DIR(t_cw *cw, t_crg *crg, t_args *args)
{
	ft_DIR_2(cw, args, 1);
	args->pc_arg2 = args->pc_arg1 + DIR_2;
	if (args->code_args == DIR_REG_REG)
	{
		ft_REG(cw, crg, args, 2);
		args->pc_arg3 = args->pc_arg2 + REG_NUM_SIZE;
	}
	else if (args->code_args == DIR_DIR_REG)
	{
		ft_DIR_2(cw, args, 2);
		args->pc_arg3 = args->pc_arg2 + DIR_2;
	}
}

void	op_lldi(t_cw *cw, t_crg *crg)
{
	t_args	args;

	ft_bzero(&args, sizeof(args));
	args.code_args = crg->code_args;
	args.pc_arg1 = PC + OP_NAME + CODE_ARGS;
	if (args.code_args == REG_REG_REG || args.code_args == REG_DIR_REG)
		ft_lldi_REG(cw, crg, &args);
	else if (args.code_args == IND_REG_REG || args.code_args == IND_DIR_REG)
		ft_lldi_IND(cw, crg, &args);
	else if (args.code_args == DIR_REG_REG || args.code_args == DIR_DIR_REG)
		ft_lldi_DIR(cw, crg, &args);
	args.arg3 = (int)cw->map[args.pc_arg3];
	args.address = args.arg1 + args.arg2;
	crg->reg[args.arg3 - 1] = ft_reverse_4(cw, ((PC + args.address))
	% MEM_SIZE);
	if (crg->reg[args.arg3 - 1] == 0)
		crg->carry = 1;
	else
		crg->carry = 0;
}
