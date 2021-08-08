#include "philo.h"

int	main(int argc, char **a)
{	
	int	i;

	pars(argc, a);
	i = 0;
	while (i < g_table.philo_count)
	{
		pthread_create(&(g_table.philos[i].thread), NULL,
			philo_thread, &g_table.philos[i]);
		usleep(50);
		i++;
	}
	pthread_create(&g_table.monitor, NULL, monitor_thread, NULL);
	i = 0;
	while (i < g_table.philo_count)
	{
		pthread_join(g_table.philos[i].thread, NULL);
		i++;
	}
	pthread_join(g_table.monitor, NULL);
	table_free(&g_table);
	return (0);
}

int	pars(int argc, char **a)
{
	if (argc == 5)
		table_init(&g_table, f(a[1]), f(a[2]), f(a[3]), f(a[4]), 0);
	else if (argc == 6)
		{
			table_init(&g_table, f(a[1]), f(a[2]), f(a[3]), f(a[4]), f(a[5]));
			return (0);
		}		
		else
		{
			printf("invalid arg\n");
			return (1);
		}
	return (0);	
}
