/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 13:34:43 by jle-quel          #+#    #+#             */
/*   Updated: 2017/07/07 14:39:16 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		ft_initiate_terms(t_select *var)
{
	int				result;
	char			*terminal_type;

	if (!(terminal_type = getenv("TERM")))
		return (ft_errno(NO_VAR));
	if ((result = tgetent(NULL, terminal_type)) == 0)
		return (ft_errno(NO_ENTRY));
	if (result == -1)
		return (ft_errno(NO_DB));
	if (tcgetattr(0, &var->eop) == -1)
		return (ft_errno(NO_TMS));
	return (0);
}

int		ft_to_non_canonique(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (ft_errno(NO_TMS));
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == 1)
		return (ft_errno(NO_SET));
	return (0);
}

int		ft_clear_shell(void)
{
	char	*clear_shell;

	if (!(clear_shell = tgetstr("cl", NULL)))
		return (ft_errno(NO_STR));
	ft_putstr_fd(clear_shell, 0);
	return (0);
}

int		ft_place_cursor(void)
{
	char	*cursor;

	if (!(cursor = tgetstr("cm", NULL)))
		return (ft_errno(NO_STR));
	ft_putstr_fd(tgoto(cursor, 0, 0), 0);
	ft_putstr_fd(tgetstr("vi", NULL), 0);
	return (0);
}
