#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				num;
}	t_fork;

// Философ
typedef struct s_Philo
{
	int				num;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	struct timeval	last_eat;
	int				eat_count;
	t_fork			*left_fork;
	t_fork			*right_fork;
}	t_philo;

// Стол со всеми философами и вилками
typedef struct s_Table
{
	int				philo_count;
	t_fork			*forks;
	t_philo			*philos;
	int				eat_period;
	int				sleep_peroid;
	int				die_period;
	int				min_eat;
	pthread_t		monitor;
	struct timeval	emul_start;
	int				simulation_end;
	pthread_mutex_t	output_mutex;
}	t_Table;

t_Table				g_table;

void	fork_init(t_fork *f, int number);
void	fork_free(t_fork *f);
void	fork_take(t_fork *f);
void	fork_leave(t_fork *f);
void	philo_init(t_philo *ph, int number, t_fork *left, t_fork *right);
void	philo_free(t_philo *philo);
void	table_init(t_Table *table, int argc, char **a);
void	table_free(t_Table *table);
void	*philo_thread(void *args);
int		time_diff(struct timeval *a, struct timeval *b);
void	print(int nPhilo, char *msg);
void	*philo_thread(void *args);
void	*monitor_thread(void *args);
int		f(const char *str);
int		pars(int argc, char **a);
int		wh_table(int i, struct timeval curr, int nFullPhilos);
int		life_cycl(t_philo *p);
#endif