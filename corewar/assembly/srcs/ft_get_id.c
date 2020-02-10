/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_id.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 07:31:51 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 21:07:44 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

char		*ft_get_comment(char **line, int strt, int fd, int type)
{
	char	*comm;
	int		i;

	if (ft_strchr(*line, '"') == ft_strrchr(*line, '"'))
	{
		comm = ft_strfjoin(ft_strsub(*line, strt,
			ft_strlen(*line) - strt), ft_strdup("\n"));
		ft_strdel(line);
		while (get_next_line(fd, line) && !ft_strchr(*line, '"'))
			comm = ft_strfjoin(ft_strfjoin(comm, *line), ft_strdup("\n"));
		i = ft_strchr(*line, '"') - *line + 1;
		comm = ft_strfjoin(comm, ft_strsub(*line, 0, i - 1));
		while (ft_isspace((*line)[i]))
			i++;
		if ((*line)[i] && (*line)[i] != COMMENT_CHAR && (*line)[i] != ';')
		{
			ft_strdel(&comm);
			ft_fdprintf(2, "Syntax error after Champion's %s\n",
				type == 1 ? "name" : "comment");
			return (NULL);
		}
	}
	else
		comm = ft_strsub(*line, strt, ft_strrchr(*line, '"') - (*line + strt));
	return (check_length(type, comm));
}

void		skip_lines(int fd, char **line, int *res, int *nb)
{
	char	*tmp;

	while (get_next_line(fd, line) > 0 && (*line = (*line)[0]
		? ft_strtrim(tmp = *line) : *line) && ++(*nb)
			&& ft_strncmp(NAME_CMD_STRING, *line, ft_strlen(NAME_CMD_STRING))
				&& ft_strncmp(COMMENT_CMD_STRING, *line,
					ft_strlen(COMMENT_CMD_STRING))
						&& (*res = is_skipable(*line, *nb)) > 0)
	{
		ft_strdel(line);
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp);
}

int			get_id_value(char **line, t_header *id, int start, int fd)
{
	if ((!ft_strncmp(NAME_CMD_STRING, *line, ft_strlen(NAME_CMD_STRING))
		&& (id->prog_name || !(id->prog_name = ft_get_comment(line, start,
			fd, 1)))) || (!ft_strncmp(COMMENT_CMD_STRING, *line,
				ft_strlen(COMMENT_CMD_STRING)) && (id->comment
					|| !(id->comment = ft_get_comment(line, start, fd, 2)))))
		return (0);
	id->prog_size = 0;
	return (1);
}

t_header	*goto_valid_instr(char **line, int fd, int *nb, t_header *id)
{
	int		res;

	ft_strdel(line);
	while (get_next_line(fd, line) > 0
		&& ++(*nb) && is_valid_instruction(*line) != 1)
	{
		if ((res = is_skipable(*line, *nb)) != 1)
		{
			if (res == -2)
			{
				ft_fdprintf(2, "Syntax error : Missing comment string ");
				ft_fdprintf(2, "at the top of file : \"%s\" at Line %d\n",
					COMMENT_CMD_STRING, *nb);
			}
			ft_strdel(line);
			return ((t_header *)free_id(id));
		}
		ft_strdel(line);
	}
	return (id);
}

t_header	*get_champ_id(int fd, char **line, int *nb)
{
	t_header	*id;
	int			start;
	int			res;

	if (!(id = (t_header*)malloc(sizeof(*id))))
		return (NULL);
	res = 1;
	id->prog_name = NULL;
	id->comment = NULL;
	*line = ft_strdup("");
	while ((!id->prog_name || !id->comment) && *line)
	{
		ft_strdel(line);
		skip_lines(fd, line, &res, nb);
		start = ft_strichr(*line, '"') + 1;
		if (check_missing_cmd(line, res, id, nb)
			|| !get_id_value(line, id, start, fd))
		{
			ft_strdel(line);
			return ((t_header *)free_id(id));
		}
	}
	return (goto_valid_instr(line, fd, nb, id));
}
