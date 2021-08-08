#include "philo.h"

// функция потока наблюдения за столом (за философами)
// Функция потока может остановить эмуляцию
void* monitor_thread(void* args)
{
    (void)args; //////////  !!!!!!!!!
    while (1)
    {
        // текущее время наблюдения
        struct timeval curr;
        gettimeofday(&curr, NULL);

        int nFullPhilos = 0; // количество сытых философов

        // Наблюдаем за всеми философами
        for (int i =0; i < g_table.philo_count; i++)
        {
            t_philo *ph = &g_table.philos[i]; // текущий наблюдаемый философ
            pthread_mutex_lock(&ph->mutex);      // получаем доступ, только этот поток может менять переменные филосософа

            // время после последнего приема пищи
            int time_after_int = time_diff(&curr, &ph->last_eat);

            // проверка смерти от голода
            if (time_after_int > g_table.die_period)
            {
                print(g_table.philos[i].num, "died");

                // остановка симуляции
                g_table.simulation_end++;
                pthread_mutex_unlock(&ph->mutex);
                return NULL;
            }

            // Сытый ли текущий философ
            if (g_table.min_eat && (ph->eat_count >= g_table.min_eat))
                nFullPhilos++;

            pthread_mutex_unlock(&ph->mutex);
        }

        // Если все философы сыты, остановка симуляции
        if (nFullPhilos == g_table.philo_count)
        {
            //print(0, "all complete");

            g_table.simulation_end++;
            return NULL;
        }
    }
}
