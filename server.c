/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:05:13 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/04/16 14:19:59 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signum, siginfo_t *info, void *ctx)
{
	static int				bit_count;
	static unsigned char	char_accum;

	(void)ctx;
	if (!info || info->si_pid <= 0)
		return ;
	if (signum != SIGUSR1 && signum != SIGUSR2)
		return ;
	char_accum <<= 1;
	if (signum == SIGUSR1)
		char_accum |= 1;
	if (++bit_count == 8)
	{
		if (char_accum == 0)
			write(1, "\n[FIN]\n", 7);
		else
			write(1, &char_accum, 1);
		bit_count = 0;
		char_accum = 0;
	}
	usleep(10);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	write(1, "PID: ", 5);
	ft_putnbr(pid);
	if (pid <= 0)
		return (1);
	write(1, "\n", 1);
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
