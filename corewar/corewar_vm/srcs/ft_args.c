/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_args.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 19:21:32 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 08:09:39 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		check_player(char **av, int *i, t_vm *vm, int nb)
{
	int		fd;
	int		check;
	int		n;
	int		cpy;

	check = 0;
	n = 0;
	cpy = n;
	if ((fd = ft_ispath(av[*i])))
	{
		vm->nb_players++;
		while (vm->players[n])
			if (vm->players[n++]->place == nb && nb)
				return (0 * ft_fdprintf(2, "Multiple -n %d option\n", nb) - 1);
		if (n == 4)
			return (0 * ft_fdprintf(2, "Too many Players\n") - 1);
		if (!(vm->players[n] = ft_new_player(-n, fd, av[*i], nb)))
			return (-1);
		return (1);
	}
	else if (nb)
		ft_fdprintf(2, "Can't read source file %s after -n %d\n", av[*i], nb);
	return (-1);
}

t_args	*sort_player(t_args *args, t_vm *vm)
{
	int			i;
	int			check;
	t_player	*player;

	check = 0;
	while (check == 0)
	{
		check = 1;
		i = 0;
		while (vm->players[i + 1])
		{
			if ((vm->players[i]->place > vm->players[i + 1]->place
				&& vm->players[i + 1]->place)
					|| (!vm->players[i]->place && vm->players[i + 1]->place))
			{
				player = vm->players[i + 1];
				vm->players[i + 1] = vm->players[i];
				vm->players[i] = player;
				check = 0;
			}
			else
				i++;
		}
	}
	return (args);
}

int		modif_args(int *i, int ac, char **av, t_args *args)
{
	if (((*i < ac && !ft_strcmp(av[*i], "-d"))
		|| !ft_strcmp(av[*i], "-dump")) && ((*i)++))
		args->dump = *i == ac || !ft_atoi(av[*i]) ? 0 : ft_atoi(av[*i]);
	else if (*i < ac && !ft_strcmp(av[*i], "-s") && ((*i)++))
		args->pause = *i == ac || !ft_atoi(av[*i]) ? 0 : ft_atoi(av[*i]);
	else if (*i < ac && !ft_strcmp(av[*i], "-v") && ((*i)++))
		args->verbosity = *i == ac || !ft_atoi(av[*i]) ? 0 : ft_atoi(av[*i]);
	else if (*i < ac && !ft_strcmp(av[*i], "-b") && ((*i)++))
		args->binary = *i != ac && !ft_strcmp(av[*i], "--stealth") ? 1 : 2;
	else if (*i < ac && !ft_strcmp(av[*i], "-a"))
		args->aff = 1;
	else
		return (0);
	return (1);
}

int		check_player_err(char **av, int *i, t_vm *vm, t_args *args)
{
	int		number;

	if (av[*i] && ft_atoi(av[*i])
		&& (number = ft_atoi(av[(*i)])) == ft_atoi(av[(*i)]))
	{
		(*i)++;
		if (check_player(av, i, vm, number) == -1)
		{
			free(args);
			return (1);
		}
	}
	else if ((*i)--)
		args->ncurse = 1;
	return (0);
}

t_args	*ft_get_args(int ac, char **av, t_args *args, t_vm *vm)
{
	int		i;

	args = ft_init_args(args, &i);
	ft_print_usage(ac);
	while (i < ac)
	{
		if ((i < ac && !ft_strcmp(av[i], "-n")) && (++i))
		{
			if (check_player_err(av, &i, vm, args))
				return (NULL);
		}
		else if (!(modif_args(&i, ac, av, args))
			&& check_player(av, &i, vm, 0) == -1)
		{
			ft_fdprintf(2, "Can't read source file %s\n", av[i]);
			free(args);
			return (NULL);
		}
		i += av[i] ? 1 : 0;
	}
	if (vm->nb_players)
		return (sort_player(args, vm));
	ft_fdprintf(2, ac != 1 ? "No players\n" : "");
	free(args);
	return (NULL);
}
