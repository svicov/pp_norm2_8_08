#include "philo.h"

// функция потока наблюдения за столом (за философами)
// Функция потока может остановить эмуляцию
void	*monitor_thread(void *args)
{
	struct timeval	curr;

	(void)args;
	while (1)
	{
		gettimeofday(&curr, NULL);
		if (wh_table(0, curr, 0))
			return (NULL);
		usleep(5000);
	}
}

int	ft_mutex_unlo(t_philo *ph)
{
	pthread_mutex_unlock(&ph->mutex);
	return (1);
}

int	wh_table(int i, struct timeval curr, int nFullPhilos)
{
	t_philo	*ph;
	int		time_after_int;

	while (i < g_table.philo_count)
	{
		ph = &g_table.philos[i];
		pthread_mutex_lock(&ph->mutex);
		time_after_int = time_diff(&curr, &ph->last_eat);
		if (time_after_int > g_table.die_period)
		{
			print(g_table.philos[i].num, "died");
			g_table.simulation_end++;
			pthread_mutex_unlock(&ph->mutex);
			return (1);
		}
		if (g_table.min_eat && (ph->eat_count >= g_table.min_eat))
			nFullPhilos++;
		i = i + ft_mutex_unlo(ph);
	}
	if (nFullPhilos == g_table.philo_count)
	{
		g_table.simulation_end++;
		return (1);
	}
	return (0);
}
