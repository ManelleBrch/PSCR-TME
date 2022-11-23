#include <ctime>
#include <cstdlib>
#include "rsleep.h"

void randsleep() {
  int r = rand();
  double ratio = (double)r / (double) RAND_MAX;
  struct timespec tosleep;
  tosleep.tv_sec =0;
  // 300 millions de ns = 0.3 secondes
  tosleep.tv_nsec = 300000000 + ratio*700000000;
  struct timespec remain;
  while ( nanosleep(&tosleep, &remain) != 0) {
    tosleep = remain;
  }
}

/*
 * Q4) nanosleep sert à suspendre l'execution d'un thread jusqu'à un temps indiqué dans le premier argument
 * ou jusqu'à réception d'un signal -> si réception d'un signal renvoie -1 avec errno = EINTR + le temps restant dans le premier argument
 *
 * pq while et pas if?
*/

/*
 * Q5) On utilise srand(time(0));
*/
