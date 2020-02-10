/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   VM_filler.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/16 20:45:35 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 02:45:30 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VM_FILLER_H
# define VM_FILLER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include "./fi_filler.h"

typedef struct	s_player
{
	char		*p1;
	char		*p2;
	int			len1;
	int			len2;
}				t_player;

int				get_line_length(char *line, int mode);
void			ft_stradd(char **str, int *x, char *add);
void			variable_init(t_player *player, t_sq *p);
void			motor(char **map, t_sq *p, t_player player);
char			*ft_get_player(char *adr1);
void			change_line(int y, char **map, char *line, t_sq *p);
void			sleep_calculator(int lagtime);
long			get_microtime(void);
void			print_bot_screen(t_sq p, t_co map_s);
void			print_bot_screen_first_step(t_co map_s, t_player player,
		t_sq p);
void			do_at_end(t_sq p, char **map, t_co map_s, t_player *player);

# define CLEAR_S "\e[1;1H\e[2J"
# define RED "\x1B[101m"
# define FRED "\x1B[41m"
# define GRN "\x1B[102m"
# define FGRN "\x1B[42m"
# define YLW "\x1B[93m"
# define YLWB "\x1B[100m"
# define WHT "\x1B[107m"
# define WHT2 "\x1B[97m"
# define YLW2 "\x1B[47m"
# define NC "\x1B[0m"

#endif
