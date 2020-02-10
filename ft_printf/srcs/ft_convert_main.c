/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_main.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 02:02:37 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 04:57:10 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_use_convert_fnc(va_list arpt, char *(*f)(va_list, t_pformat *),
		t_pformat *d)
{
	return (f(arpt, d));
}

void	*ft_get_convert_fnc(int index)
{
	void	*tab[20];

	tab[0] = &ft_convert_s;
	tab[1] = &ft_convert_sm;
	tab[2] = &ft_convert_p;
	tab[3] = &ft_convert_d;
	tab[4] = &ft_convert_dm;
	tab[5] = &ft_convert_d;
	tab[6] = &ft_convert_o;
	tab[7] = &ft_convert_om;
	tab[8] = &ft_convert_u;
	tab[9] = &ft_convert_u;
	tab[10] = &ft_convert_x;
	tab[11] = &ft_convert_xm;
	tab[12] = &ft_convert_c;
	tab[13] = &ft_convert_cm;
	tab[14] = &ft_convert_f;
	tab[15] = &ft_convert_f;
	tab[16] = &ft_convert_e;
	tab[17] = &ft_convert_e;
	tab[18] = &ft_convert_g;
	tab[19] = &ft_convert_g;
	return (tab[index]);
}
