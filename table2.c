#include "philo.h"

// Инициализация стола
void table_init(t_Table * table, int nPhilo, int tDie, int tEat, int tSleep, int max_eat_count)
{
    int nForks = nPhilo;
    
    table->forks = (t_fork*)malloc(nForks * sizeof(t_fork));
    for (int i = 0; i < nForks; i++)
        fork_init(&table->forks[i], i + 1);
        
    table->philo_count = nPhilo;
    table->philos = (t_philo*)malloc(nPhilo * sizeof(t_philo));
    for (int i = 0; i < nPhilo; i++)
        philo_init(&table->philos[i], i + 1, &table->forks[i], &table->forks[(i + 1) % nForks]);
        
    table->eat_period = tEat;
    table->sleep_peroid = tSleep;
    table->die_period = tDie;
    table->min_eat = max_eat_count;

    gettimeofday(&table->emul_start, NULL);
    
    table->simulation_end = 0;

    pthread_mutex_init(&table->output_mutex, NULL);
}

// Разрушение стола
void table_free(t_Table *table)
{
    for (int i = 0; i < table->philo_count; i++){
        fork_free (&table->forks[i]);
        philo_free(&table->philos[i]);
    }

    free(table->forks);
    free(table->philos);  

    pthread_mutex_destroy(&table->output_mutex);
}
