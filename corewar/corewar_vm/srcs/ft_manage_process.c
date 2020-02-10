/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_process.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/14 07:34:41 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 11:31:10 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	add_dead_process(t_process *dead, t_vm *vm)
{
	t_process	*tmp;

	dead->next = NULL;
	dead->prev = NULL;
	if (!vm->dead_process)
		vm->dead_process = dead;
	else
	{
		tmp = vm->dead_process;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = dead;
	}
}

void	kill_process(t_process *tmp, t_process **process, int verbosity,
		t_vm *vm)
{
	t_process *next;

	next = tmp->next;
	if ((verbosity & 8))
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				tmp->nb, tmp->lcycle == -1 ? 0 :
				vm->cycle - tmp->lcycle, vm->death);
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		*process = next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	add_dead_process(tmp, vm);
}

void	ft_check_process_lives(t_process **process, int *last_live,
		t_vm *vm, int verbosity)
{
	t_process	*tmp;
	t_process	*next;

	tmp = *process;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->last_live < 0 && tmp->last_live >= -(vm->nb_players))
			*last_live = vm->death > 0 ? tmp->last_live : *last_live;
		if (tmp->live == -1 && vm->death > 0)
			tmp->live = 0;
		else
			kill_process(tmp, process, verbosity, vm);
		tmp = next;
	}
}

int		ft_count_lives(t_process *process)
{
	int			count;

	count = 0;
	while (process)
	{
		if (process->live > 0)
			process->live = -1;
		process = process->next;
	}
	return (count);
}

int		check_death(t_vm *vm, int *check, int *last_live, t_args *args)
{
	(*check)++;
	ft_count_lives(vm->process);
	ft_check_process_lives(&vm->process, last_live,
			vm, args->verbosity);
	if (*check >= MAX_CHECKS || vm->players[0]->nb_live >= NBR_LIVE)
	{
		vm->death -= CYCLE_DELTA;
		if (args->verbosity & 2)
			ft_printf("Cycle to die is now %d\n", vm->death);
		*check = 0;
	}
	vm->players[0]->nb_live = 0;
	return (vm->death <= 0 ? 1 : vm->death);
}
