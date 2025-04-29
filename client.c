/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:13:53 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/04/29 20:13:46 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signum)
{
	if (signum == SIGUSR1)
		write(1, "Bit has been receieved\n", 23);
	else if (signum == SIGUSR2)
		write(1, "Character has been delivered\n", 29);
}

void	config_signals(void)
{	
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = &handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

void	send_str(pid_t pid, char *s)
{
	unsigned char	c;
	int				nbr_bits;

	while (*s)
	{
		c = *s;
		nbr_bits = 8;
		while (nbr_bits--)
		{
			if ((c >> 7) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			c <<= 1;
		}
		s++;
	}
	exit(1);
}

int	main(int argc, char **argv)
{
	pid_t				pid;

	if (argc != 3)
	{
		write(2, "Uso: ./client [PID_SERVER] [MENSSAGE]\n", 38);
		return (1);
	}
	pid = (pid_t)ft_atoi(argv[1]);
	config_signals();
	send_str(pid, argv[2]);
	while (1)
		pause();
	return (0);
}
