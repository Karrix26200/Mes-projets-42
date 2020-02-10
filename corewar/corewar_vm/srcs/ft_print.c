/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/13 12:03:52 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 19:51:18 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_print_usage(int ac)
{
	if (ac > 1)
		return ;
	ft_putstr("Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth");
	ft_putstr("][-a] <champion1.cor> <...>\n-a        :");
	ft_putendl(" Prints output from \"aff\" (Default is to hide it)");
	ft_putstr("#### TEXT OUTPUT MODE ########################################");
	ft_putendl("##################");
	ft_putendl("-d N      : Dumps memory after N cycles then exits");
	ft_putendl("-s N      : Runs N cycles, dumps memory, pauses, then repeats");
	ft_putstr("-v N      : Verbosity levels, can be added together to enable");
	ft_putendl(" several\n- 0 : Show only essentials");
	ft_putendl("- 1 : Show lives");
	ft_putendl("- 2 : Show cycles");
	ft_putendl("- 4 : Show operations (Params are NOT litteral ...)");
	ft_putendl("- 8 : Show deaths");
	ft_putendl("- 16 : Show PC movements (Except for jumps)");
	ft_putstr("#### BINARY OUTPUT MODE ######################################");
	ft_putendl("##################");
	ft_putendl("-b        : Binary output mode for corewar.42.fr");
	ft_putendl("--stealth : Hides the real contents of the memory");
	ft_putstr("############################################################");
	ft_putendl("####################");
}

void	ft_print_reg(long *reg)
{
	int		i;

	i = -1;
	while (++i < 16)
		ft_printf("reg %i = %lld\n", i, reg[i]);
}

int		ft_print_mem(t_vm *vm)
{
	t_mem	*curr;
	int		i;
	char	*buff;

	curr = vm->mem;
	buff = NULL;
	buff = ft_strdup("");
	i = 0;
	while (curr && (i == 0 || curr != vm->mem))
	{
		if (i % 64 == 0)
			buff = ft_strfjoin(buff,
				ft_strfjoin(ft_strdup(COLOR ? "\x1B[0m" : ""),
					ft_strfjoin(ft_strdup(i == 0 ? "0x" : "\n0x"),
						ft_strfjoin(ft_get_hex(i, 4), ft_strdup(" : ")))));
		buff = ft_strfjoin(buff,
			ft_strfjoin(ft_get_color(curr->player, curr, vm->process),
				ft_strfjoin(ft_get_hex(curr->byte, 2), ft_strdup(" "))));
		curr = curr->next;
		i++;
	}
	buff = ft_strfjoin(buff, ft_strdup("\n"));
	write(1, buff, ft_strlen(buff));
	ft_strdel(&buff);
	return (1);
}
