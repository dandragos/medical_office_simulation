#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_DOCTORS 3
#define MAX_CONSULTATION_TIME 10
#define MAX_WAIT_TIME 5
#define NUM_PATIENTS 10

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    int doctor_id;
    int is_busy;
} Doctor;

Doctor doctors[NUM_DOCTORS];

void* patient_thread(void* arg) {
    int patient_id = *(int*)arg;
    int random_wait = rand() % MAX_WAIT_TIME + 1;

    sleep(random_wait);

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    int i;
    for (i = 0; i < NUM_DOCTORS; i++) {
        pthread_mutex_lock(&doctors[i].mutex);
        if (!doctors[i].is_busy) {
            printf("Patient %d is seeing Doctor %d\n", patient_id, i);
            doctors[i].is_busy = 1;
            pthread_mutex_unlock(&doctors[i].mutex);
            sleep(rand() % MAX_CONSULTATION_TIME + 1);
            gettimeofday(&end_time, NULL);
            printf("Patient %d finished seeing Doctor %d\n", patient_id, i);

            long int wait_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + end_time.tv_usec - start_time.tv_usec;
            printf("Patient %d waited for %ld microseconds\n", patient_id, wait_time);

            pthread_mutex_lock(&doctors[i].mutex);
            doctors[i].is_busy = 0;
            pthread_cond_signal(&doctors[i].condition);
            pthread_mutex_unlock(&doctors[i].mutex);
            break;
        } else {
            pthread_mutex_unlock(&doctors[i].mutex);
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t patients[NUM_PATIENTS];
    int patient_ids[NUM_PATIENTS];

   
    int i;
    for (i = 0; i < NUM_DOCTORS; i++) {
        doctors[i].doctor_id = i;
        doctors[i].is_busy = 0;
        pthread_mutex_init(&doctors[i].mutex, NULL);
        pthread_cond_init(&doctors[i].condition, NULL);
    }

 
    for (i = 0; i < NUM_PATIENTS; i++) {
        patient_ids[i] = i;
        pthread_create(&patients[i], NULL, patient_thread, &patient_ids[i]);
    }

    for (i = 0; i < NUM_PATIENTS; i++) {
        pthread_join(patients[i], NULL);
    }


    for (i = 0; i < NUM_DOCTORS; i++) {
        pthread_mutex_destroy(&doctors[i].mutex);
        pthread_cond_destroy(&doctors[i].condition);
    }

    return 0;
}
