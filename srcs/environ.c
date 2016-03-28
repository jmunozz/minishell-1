/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:21:35 by tboos             #+#    #+#             */
/*   Updated: 2016/03/28 16:27:27 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(char *name, char *value, t_config *config)
{
	int		i;
	char	**f;
	char	*memo;

	f = config->env;
	if ((i = ft_strtabifindstart(f, name)) >= 0
		&& (memo = f[i])
		&& !(f[i] = ft_strchrjoin(name, '=', value))
		&& (f[i] = memo))
		FT_PUTSTRFD("minishell: error while setenv for: ", name, "\n", 2);
	else if (i >= 0 && !ft_strcmp(name, "PWD"))
	{
		ft_setenv("OLDPWD", memo + 4, config);
		free(memo);
	}
	else if (i < 0 && !(memo = ft_strchrjoin(name, '=', value)))
		FT_PUTSTRFD("minishell: malloc error during setenv for: ",
				name, "\n", 2);
	else if (i < 0 && !(config->env = ft_strtabadd(f, memo))
		&& ft_freegiveone((void **)&memo) && (config->env = f))
		FT_PUTSTRFD("minishell: malloc error during setenv for: ",
				name, "\n", 2);
	else if (f && config->env && f != config->env)
		ft_strtabfree(f);
}

void	ft_env(char **argv, t_config *config)
{
	if (!argv[1])
	{
		ft_putstrtab((char const **)(config->env), '\n');
		ft_putchar('\n');
	}
}

void	ft_setenv(char **argv, t_config *config)
{
	int		i;
	char	*t;
	char	*p;

	i = 0;
	while (argv[++i])
	{
		if ((t = ft_strchr(argv[i], '=')))
		{
			*t = '\0';
			p = argv[i] - 1;
			while (*(++p))
				*p = ft_toupper(*p);
			*p = '=';
			while (*(++p))
				*p = ft_tolower(*p);
		}
		ft_strtabadd(config->env, argv[i]);
	}
}

void	ft_unsetenv(char **argv, t_config *config)
{
	int		i;

	i = 0;
	while (argv[++i])
		ft_strncmptabdel(config->env, argv[i]);
}
