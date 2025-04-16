/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:13:53 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/04/16 15:11:51 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_ack;

void	handler(int signum, siginfo_t *info, void *ctx)
{
	(void)ctx;
	(void)info;
	(void)signum;
	if (signum != SIGUSR1)
		return ;		
	g_ack = 1;
}

void	send_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 7;
	g_ack = 1;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		g_ack = 0;
		while (!g_ack)
			pause();
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	char				*str;
	int					i;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	if (argc != 3)
	{
		write(2, "Uso: ./client [PID_SERVER] [MENSSAGE]\n", 38);
		return (1);
	}
	pid = (pid_t)ft_atoi(argv[1]);
	str = argv[2];
	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
	return (0);
}
