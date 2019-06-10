/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ftoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/31 18:40:16 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 05:50:20 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static long int		s_get_pprec(long prec)
{
	long int pprec;

	pprec = (prec == 0) ? 0 : 1;
	prec = prec > 18 ? 19 : prec + 1;
	while (--prec)
		pprec = pprec * 10;
	return (pprec);
}

static int			ft_isneine(long t)
{
	char	*str;
	int		i;

	i = -1;
	str = ft_itoa(t);
	while (str[++i])
	{
		if (str[i] != '-' && str[i] != '9')
		{
			ft_memdel((void**)&str);
			return (0);
		}
	}
	ft_memdel((void**)&str);
	return (1);
}

static int			ft_strisneine(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '-' && str[i] != '9')
			return (0);
	}
	return (1);
}

char				*ft_ftoa_next(long prec, long pprec, long t, long ln)
{
	char	*str;
	char	*fstr;
	int		fstrlen;

	str = ft_itoa(ln);
	fstr = ft_itoa(t);
	fstr = ft_strjoin_del(ft_strinit('0', ft_nbrlen_base(pprec, 10) -
				ft_nbrlen_base(t, 10) - 1), fstr);
	fstrlen = (long)ft_strlen(fstr);
	if ((long)ft_strlen(fstr) > prec && fstr[prec] >= '6' && fstr[prec] <= '9')
	{
		if (ft_strisneine(fstr) && (str = ft_strrep(str, ft_atoi(str) < 0 ?
						ft_itoa(ft_atoi(str) - 1) : ft_itoa(ft_atoi(str) + 1))))
			fstr = ft_strrep(fstr, ft_strinit('0', prec));
		else
			fstr = ft_strrep(fstr, ft_itoa(ft_atoi(fstr)
						+ 10 - (fstr[prec] - 48)));
		if (fstrlen > (long)ft_strlen(fstr))
			fstr = ft_strjoin_del(ft_strinit('0',
						fstrlen - (long)ft_strlen(fstr)), fstr);
	}
	fstr = ft_strrep(fstr, ft_strsub(fstr, 0, prec));
	str = ft_strjoin_del(str, ft_strdup("."));
	str = ft_strjoin_del(str, fstr);
	return (str);
}

char				*ft_ftoa(double n, long prec)
{
	long		t;
	long int	pprec;
	long		ln;
	char		*neg;

	if (n != n)
		return (ft_strdup("nan"));
	neg = n < 0 ? ft_strdup("-") : ft_strdup("");
	n = n < 0 ? n * -1 : n;
	prec = prec == -1 ? 6 : prec;
	pprec = s_get_pprec(prec + 1);
	if (pprec == 0)
		n += 0.5;
	else
		n += (5.0 / (pprec * 10));
	if (pprec == 0)
		return (ft_strdup(""));
	ln = (long)n;
	t = (n - ln) * pprec;
	if (t < 0 && (ft_nbrlen_base(t, 10) - ft_nbrlen_base(pprec, 10) == 0 &&
			ft_isneine(t)) && !(t = 0))
		ln -= 1;
	else if (t < 0)
		t = -t + 1;
	return (ft_strjoin_del(neg, ft_ftoa_next(prec, pprec, t, ln)));
}
