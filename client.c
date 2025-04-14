/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:13:53 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/04/14 08:59:33 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

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

void	send_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*str;
	int		i;

	if (argc != 3)
	{
		write(2, "Uso: ./client [PID_SERVIDOR] [MENSAJE]\n", 38);
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
