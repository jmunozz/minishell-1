#ifndef INPUT_SCAN_H
# define INPUT_SCAN_H

typedef struct	s_stream
{
	char		*term;
	char		*tput;
	int			fd;
	int			ret;
	int			shindex;
	int			state;
	char		buf[9];
	char		*command;
	char		*kill;
	size_t		pos;
	size_t		col;
	t_config	*config;
}				t_stream;
/*
**streamscan.c
*/
char			*ft_streamscan(t_config *config, t_stream *stream, int fd);
int				ft_underline_mess(char *mess, t_stream *stream);
int				ft_quotecheck(t_stream *stream);
/*
**termcaps.c
*/
int				ft_putcharint(int	i);
void			ft_tputs(t_stream *stream);
void			ft_mvleft(t_stream *stream);
void			ft_mvright(t_stream *stream);
/*
**arrowlr.c && arrowud.c
*/
void			ft_ctrlleft(t_stream *stream);
void			ft_ctrlright(t_stream *stream);
void			ft_left(t_stream *stream);
void			ft_right(t_stream *stream);
void			ft_goend(t_stream *stream);
void			ft_gohome(t_stream *stream);
void			ft_ctrlup(t_stream *stream);
void			ft_ctrldown(t_stream *stream);
/*
**deletion.c
*/
void			ft_clean_field(t_stream *stream);
void			ft_erase(t_stream *stream);
void			ft_sup(t_stream *stream);
void			ft_del(t_stream *stream);
/*
**chrparse.c
*/
void			ft_flushend(t_stream *stream);
void			ft_flush(t_stream *stream);
int				ft_chrparse(t_stream *stream);
/*
**autocomp.c
*/
void			ft_autocomp(t_stream *stream);
/*
**prompt.c
*/
int				ft_prompt(t_config *config);
/*
**history.c
*/
void			ft_up(t_stream *stream);
void			ft_down(t_stream *stream);
void			ft_decr_history(int *hindex);
void			ft_incr_history(int *hindex);
void			ft_push_history(t_stream *stream, t_config *config);

#endif