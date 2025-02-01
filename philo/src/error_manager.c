
#include "../includes/philo.h"

void    error_exit(const char *error)
{
    printf(RED"%s\n"RES, error);
    exit(EXIT_FAILURE);
}