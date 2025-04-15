/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:13:53 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/04/15 17:45:50 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 199309L
#define _XOPEN_SOURCE 500
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

volatile sig_atomic_t running;
// static volatile int	running;

int	ft_atoi(char *s)
{
	int	sign;
	int res;
	
	sign = 1;
	res = 0;
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -sign;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + *s - '0';
		s++;
	}
	return (res * sign);
}

void handler(int signum, siginfo_t *info, void *ctx)
{
	(void)ctx;
	(void)info;
	(void)signum;
	write(1, "[SIG]", 5);
	running = 1;
}

void	send_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 7;
	running = 1;
	while (i >= 0)
	{
		if (running == 1)
		{
			if ((c >> i) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i--;
			usleep(1000);
			running = 0;
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*str;
	int		i;
	struct	sigaction sa;
	
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	if (argc != 3)
	{
		write(2, "Uso: ./client [PID_SERVER] [MENSSAGE]\n", 38);
		return (1);
	}
	pid = (pid_t)ft_atoi(argv[2]);
	str = argv[1];
	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
	return (0);
}
