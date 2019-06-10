/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fd_matrix.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 11:48:58 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 11:49:31 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/header.h"

void		fd_get_change_dim(float tab[3][3])
{
	tab[0][0] = 1;
	tab[0][1] = 0;
	tab[0][2] = 0;
	tab[1][0] = 0;
	tab[1][1] = 1;
	tab[1][2] = 0;
	tab[2][0] = 0;
	tab[2][1] = 0;
	tab[2][2] = 1;
}

void		fd_get_rotatex(float tab[3][3], float angle)
{
	tab[0][0] = 1;
	tab[0][1] = 0;
	tab[0][2] = 0;
	tab[1][0] = 0;
	tab[1][1] = cos(angle);
	tab[1][2] = -sin(angle);
	tab[2][0] = 0;
	tab[2][1] = sin(angle);
	tab[2][2] = cos(angle);
}

void		fd_get_rotatey(float tab[3][3], float angle)
{
	tab[0][0] = cos(angle);
	tab[0][1] = 0;
	tab[0][2] = sin(angle);
	tab[1][0] = 0;
	tab[1][1] = 1;
	tab[1][2] = 0;
	tab[2][0] = -sin(angle);
	tab[2][1] = 0;
	tab[2][2] = cos(angle);
}

void		fd_get_rotatez(float tab[3][3], float angle)
{
	tab[0][0] = cos(angle);
	tab[0][1] = -sin(angle);
	tab[0][2] = 0;
	tab[1][0] = sin(angle);
	tab[1][1] = cos(angle);
	tab[1][2] = 0;
	tab[2][0] = 0;
	tab[2][1] = 0;
	tab[2][2] = 1;
}

t_vector	fd_vectmul(t_vector v, float format[3][3], float mul_z)
{
	t_vector newv;

	mul_z = v.z == 0 ? 0 : mul_z;
	newv.x = v.x * format[0][0] + v.y * format[1][0] +
		(v.z + mul_z * v.z) * format[2][0];
	newv.y = v.x * format[0][1] + v.y * format[1][1] +
		(v.z + mul_z * v.z) * format[2][1];
	newv.z = v.x * format[0][2] + v.y * format[1][2] +
		(v.z + mul_z * v.z) * format[2][2];
	return (newv);
}
