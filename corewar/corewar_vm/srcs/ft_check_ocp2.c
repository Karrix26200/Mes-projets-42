/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_ocp2.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 09:45:36 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 13:36:23 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_check_store(t_mem *mem)
{
	if ((mem->next->byte & 0xf0) == (REG_CODE << 6) + (IND_CODE << 4))
		return (ft_check_reg(mem->next->next->byte));
	else if ((mem->next->byte & 0xf0) == (REG_CODE << 6) + (REG_CODE << 4))
		return (ft_check_reg(mem->next->next->byte)
			&& ft_check_reg(mem->next->next->next->byte));
	else
		return (0);
	return (0);
}

int		ft_check_add(t_mem *mem)
{
	if ((mem->next->byte & 0xfc)
		== (REG_CODE << 6) + (REG_CODE << 4) + (REG_CODE << 2))
		return (ft_check_reg(mem->next->next->byte)
			&& ft_check_reg(mem->next->next->next->byte)
				&& ft_check_reg(mem->next->next->next->next->byte));
	else
		return (0);
	return (0);
}

int		ft_check_load_index(t_mem *mem)
{
	if (((mem->next->byte) >> 6) == REG_CODE)
	{
		if (!(ft_check_reg(mem->next->next->byte)))
			return (0);
		if (((mem->next->byte >> 4) & 0x03) == REG_CODE)
		{
			return (ft_check_reg(mem->next->next->next->byte)
				&& ft_check_reg(mem->next->next->next->next->byte));
		}
		return (ft_check_reg(mem->next->next->next->next->next->byte));
	}
	else
	{
		if (((mem->next->byte >> 4) & 0x03) == REG_CODE)
		{
			return (ft_check_reg(mem->next->next->next->next->byte)
				&& ft_check_reg(mem->next->next->next->next->next->byte));
		}
		return (ft_check_reg(mem->next->next->next->next->next->next->byte));
	}
	return (0);
}

int		ft_check_store_index(t_mem *mem)
{
	if (!(ft_check_reg(mem->next->next->byte))
		|| (mem->next->byte >> 6) != REG_CODE)
		return (0);
	if (((mem->next->byte >> 4) & 0x03) == REG_CODE)
	{
		if (!(ft_check_reg(mem->next->next->next->byte)))
			return (0);
		if (((mem->next->byte >> 2) & 0x03) == REG_CODE)
			return (ft_check_reg(mem->next->next->next->next->byte));
		return (((mem->next->byte >> 2) & 0x03) == DIR_CODE ? 1 : 0);
	}
	else if (!((mem->next->byte >> 4) & 0x03))
		return (0);
	if (((mem->next->byte >> 2) & 0x03) == REG_CODE)
		return (ft_check_reg(mem->next->next->next->next->next->byte));
	else if ((!((mem->next->byte >> 2) & 0x03))
		|| ((mem->next->byte >> 2) & 0x03) == IND_CODE)
		return (0);
	return (1);
}
