/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:05:13 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/04/29 19:46:37 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signum, siginfo_t *info, void *ctx)
{
	static int				bit_count = -1;
	static unsigned char	char_accum;

	(void)ctx;
	if (bit_count < 0)
		bit_count = 7;
	if (signum == SIGUSR1)
		char_accum |= (1 << bit_count);
	bit_count--;
	if (bit_count < 0)
	{
		write(1, &char_accum, 1);
		char_accum = 0;
		if (kill(info->si_pid, SIGUSR2) == -1)
			write(2, "Error: Failed to send SIGUSR2\n", 30);
		return ;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		write(2, "Error: Failed to send SIGUSR1\n", 30);
}

void	set_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(1);
}

int	main(void)
{
	int					pid;

	pid = getpid();
	write(1, "PID: ", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	if (pid <= 0)
		return (1);
	while (1)
		set_signals();
	return (0);
}
