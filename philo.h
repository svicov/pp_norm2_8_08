#ifndef PHILO_H
#  define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_fork
{
    pthread_mutex_t mutex; // мьютекс доступа к вилке
    int num;               // номер вилки, используется только для отладки
}	t_fork;

// Философ
typedef struct s_Philo
{
    int num;
    pthread_t thread;
    pthread_mutex_t mutex;
    struct timeval last_eat;
    int eat_count;
    
    t_fork *left_fork;  // Указатель на используемую в качестве левой вилку
    t_fork *right_fork; // Указатель на используемую в качестве правой вилку
}	t_philo;

// Стол со всеми философами и вилками
typedef struct s_Table
{
    int    philo_count;             // кол-во философов (и вилок)

    t_fork *forks;             // массив вилок
    t_philo *philos;           // массив философов
    
    int eat_period;                 // время на прием пищи
    int sleep_peroid;               // время на сон
    int die_period;                 // максимальное время между приемами пищи чтобы не умереть
    int min_eat;                    // минимальное кол-во приемов пищи, если 0, то не учитывается

    pthread_t monitor;              // поток наблюдения за столом и окончания эмуляции
    struct timeval emul_start;      // время начала эмуляции
    int simulation_end;             // флаг завершения эмуляции

    pthread_mutex_t output_mutex;   // мьютекс разграничения доступа к выводу сообщений
}	t_Table;

t_Table g_table;

void fork_init(t_fork *f, int number);
void fork_free(t_fork *f);
void fork_take(t_fork *f);
void fork_leave(t_fork *f);
void philo_init(t_philo *ph, int number, t_fork *left, t_fork *right);
void philo_free(t_philo *philo);
void table_init(t_Table * table, int nPhilo, int tDie, int tEat, int tSleep, int max_eat_count);
void table_free(t_Table *table);
void* philo_thread(void* args);
int time_diff(struct timeval* a, struct timeval* b);
void print(int nPhilo, char* msg);
void* philo_thread(void* args);
void* monitor_thread(void* args);
int	f(const char *str);
int	pars(int argc, char **a);
void *wh_table(int i, struct timeval curr, int nFullPhilos);



#endif