/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:21:27 by tboos             #+#    #+#             */
/*   Updated: 2016/03/31 12:52:21 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_access_dir(char const *path)
{
	char		cpy[_POSIX_PATH_MAX + 1];
	char		*endl;
	struct stat	buf;

	if (_POSIX_PATH_MAX < ft_strlen(path))
		return (1 ^ ft_error(SHNAME, PATH_MAX_EXEED, (char *)path,
			CR_ERROR | SERROR));
	endl = ft_strcpy(cpy, path);
	while ((endl = ft_strchr(endl + 1, '/')))
	{
		*endl = '\0';
		if (-1 == access(cpy, F_OK) && !(endl = NULL))
			ft_error(SHNAME, "directory doesn't exist", cpy, CR_ERROR);
		else if (-1 == stat(cpy, &buf) && !(endl = NULL))
			ft_error(SHNAME, "stat failed on", cpy, CR_ERROR);
		else if (!S_ISDIR(buf.st_mode) && !(endl = NULL))
			ft_error(SHNAME, cpy, "not a directory", CR_ERROR);
		else if (-1 == access(cpy, X_OK) && !(endl = NULL))
			ft_error(SHNAME, "permission denied", cpy, CR_ERROR);
		if (!endl)
			return (0);
		*endl = '/';
	}
	return (1);
}

void	ft_access_exec(char *path, char **argv, t_config *config)
{
	struct stat	buf;

	if (!ft_access_dir(path))
		return ;
	if (-1 == access(path, F_OK))
		ft_error(SHNAME, "command not found", path, CR_ERROR);
	else if (-1 == stat(path, &buf))
		ft_error(SHNAME, "access denied", path, CR_ERROR);
	else if (S_ISDIR(buf.st_mode))
		ft_cd(argv, config);
	else if (!S_ISREG(buf.st_mode))
		ft_error(SHNAME, path, "not a regular file", CR_ERROR);
	else if (-1 == access(path, X_OK))
		ft_error(SHNAME, path, "permission denied", CR_ERROR);
	else
		ft_fewef(path, argv, config->env);
}
