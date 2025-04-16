/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:17:22 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/04/16 14:33:49 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 199309L
# define _XOPEN_SOURCE 500
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>

unsigned int	ft_atoi(char *s);
void			ft_putnbr(int num);

#endif