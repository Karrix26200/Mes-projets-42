/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/13 12:01:53 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 20:01:27 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_args		*ft_init_args(t_args *args, int *i)
{
	*i = 1;
	if (!(args = (t_args *)malloc(sizeof(t_args))))
		return (NULL);
	args->aff = 0;
	args->dump = -1;
	args->binary = 0;
	args->pause = -1;
	args->verbosity = -1;
	args->ncurse = 0;
	return (args);
}

t_vm		*ft_init_vm(t_vm *vm)
{
	int		i;

	if (!(vm = (t_vm *)malloc(sizeof(t_vm))))
		return (NULL);
	vm->mem = NULL;
	if (!(vm->players = (t_player **)malloc(5 * sizeof(t_player *))))
		return (NULL);
	i = 0;
	while (i < 5)
	{
		vm->players[i] = NULL;
		i++;
	}
	vm->process = NULL;
	vm->death = CYCLE_TO_DIE;
	vm->cycle = 0;
	vm->nb_players = 0;
	vm->dead_process = NULL;
	return (vm);
}

int			init_playerprog(t_vm *vm, int *p, int *addr, t_mem **curr)
{
	int		j;

	j = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	while (vm->players[*p - 1] && j < (MEM_SIZE / vm->nb_players)
		+ PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
	{
		if ((!vm->mem && !(vm->mem = ft_memnew(NULL,
			j < vm->players[*p - 1]->size ?
				vm->players[*p - 1]->buffer[j] : 0,
					j < vm->players[*p - 1]->size ? *p - 1 : -1, (*addr)++)))
						|| (*curr && !((*curr)->next = ft_memnew((*curr),
							j < vm->players[*p - 1]->size
								? vm->players[*p - 1]->buffer[j] : 0,
									j < vm->players[*p - 1]->size
										? *p - 1 : -1, (*addr)++))))
			return (0);
		(*curr) = (vm->mem->next ? (*curr)->next : vm->mem);
		j++;
	}
	(*p)++;
	return (1);
}

t_mem		*ft_init_vm_mem(t_vm *vm)
{
	int		i;
	int		j;
	int		p;
	int		addr;
	t_mem	*curr;

	i = 0;
	p = 1;
	curr = NULL;
	addr = 0;
	while (i < MEM_SIZE && (j = PROG_NAME_LENGTH + COMMENT_LENGTH + 16))
	{
		if (!init_playerprog(vm, &p, &addr, &curr))
			return (NULL);
		i += (MEM_SIZE / vm->nb_players);
		if (i + 1 == MEM_SIZE && vm->nb_players % 2 == 1)
		{
			i++;
			curr->next = ft_memnew(curr, 0, -1, addr++);
			curr = curr->next;
		}
	}
	curr->next = vm->mem;
	vm->mem->prev = curr;
	return (vm->mem);
}

t_process	*ft_init_process(t_vm *vm)
{
	int			i;
	int			j;
	t_mem		*mem;

	i = 0;
	j = 0;
	mem = vm->mem;
	while (i < vm->nb_players)
	{
		while (mem && j < (MEM_SIZE / vm->nb_players) * i)
		{
			mem = mem->next;
			j++;
		}
		if (!(vm->process = ft_new_process(&vm->process, -1 - i, mem)))
			return (NULL);
		vm->process->player = i;
		i++;
	}
	vm->process->prev = NULL;
	return (vm->process);
}
