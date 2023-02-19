#include <pthread.h>

struct station {
	// FILL ME IN
    pthread_mutex_t enterTrain ;
    pthread_cond_t trainArrived ;
    pthread_cond_t trainFull ;
    int trainCapacity ;
    int waitingPassengers ;
    int aboard ;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);