/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_new.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/13 12:03:07 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 19:46:05 by sbedene     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_op		*ft_new_op(char opcode, void (*ft)(t_process *process,
			t_mem *mem, int verb, t_player **players), int cast)
{
	t_op	*op;

	if (!(op = (t_op *)malloc(sizeof(t_op))))
		return (NULL);
	op->opcode = opcode;
	op->cast = cast;
	op->ft = ft;
	return (op);
}

t_player	*ft_new_player(int j, int fd, char *champ, int n)
{
	int			i;
	t_player	*new_player;

	new_player = NULL;
	if (!(new_player = (t_player *)malloc(sizeof(t_player))) && n)
		return (NULL);
	i = 0;
	new_player->nb = j;
	new_player->nb_live = 0;
	new_player->place = n;
	if (!(new_player->buffer = ft_get_bin(fd, &new_player->size,
		champ, new_player)))
	{
		free(new_player);
		return (NULL);
	}
	if (new_player->size < COMMENT_LENGTH + PROG_NAME_LENGTH + 16)
	{
		ft_fdprintf(2, "Error: File %s is too small to be a champion\n", champ);
		ft_strdel(&new_player->buffer);
		free(new_player);
		return (NULL);
	}
	return (new_player);
}

t_mem		*ft_memnew(t_mem *prev, char byte, int color, int addr)
{
	t_mem	*mem_new;

	if (!(mem_new = (t_mem *)malloc(sizeof(t_mem))))
		return (NULL);
	mem_new->addr = addr;
	mem_new->byte = byte;
	mem_new->prev = prev;
	mem_new->next = NULL;
	mem_new->player = color;
	return (mem_new);
}

t_process	*ft_new_process(t_process **first, int nb, t_mem *mem)
{
	int				i;
	static	int		number = 0;
	t_process		*process;

	if (!(process = (t_process *)malloc(sizeof(t_process)))
	|| !(process->reg = (long *)malloc(16 * sizeof(long))))
		return (NULL);
	process->reg[0] = nb;
	i = 1;
	while (i < 16)
		process->reg[i++] = 0;
	process->carry = 0;
	process->next = *first;
	process->mem = mem;
	process->pc = 0;
	process->opcode = mem->byte;
	process->cast = -1;
	process->last_live = 0;
	process->lcycle = 0;
	process->live = 0;
	process->nb = ++number;
	process->mem_bu = NULL;
	if (process->next)
		process->next->prev = process;
	return (process);
}
