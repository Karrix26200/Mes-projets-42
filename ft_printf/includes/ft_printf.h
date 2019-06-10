/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 18:24:28 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 04:57:25 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/includes/libft.h"
# include <locale.h>

typedef struct	s_pformat
{
	char			*flag;
	int				width;
	int				prec;
	char			*size;
	char			conv;
}				t_pformat;

typedef struct	s_printf
{
	char			*str;
	int				len;
	struct s_printf	*next;
}				t_printf;

int				ft_printf(const char *format,
		...) __attribute__((format(printf,1,2)));

int				ft_fprintf(int fd, const char *format,
		...) __attribute__((format(printf,2,3)));

int				ft_sprintf(char **dst, const char *format,
		...) __attribute__((format(printf,2,3)));

char			*ft_cprintf(const char *format,
		...) __attribute__((format(printf,1,2)));

t_printf		*ft_mainprintf(const char *format, va_list arpt, int *totalen);

char			*ft_flag_save(const char *format, int *i);
int				ft_width_save(const char *format, int *i, va_list arpt,
		t_pformat *d);
int				ft_prec_save(const char *format, int *i, va_list arpt);
char			*ft_size_save(const char *format, int *i);
char			ft_conv_save(const char *format, int *i);

void			ft_format_free(t_pformat *d);

int				ft_lstp_controller(t_printf *begin, int mod,
		int fd, char **dst);
t_printf		*ft_lstp_new(char *str, int len);

long long		ft_get_cast_int(t_pformat *d, va_list arpt);
long long		ft_get_cast_base(t_pformat *d, va_list arpt);
void			*ft_get_cast_other(t_pformat *d, va_list arpt);

char			*ft_use_convert_fnc(va_list arpt,
		char *(*f)(va_list, t_pformat *), t_pformat *d);
void			*ft_get_convert_fnc(int index);

char			*ft_convert_s(va_list arpt, t_pformat *d);
char			*ft_convert_sm(va_list arpt, t_pformat *d);
char			*ft_convert_p(va_list arpt, t_pformat *d);
char			*ft_convert_d(va_list arpt, t_pformat *d);
char			*ft_convert_dm(va_list arpt, t_pformat *d);
char			*ft_convert_o(va_list arpt, t_pformat *d);
char			*ft_convert_om(va_list arpt, t_pformat *d);
char			*ft_convert_u(va_list arpt, t_pformat *d);
char			*ft_convert_x(va_list arpt, t_pformat *d);
char			*ft_convert_xm(va_list arpt, t_pformat *d);
char			*ft_convert_c(va_list arpt, t_pformat *d);
char			*ft_unicodenew(int c, int len);
char			*ft_convert_cm(va_list arpt, t_pformat *d);
char			*ft_convert_f(va_list arpt, t_pformat *d);
char			*ft_convert_e(va_list arpt, t_pformat *d);
char			*ft_convert_g(va_list arpt, t_pformat *d);

void			ft_format_prec(t_printf *newl, t_pformat *d, int neg);
void			ft_format_flag(t_printf *newl, t_pformat *d, int neg);
t_printf		*ft_try_format(const char *format, int *i, int s, va_list arpt);

int				ft_get_color_id_other(const char *format, int *i, int a);
int				ft_get_color_txt(const char *format);
int				ft_get_color_id_macro(const char *format, int *i, int a);
int				ft_get_color_id(const char *format, int *i);
t_printf		*ft_try_color(const char *format, int *i, int s);

#endif
