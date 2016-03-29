/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:08 by tboos             #+#    #+#             */
/*   Updated: 2016/03/29 20:42:59 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_signal(void)
{
	if (SIG_ERR == signal(SIGINT, SIG_IGN))
		return (ft_initerror());
	if (SIG_ERR == signal(SIGTSTP, SIG_IGN))
		return (ft_initerror());
	return (0);
}

static void	ft_manage_files(int ac, char **av, t_config *config)
{
	char		*cmd;
	int			fd;
	int			i;

	i = 0;
	while (++i < ac)
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
			FT_PUTSTRFD("minishell: can't open input file: ",
					av[i], "\n", 2);
		else if ((cmd = ft_streamscan(config, fd)))
		{
			while (cmd)
			{
				ft_run_command(config, cmd);
				free(cmd);
				cmd = NULL;
				cmd = ft_streamscan(config, fd);
			}
			close(fd);
		}
	}
}

static void	ft_tricase(int ac, char **av, t_config *config)
{
	char		*cmd;

	if (ac > 1)
		ft_manage_files(ac, av, config);
	else if ((cmd = ft_streamscan(config, 0)))
		while (cmd)
		{
			ft_run_command(config, cmd);
			free(cmd);
			cmd = ft_streamscan(config, 0);
		}
	else if (!ft_signal() && dprintf(1, "signaling \n"))
		ft_minishell(config);
	ft_shell_exit(config, NULL);
}

int			main(int ac, char **av, char **env)
{
	t_config	*config;

	if (!(config = (t_config *)ft_memalloc(sizeof(t_config))))
		return (ft_initerror());
	ft_bzero(config->history, sizeof(config->history));
	if (!(config->env = ft_strtabdup(env))
			|| !ft_pathtohash(config))
	{
		ft_free_config(config);
		return (ft_initerror());
	}
	ft_tricase(ac, av, config);
	return (0);
}
