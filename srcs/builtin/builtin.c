/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:16:34 by tboos             #+#    #+#             */
/*   Updated: 2016/03/31 14:44:22 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_clean_path(char *path)
{
	int		i;

	i = 0;
	while (path && path[i])
	{
		if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '/')
			ft_strcpy(path + i, path + i + 2);
		else if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '.'
				&& i - 2 > 0 && path[i - 1] != '.' && path[i - 2] != '.')
		{
			while (--i != 0 && path[i] != '/')
				;
			ft_strcpy(path + i + 1, ft_strchr(path + i + 1, '/') + 3);
		}
		else if (path[i] == '/' && path[i + 1] == '/')
			ft_memmove(path + i, path + i + 1, strlen(path + i));
		else
			i++;
	}
	if (path && i > 2 && path[i - 1] == '.' && path[i - 2] == '/')
		path[i - 2] = '\0';
	if (path && i && path[i - 1] == '/')
		path[i - 1] = '\0';
	if (*path == '/' && *(path + 1) == '.' && *(path + 2) == '.')
		*(path + 1) = '\0';
}

static void	ft_path_follow(char *path, char **argv, t_config *config, int i)
{
	ft_clean_path(path);
	if (!ft_access_dir(path))
		;
	else if (!chdir(path))
		ft_setenv("PWD", path, config);
	else
		FT_PUTSTRFD("minishell: no such file: ",
				(argv[i] ? argv[i] : path), "\n", 2);
	free(path);
}

void		ft_cd(char **argv, t_config *config)
{
	char	*path;
	int		i;

	path = NULL;
	if ((i = (ft_strcmp(argv[0], "cd") ? 0 : 1)) && ft_strtablen(argv) - i > 1
		&& (i += 3))
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (!argv[i] && (path = ft_strtabfind(config->env, "HOME=")))
		path = ft_strdup(path + 5);
	else if (argv[i] && argv[i][0] == '/')
		path = ft_strdup(argv[i]);
	else if (argv[i] && argv[i][0] == '~'
			&& (path = ft_strtabfind(config->env, "HOME=")))
		path = ft_strslashjoin(path + 5,
				(ft_strlen(argv[i]) > 2 ? argv[i] + 2 : "."));
	else if (argv[i] && argv[i][0] == '-'
			&& (path = ft_strtabfind(config->env, "OLDPWD=")))
		path = ft_strslashjoin(path + 7,
				(ft_strlen(argv[i]) > 2 ? argv[i] + 2 : "."));
	else if (argv[i] && (path = ft_strtabfind(config->env, "PWD")))
		path = ft_strslashjoin(path + 4, argv[i]);
	if (path)
		ft_path_follow(path, argv, config, i);
	else if (i < 3)
		ft_putstr_fd("minishell: cd: path error, env might be corrupted\n", 2);
}

static void	ft_pwd(char **argv, char *pwd)
{
	if (argv[1])
		ft_putstr_fd("pwd: too many arguments\n", 2);
	else if (!pwd)
		ft_putstr_fd("pwd: path in env is corrupted\n", 2);
	else
		ft_putendl(pwd + 4);
}

int			ft_builtin(char **argv, t_config *config)
{
	if (!ft_strcmp(argv[0], "exit"))
		ft_shell_exit(config, argv);
	else if (!ft_strcmp(argv[0], "exitfather"))
		ft_kill_father(config);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(argv, ft_strtabfind(config->env, "PWD"));
	else if (!ft_strcmp(argv[0], "env") || !ft_strcmp(argv[0], "printenv"))
		ft_env(argv, config);
	else if (!ft_strcmp(argv[0], "unsetenv") || !ft_strcmp(argv[0], "unset"))
		ft_unsetenv(argv, config);
	else if (!ft_strcmp(argv[0], "setenv") || !ft_strcmp(argv[0], "set"))
		ft_readysetenv(argv, config);
	else if (!ft_strcmp(argv[0], "cd"))
		ft_cd(argv, config);
	else
		return (0);
	return (1);
}