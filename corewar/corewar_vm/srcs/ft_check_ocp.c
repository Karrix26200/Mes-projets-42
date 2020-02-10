/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_ocp.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/15 04:12:50 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 13:33:37 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_check_reg(char reg)
{
	if (reg < 1 || reg > 16)
		return (0);
	return (1);
}

int		ft_check_comp(t_mem *mem, char ocp, int decal)
{
	if (((ocp >> (6 - decal)) & 0x03) == REG_CODE)
	{
		if (decal == 4)
			return (ft_check_reg(mem->byte));
		return (ft_check_reg(mem->byte)
				&& ft_check_comp(mem->next, ocp, decal + 2));
	}
	else if (decal == 4)
		return (0);
	else if (((ocp >> (6 - decal)) & 0x03) == DIR_CODE)
		return (ft_check_comp(mem->next->next->next->next, ocp, decal + 2));
	else if (((ocp >> (6 - decal)) & 0x03) == IND_CODE)
		return (ft_check_comp(mem->next->next, ocp, decal + 2));
	return (0);
}

int		ft_check_load(t_mem *mem)
{
	if ((mem->next->byte & 0xf0) == (DIR_CODE << 6) + (REG_CODE << 4))
		return (ft_check_reg(mem->next->next->next->next->next->next->byte));
	else if ((mem->next->byte & 0xf0) == (IND_CODE << 6) + (REG_CODE << 4))
		return (ft_check_reg(mem->next->next->next->next->byte));
	else
		return (0);
	return (0);
}

int		ft_check_aff(t_mem *mem)
{
	if (!ft_check_reg(mem->next->next->byte))
		return (0);
	return (1);
}

int		ft_check_ocp(t_mem *mem, int opcode)
{
	if (opcode == 0x02 || opcode == 0x0d)
		return (ft_check_load(mem));
	else if (opcode == 0x03)
		return (ft_check_store(mem));
	else if (opcode == 0x04 || opcode == 0x05)
		return (ft_check_add(mem));
	else if (opcode == 0x06 || opcode == 0x07 || opcode == 0x08)
		return (ft_check_comp(mem->next->next, mem->next->byte, 0));
	else if (opcode == 0x0a || opcode == 0x0e)
		return (ft_check_load_index(mem));
	else if (opcode == 0x0b)
		return (ft_check_store_index(mem));
	else if (opcode == 0x10)
		return (ft_check_aff(mem));
	return (1);
}
