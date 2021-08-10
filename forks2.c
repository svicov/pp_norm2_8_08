#include "philo.h"

// Инициализировать вилку f
void	fork_init(t_fork *f, int number)
{
	pthread_mutex_init(&f->mutex, NULL);
	f->num = number;
}

// Уничтожить вилку f
void	fork_free(t_fork *f)
{
	pthread_mutex_destroy(&f->mutex);
}

// Взять вилку f
// Если вилка занята, поток блокируется, пока вилка не освободится
void	fork_take(t_fork *f)
{
	pthread_mutex_lock(&f->mutex);
}

// Положить вилку
// Если вилка уже лежит, то ничего не делает
void	fork_leave(t_fork *f)
{
	pthread_mutex_unlock(&f->mutex);
}
