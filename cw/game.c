/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: draudrau <draudrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:06:16 by draudrau          #+#    #+#             */
/*   Updated: 2019/10/05 23:00:57 by draudrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

/*
** Важно, чтобы во время цикла все описанные проверки и действия выполнялись строго
** в указанной последовательности.
** Поскольку за один цикл одна и та же каретка может получить новый код операции и
** установить количество циклов до её исполнения. А также уменьшить это количество
** на единицу.
** Если бы существовала операция со всего одним циклом ожидания, то она также была
** бы выполнена во время этого одного цикла.
**
** "if" работают
**        парами первый и второй, либо второй и третий (поэтому не else)
**        либо только в второй
*/


void        ft_print_crg(t_crg *crg)
{
    int i = 0;

    while (i < 16)
    {
        printf("reg: %d = %d\n", i, crg->reg[i]);
        i++;
    }
        printf("pc = %d\n", crg->pc);
        printf("carry = %d\n", crg->carry);
        printf("cur_op = %d\n", crg->cur_op);
        printf("bef_op = %d\n", crg->bef_op);
        printf("last_live = %d\n", crg->last_live);
        printf("step = %d\n", crg->step);
}

void        ft_do_op(t_cw *cw, t_crg *crg)
{
    printf("До операции ld\n");
    ft_print_crg(crg);
    if (crg->cur_op == 2)
    {
        printf("ЗАШЛИ В ОПЕРАЦИЮ ld\n");
        op_ld(cw, crg);
    }
    printf("После операции ld\n");
    ft_print_crg(crg);
}



void        ft_do_cycle(t_cw *cw)
{
    t_crg    *temp;
    int        valid;

    temp = cw->crg;
    while (temp != NULL)
    {
        printf("\n\nNEXT CYCLE\n\n");
        // самый первый ход в игре => картеки пусты (коммент в кукбук)
        // т.е crg->cur_op = 0, bef_op = 0, pc = 0

        // 1) Устанавливаем код операции
            // Если во время прошлого цикла каретка передвигалась ...
        if (temp->bef_op == 0)     // Перемещение имело место быть
        {
            
            temp->cur_op = cw->map[temp->pc];    // Узнать код операции = считать байт, на котором находится каретка
            // Если полученное число соответствует коду реальной операции, то его необходимо запомнить
            // Запомнили на предыдущем этапе тк там повтор по тексту, поэтому можно и так
            if (temp->cur_op > 0 && temp->cur_op <= 16)
                temp->bef_op = cw->op[temp->cur_op - 1].ccl_cost;    // также нужно установить значение переменной, которая хранит количество циклов до исполнения операции.
                // temp->bef_op = g_op_tab[temp->cur_op - 1].ccl_cost;    // также нужно установить значение переменной, которая хранит количество циклов до исполнения операции.
            // Если считанное число не попадает в диапазон [0x01; 0x10],
            // то есть полученный код указывает на несуществующую операцию.
            // В этом случае необходимо запомнить считанный код, а значение переменной, 
            // хранящей количество циклов до выполнения, оставить равным нулю (все уже сделано).
        }
        printf("GAME after IF #1\n");
        ft_print_crg(temp);
        // 2) Уменьшить количество циклов до исполнения
            // Если количество циклов до выполнения, которое хранит соответствующая переменная в каретке, больше нуля
        if (temp->bef_op > 0)
            (temp->bef_op)--;
        printf("GAME after IF #2\n");
        ft_print_crg(temp);
        // 3) Выполнить операцию
            // Если количество циклов до исполнения равно нулю ...
        if (temp->bef_op == 0)
        {
            if (temp->cur_op > 0 && temp->cur_op <= 16)    // Если хранящийся код соответствует существующей операции ...
            {
                valid = 1;
                //valid = ft_valid_arg_and_reg(cw->map[temp->pc + 1]);    // тогда необходимо проверить на валидность код содержащий типы аргументов.
                if (valid > 0)    // Если данный код корректен и указывает, что среди аргументов операции есть регистр, необходимо также убедиться в корректности номера регистра. (регистры проверили на предыдущем шаге)
                 {
                     ft_do_op(cw, temp);    // Если все необходимые проверки были успешно пройдены, нужно выполнить операцию ...
                     (temp->pc)++;    // и передвинуть каретку на следующую позицию. (в ft_do_op она проедет до последнего байта операции)
                }
                //else    // Если с самим кодом все нормально, но код типов аргументов или же номер регистра ошибочен ...
                //    temp->pc += ft_skip_step(cw->op[temp->cur_op - 1], cw->map[temp->pc + 1]);    // нужно пропустить данную операцию вместе с кодом типов аргументов и самими аргументами.
            }
            else    // Если же код операции ошибочен ...
                (temp->pc)++; // необходимо просто переместить каретку на следующий байт.
        }
        printf("GAME after IF #3\n");
        ft_print_crg(temp);
        temp = temp->next;
    }
}

void    ft_del_carriage(t_cw *cw, t_crg *cur, t_crg *prev)
{
    t_crg *tmp;

    tmp = NULL;
    if (prev == NULL) // Если удаляемая каретка первая в списке
    {
        cw->crg = cur->next;
        tmp = cur;
        cur = cw->crg;
        free(tmp);
    }
    else
    {
        tmp = cur->next;
        free(cur);
        prev->next = tmp;
    }
}

void    ft_check(t_cw *cw)
{
    t_crg *curren_car;
    t_crg *prev_car;

    curren_car = cw->crg;
    prev_car = NULL;
    cw->checks++;
    while (curren_car != NULL)
    {
        if (curren_car->last_live > cw->c_to_die)
        {
            ft_del_carriage(cw, curren_car, prev_car);  // Доделать!
        }
        if (cw->count_live >= NBR_LIVE)
            cw->c_to_die = cw->c_to_die - CYCLE_DELTA;
        
        prev_car = curren_car;
        curren_car = curren_car->next;
    }
}

void    ft_start_game(t_cw *cw)
{
    t_crg *lst;

    while (cw->crg != NULL)
    {
        if (cw->c_to_die > 0)
        {
            lst = cw->crg;
            while (cw->round < cw->c_to_die)
            {
                ft_do_cycle(cw);
                cw->round++;  
            }
        }
        else // конец игры ?
        {
            ft_do_cycle(cw);
            cw->round++;
        }
        ft_check(cw);
    }
}