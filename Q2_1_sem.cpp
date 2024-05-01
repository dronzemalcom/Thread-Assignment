#include <iostream>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <chrono> 
using namespace std;
// Write a program to create two threads. One thread will run the function called runMeFirst, and the other thread runs the 
// function runMeSecond. The function runMeFirst displays the sentence "Run me first" and the runMeSecond function displays 
// "I run second". Use semaphores to make the function runMeFirst runs before the function runMeSecond.

sem_t sem;

void runMeFirst() {
    
    cout << "Run me first" << endl;
    sem_post(&sem);
}


void runMeSecond() {
 
    cout << "Thread 2(runMeSecond) is waiting..." << endl;
    sem_wait(&sem); // blocking call
    cout << "Thread 2(runMeSecond)  has acquired the semaphore" << endl;
    cout << "I run second " << endl;

}


int main() {
    sem_init(&sem, 0, 0);
   
    // Create threads
     thread t2(runMeSecond); 
     thread t1(runMeFirst);
   // thread t2(runMeSecond);

    // Join threads
    t1.join();
    t2.join();
    
    sem_destroy(&sem); // destroy the semaphore
    return 0;
}