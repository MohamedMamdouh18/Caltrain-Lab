#include <pthread.h>
#include "caltrain.h"


void
station_init(struct station *station) {
    pthread_mutex_init(&station->enterTrain, NULL);
    pthread_cond_init(&station->trainArrived, NULL);
    pthread_cond_init(&station->trainFull, NULL);
    station->waitingPassengers = 0;

}

void
station_load_train(struct station *station, int count) {
    //no passenger waiting or the train has no empty seats
    if (count == 0 || station->waitingPassengers == 0) return;

    pthread_mutex_lock(&station->enterTrain);
    if (count > station->waitingPassengers) station->aboard = station->waitingPassengers;
    else station->aboard = count;

    station->trainCapacity = count;

    pthread_cond_broadcast(&station->trainArrived);

    pthread_cond_wait(&station->trainFull, &station->enterTrain);
    pthread_mutex_unlock(&station->enterTrain);
}

void
station_wait_for_train(struct station *station) {
    pthread_mutex_lock(&station->enterTrain);

    station->waitingPassengers++;

    while (station->trainCapacity == 0) {
        pthread_cond_wait(&station->trainArrived, &station->enterTrain);
    }
    station->trainCapacity--;
    station->waitingPassengers--;

    pthread_mutex_unlock(&station->enterTrain);
}

void
station_on_board(struct station *station) {
    pthread_mutex_lock(&station->enterTrain);
    station->aboard--;
    pthread_mutex_unlock(&station->enterTrain);

    if (station->aboard == 0 && (station->waitingPassengers == 0 || station->trainCapacity == 0)) {
        pthread_cond_signal(&station->trainFull);
    }
}
