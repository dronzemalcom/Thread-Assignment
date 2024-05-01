#include <iostream>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <chrono> 
using namespace std;

sem_t sem1, sem2;

void runMeFirst() {
    
    cout << "Run me first" << endl;
    sem_post(&sem1);
}

void runMeSecond() {
 
    cout << "Thread 2(runMeSecond) is waiting..." << endl;
    sem_wait(&sem1); // blocking call
    cout << "Thread 2(runMeSecond)  has acquired the semaphore" << endl;
    cout << "I run second " << endl;
    sem_post(&sem2);

}
void runMeThird() {
 
    cout << "Thread 3(runMeThird) is waiting..." << endl;
    sem_wait(&sem2); // blocking call
    cout << "Thread 3(runMeThird)  has acquired the semaphore" << endl;
    cout << "I run Third " << endl;

}


int main() {
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);

   
    // Create threads
     thread t3(runMeThird); 
     thread t2(runMeSecond); 
     thread t1(runMeFirst);
   // thread t2(runMeSecond);

    // Join threads
    t1.join();
    t2.join();
    t3.join();
    
    sem_destroy(&sem1); // destroy the semaphore
    sem_destroy(&sem2); // destroy the semaphore

    return 0;
}