#include "philo.h"

// Инициализация философа
void philo_init(t_philo *ph, int number, t_fork *left, t_fork *right)
{
    ph->num = number;
    ph->left_fork = left;
    ph->right_fork = right;

    pthread_mutex_init(&ph->mutex, NULL);

    gettimeofday(&ph->last_eat, NULL);
}

// Разрушение философа
void philo_free(t_philo *philo)
{
    pthread_mutex_destroy(&philo->mutex);
}

// Возвращает разницу в миллисекундах между временем a и временем b
int time_diff(struct timeval* a, struct timeval* b)
{
    return (a->tv_sec - b->tv_sec) * 1000 + (a->tv_usec - b->tv_usec) / 1000;
}

// печатает сообщение msg от философа с номером nPhilo
void print(int nPhilo, char* msg)
{
    // только один поток одноврменно может выводить сообщения
    pthread_mutex_lock(&g_table.output_mutex); 

    // время вывода сообщения
    struct timeval curr;
    gettimeofday(&curr, NULL);

    // время от начала эмуляции в миллисекундах
    int fromBegin = time_diff(&curr, &g_table.emul_start); //Время в выводе не совпадает c реальным временем на которое проверяется смерть 
    printf("%d %d %s\n", fromBegin, nPhilo, msg);

    pthread_mutex_unlock(&g_table.output_mutex);
}
