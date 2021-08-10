#include "philo.h"

void	table_ini1(t_Table *table, int argc, char **a)
{
	table->eat_period = f(a[3]);
	table->sleep_peroid = f(a[4]);
	table->die_period = f(a[2]);
	if (argc == 6)
		table->min_eat = f(a[5]);
	else
		table->min_eat = 0;
}
// Инициализация стола

void	table_init(t_Table *table, int argc, char **a)
{
	int	i;
	int	nForks;

	nForks = f(a[1]);
	table->forks = (t_fork *)malloc(nForks * sizeof(t_fork));
	i = 0;
	while (i < nForks)
	{
		fork_init(&table->forks[i], i + 1);
		i++;
	}
	table->philo_count = f(a[1]);
	table->philos = (t_philo *)malloc(f(a[1]) * sizeof(t_philo));
	i = 0;
	while (i < f(a[1]))
	{
		philo_init(&table->philos[i],
			i + 1, &table->forks[i], &table->forks[(i + 1) % nForks]);
		i++;
	}
	table_ini1(table, argc, a);
	gettimeofday(&table->emul_start, NULL);
	table->simulation_end = 0;
	pthread_mutex_init(&table->output_mutex, NULL);
}

// Разрушение стола
void	table_free(t_Table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		fork_free (&table->forks[i]);
		philo_free(&table->philos[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
	pthread_mutex_destroy(&table->output_mutex);
}
