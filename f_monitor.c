#include "philo.h"

// функция потока наблюдения за столом (за философами)
// Функция потока может остановить эмуляцию
void* monitor_thread(void* args)
{
    struct timeval curr;
    int i;

    (void)args; //////////  !!!!!!!!! udalit'
    while (1)
    {        
        gettimeofday(&curr, NULL);
        int nFullPhilos = 0; // количество сытых философов
        i =0;
         wh_table(i, curr, nFullPhilos);
       // while (i < g_table.philo_count) // Наблюдаем за всеми философами
      //  {
           
           //  t_philo *ph = &g_table.philos[i]; // текущий наблюдаемый философ
           //  pthread_mutex_lock(&ph->mutex);      // получаем доступ, только этот поток может менять переменные филосософа            
           //  int time_after_int = time_diff(&curr, &ph->last_eat);// время после последнего приема пищи            
           //  if (time_after_int > g_table.die_period)// проверка смерти от голода
           //  {
           //      print(g_table.philos[i].num, "died");                
           //      g_table.simulation_end++;// остановка симуляции
           //      pthread_mutex_unlock(&ph->mutex);
           //      return NULL;
           //  }            
           //  if (g_table.min_eat && (ph->eat_count >= g_table.min_eat))// Сытый ли текущий философ 
           //      nFullPhilos++;
           //  pthread_mutex_unlock(&ph->mutex);
        //    i++;
       // }        
        if (nFullPhilos == g_table.philo_count)// Если все философы сыты, остановка симуляции
        {
            g_table.simulation_end++;//print(0, "all complete");
            return NULL;
        }
    }
}

void *wh_table(int i, struct timeval curr, int nFullPhilos)
{    
    while (i < g_table.philo_count) // Наблюдаем за всеми философами
    {
        t_philo *ph;
        int time_after_int;
        ph = &g_table.philos[i];
        pthread_mutex_lock(&ph->mutex);
        time_after_int = time_diff(&curr, &ph->last_eat);
        if (time_after_int > g_table.die_period)// проверка смерти от голода
        {
            print(g_table.philos[i].num, "died");                
            g_table.simulation_end++;// остановка симуляции
            pthread_mutex_unlock(&ph->mutex);
            return NULL;
        }
        if (g_table.min_eat && (ph->eat_count >= g_table.min_eat))// Сытый ли текущий философ 
            nFullPhilos++;
        pthread_mutex_unlock(&ph->mutex);
        i++;
    }
    if (nFullPhilos == g_table.philo_count)// Если все философы сыты, остановка симуляции
    {
        g_table.simulation_end++;//print(0, "all complete");
        return NULL;
    }      
}