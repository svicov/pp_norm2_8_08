#include "philo.h"

// Функция потока философа
// принимает в качестве аргумента указатель на философа, возвращает NULL

unsigned long my_time(void) ///////////////////////
{
	struct timeval t_time;

	gettimeofday(&t_time, 0);
	return ((t_time.tv_sec * 1000) + (t_time.tv_usec / 1000));
}

void ft_usleep(unsigned long ms_sec) //////////////////////////
{
	unsigned long start;

	start = my_time();

	while (my_time() - start < ms_sec)
		usleep(500);
}

int	life_cycl(t_philo *p)
{
	fork_take(p->right_fork);
	print(p->num, "has taken a fork");
	if (g_table.simulation_end)
		return (1);
	pthread_mutex_lock(&p->mutex);
	gettimeofday(&p->last_eat, NULL);
	print(p->num, "is eating");
	pthread_mutex_unlock(&p->mutex);
	ft_usleep(g_table.eat_period); /////////////////
	if (g_table.simulation_end)
		return (1);
	fork_leave(p->left_fork);
	fork_leave(p->right_fork);
	pthread_mutex_lock(&p->mutex);
	p->eat_count++;
	pthread_mutex_unlock(&p->mutex);
	print(p->num, "is sleeping");
	ft_usleep(g_table.sleep_peroid); //////////////////
	if (g_table.simulation_end)
		return (1);
	return (0);
}

void	*philo_thread(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	while (g_table.simulation_end == 0)
	{
		print(p->num, "is thinking");
		fork_take(p->left_fork);
		print(p->num, "has taken a fork");
		if (g_table.simulation_end)
			break ;
		if (p->right_fork == p->left_fork)
		{
			while (!g_table.simulation_end)
				usleep(1000);
			break ;
		}
		if (life_cycl(p))
			break ;
	}
	fork_leave(p->left_fork);
	fork_leave(p->right_fork);
	return (NULL);
}
