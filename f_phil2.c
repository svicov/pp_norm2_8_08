#include "philo.h"

// Функция потока философа
// принимает в качестве аргумента указатель на философа, возвращает NULL
void* philo_thread(void* args)
{
    t_philo *p = (t_philo*)args;

    // Цикл (думать - есть - спать)
    while (g_table.simulation_end == 0) {

        print(p->num, "is thinking");

        // Философ думает, пока не возьмет две вилки
        // Сначала левую...
        fork_take(p->left_fork);
        print(p->num, "has taken a fork");

        if (g_table.simulation_end)
            break;

        // Если философ один, то его левая вилка будет указывать на правую
        // поэтому взять ее еще один раз не получится (будет бесконечное ожидание)
        // В этом случае просто ждем завершения эмуляции
        // Поток наблюдения должен отследить голод этого философа и завершить эмуляцию
        if (p->right_fork == p->left_fork)
        {
            // ожидаем завершения симуляции
            while (!g_table.simulation_end)
                usleep(1000);

            break;
        }

        // ... затем правую
        fork_take(p->right_fork);
        print(p->num, "has taken a fork");

        if (g_table.simulation_end)
            break;

        // last_eat и eat_count могут читаться из несольких потоков
        // (поток философа и поток наблюдения)
        // поэтому защищаем их мьютексом философа
        pthread_mutex_lock(&p->mutex);

        gettimeofday(&p->last_eat, NULL); // время начала приема пищи
        print(p->num, "is eating");
        pthread_mutex_unlock(&p->mutex);

        // Ожидаем завершения приема пищи
        usleep(g_table.eat_period * 1000);
        if (g_table.simulation_end)
            break;

        // Кладем вилки на стол
        fork_leave(p->left_fork);
        fork_leave(p->right_fork);

        pthread_mutex_lock(&p->mutex);
        p->eat_count++;
        pthread_mutex_unlock(&p->mutex);

        // теперь сон
        print(p->num, "is sleeping");

        // ожидаем завершение сна
        usleep(g_table.sleep_peroid * 1000);
        if (g_table.simulation_end)
            break;
    }
    // На случай если симуляция остановилась внутри цикла
    // освобождаем (кладем на стол) вилки
    fork_leave(p->left_fork);
    fork_leave(p->right_fork);

    return NULL;
}