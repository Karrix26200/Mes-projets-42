/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/10 22:17:05 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 21:06:12 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

char	**ft_init_instruction_list(void)
{
	char	**instructions;

	instructions = (char **)malloc(17 * sizeof(char *));
	instructions[0] = ft_strdup("live");
	instructions[1] = ft_strdup("ld");
	instructions[2] = ft_strdup("st");
	instructions[3] = ft_strdup("add");
	instructions[4] = ft_strdup("sub");
	instructions[5] = ft_strdup("and");
	instructions[6] = ft_strdup("or");
	instructions[7] = ft_strdup("xor");
	instructions[8] = ft_strdup("zjmp");
	instructions[9] = ft_strdup("ldi");
	instructions[10] = ft_strdup("sti");
	instructions[11] = ft_strdup("fork");
	instructions[12] = ft_strdup("lld");
	instructions[13] = ft_strdup("lldi");
	instructions[14] = ft_strdup("lfork");
	instructions[15] = ft_strdup("aff");
	instructions[16] = NULL;
	return (instructions);
}

int		ft_print_usage(char *path)
{
	ft_printf("Usage: %s [-a] <sourcefile.s>\n", path);
	ft_putstr("	-a : Instead of creating a .cor file");
	ft_putstr("outputs a stripped and annotated version of");
	ft_putstr(" the code to the standard output\n");
	return (-1);
}

t_data	*init_data(char **av)
{
	int		i;
	int		j;
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->fd = -1;
	data->line = NULL;
	data->nb = 0;
	data->option = 0;
	data->file = NULL;
	i = 1;
	while (av[i])
	{
		if (!(ft_strcmp(av[i], "-a")) && (data->option = 1)
				&& (j = i - 1) == i - 1)
			while (av[++j])
				av[j] = av[j + 1];
		else
			data->file = av[i++];
	}
	return (data);
}

int		main(int ac, char **av)
{
	t_asm		*assemb;
	t_header	*id;
	t_data		*data;
	char		*tmp;

	assemb = NULL;
	if ((ac == 1 && ft_print_usage(av[0]))
			|| (!(data = init_data(av))))
		return (-1);
	if ((data->fd = open(data->file, O_RDONLY)) == -1)
	{
		ft_fdprintf(2, "Can't read source file : %s\n", data->file);
		free(data);
		return (-1);
	}
	if (!(id = get_champ_id(data->fd, &data->line, &data->nb))
			|| !(ft_get_instruction(&assemb, data, &id->prog_size)))
		return (clean_exit(-1, data, assemb, id));
	if (!ft_check_labels(assemb, assemb))
		return (clean_exit(-1, data, assemb, id));
	ft_create_bin(assemb, id, (tmp = ft_strsub(data->file, 0,
					ft_strrchr(data->file, '.') - data->file)), data);
	ft_strdel(&tmp);
	return (clean_exit(0, data, assemb, id));
}
