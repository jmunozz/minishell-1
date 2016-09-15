/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:23:28 by tboos             #+#    #+#             */
/*   Updated: 2016/09/11 14:42:35 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "posix.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <term.h>
# include <curses.h>
# include <dirent.h>
# include <stdio.h>
# include <termios.h>
# include <fcntl.h>
# include <signal.h>
# include <pwd.h>
# include "libft.h"
# include "core.h"
# include "input_scan.h"
# include "run_command.h"
# ifdef LINUX
#  include "keys_linux.h"
# else
#  include "keys_mac.h"
# endif

#endif
