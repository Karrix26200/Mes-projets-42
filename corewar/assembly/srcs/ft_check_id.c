/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_id.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 09:02:31 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 21:07:29 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int			is_skipable(char *line, int nb)
{
	int		j;
	char	*tmp;

	j = 0;
	while (ft_isspace(line[j]))
		j++;
	if (line[j] == COMMENT_CHAR || line[j] == ';')
		return (1);
	if (line[j] == '.' && ft_strncmp(NAME_CMD_STRING, line,
		ft_strlen(NAME_CMD_STRING)) && ft_strncmp(COMMENT_CMD_STRING,
			line, ft_strlen(COMMENT_CMD_STRING)) && (j = 1))
	{
		while (line[j] && !ft_isspace(line[j]))
			j++;
		ft_fdprintf(2, "Unrecognized command string : \"%s\" at Line %d\n",
			(tmp = ft_strsub(line, 0, j)), nb);
		ft_strdel(&tmp);
		return (-1);
	}
	j = 0;
	while (line[j] && ft_isspace(line[j]))
		j++;
	if (line[j])
		return (-2);
	return (1);
}

char		*check_length(int type, char *comm)
{
	if ((type == 2 && ft_strlen(comm) > COMMENT_LENGTH)
		|| (type == 1 && ft_strlen(comm) > PROG_NAME_LENGTH))
	{
		ft_strdel(&comm);
		ft_fdprintf(2, "Champion %s too long (Max length %d)\n",
			type == 1 ? "name" : "comment", type == 1
				? PROG_NAME_LENGTH : COMMENT_LENGTH);
		return (NULL);
	}
	return (comm);
}

int			check_missing_cmd(char **line, int res, t_header *id, int *nb)
{
	if (!*line || (res <= 0 && ft_strncmp(NAME_CMD_STRING,
		*line, ft_strlen(NAME_CMD_STRING))
			&& ft_strncmp(COMMENT_CMD_STRING, *line,
				ft_strlen(COMMENT_CMD_STRING))))
	{
		if (!id->prog_name || !id->comment)
		{
			ft_fdprintf(2, "Syntax error : Missing %s",
				!id->prog_name ? "name" : "comment");
			ft_fdprintf(2,
				"command string at the top of file : \"%s\" at Line %d\n",
					!id->prog_name ? NAME_CMD_STRING : COMMENT_CMD_STRING, *nb);
		}
		return (1);
	}
	return (0);
}
