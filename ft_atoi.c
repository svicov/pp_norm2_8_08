#include "philo.h"

static	int	poluch_chisl2(const char *st, int z)
{
	int			razr;
	int			flag;
	int			slo;

	razr = 0;
	flag = 0;
	slo = 0;
	while (47 < *st && *st <= 57 && st != '\0' && razr < 11)
	{
		if (48 < *st && *st <= 57)
			flag = 1;
		if (flag == 1)
			razr++;
		slo = slo * 10 + *(st) - '0';
		st++;
	}
	return (slo * z);
}

static	int	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || (c == 32))
		return (1);
	return (0);
}

int	f(const char *str)
{
	int			znak;
	const char	*s;

	znak = 1;
	s = str;
	while (ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			znak = -1;
		s++;
	}
	return (poluch_chisl2(s, znak));
}
