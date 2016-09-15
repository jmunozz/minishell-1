#include "minishell.h"

static int	ft_safeputstr(int fd, char *str)
{
	if (str && 0 > write(fd, str, ft_strlen(str)))
	{
		ft_error(SHNAME, NULL, SAVE_H_ERR, CR_ERROR | SERROR);
		ft_freegiveone((void **)&str);
		return (0);
	}
	ft_freegiveone((void **)&str);
	return (1);
}

void		ft_purge_history(t_config *config)
{
	int		i;
	int		fd;

	if ((fd = open(config->hloc, O_CREAT | O_WRONLY
		| O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		ft_error(SHNAME, NULL, SAVE_H_ERR, CR_ERROR | SERROR);
	else
	{
		i = config->hindex;
		while (1)
		{
			ft_incr_history(&i);
			if (!ft_safeputstr(fd, config->history[i])
				|| i == config->hindex)
				break ;
			if (config->history[i])
				write(fd, "\n", 1);
		}
		write(fd, "\0", 1);
		close(fd);
	}
}

void		ft_load_history(t_config *config)
{
	int		fd;

	if ((fd = open(config->hloc, O_RDONLY)) < 0)
		ft_error(SHNAME, NULL, LOAD_H_ERR, CR_ERROR | SERROR);
	else
	{
		while (get_next_line(fd, &(config->history[config->hindex])) > 0)
			if (config->history[config->hindex][0])
				ft_incr_history(&(config->hindex));
		close(fd);
	}
}
