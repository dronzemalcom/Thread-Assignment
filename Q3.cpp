#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <chrono> 
#include <condition_variable>
using namespace std;

struct requestStructure { //format for the data will be storing
    int request_id; 
    string ip_address;
    string page_requested;
};

// Global variables
mutex mtx;
condition_variable cv;
int count = 1;
queue<requestStructure> msg_queue; // queue that will hold the structs use pop and push please
string webPages[10] = {"google.com", "yahoo.com", "onlinegbd.com", "youtube.com", "canvas.com", "ridge.com", "gmail.com", "turkey.com", "redblueyellow.com", "amazon.com"};

//  sleep for random number between 1-3 seconds using sleep_for instruction. CHECKK
//  generate a request with request_id from a counter shared, ip_address as an empty string and page_request as 
//  a random web page name from the array webPages defined above; then save the request in msg_queue.
//  notify one thread to consume it
void listen() {
    srand(time(0));
    while(true){
        this_thread::sleep_for(chrono::seconds(rand() % 3 + 1));
        
        requestStructure r;
        r.request_id = count; // set the counter curent value to the request id starting at 1
        r.ip_address = "";  // ip address is just an emptyv string cool
        r.page_requested = webPages[rand() % 9 + 0]; // Randomly grab a webpage 
        {
            lock_guard< mutex> lock(mtx);
            msg_queue.push(r); // push the struct to a queue
            count++;
        }
        cv.notify_one();
    }

};   

// if the msg_queue is empty, then wait using conditional variable else get the request from the msg_queue
// display a message; "thread thread_id completed request request_id requesting webpage page_requested"; 
//  where thread_id is the id number of the thread, the request_id is the id number of the request and
//  page_requested as the web page requested.
void do_request(int thread_id){
    while(true) {
    unique_lock< mutex> lock(mtx);
    cv.wait(lock, []{return !msg_queue.empty();});
    requestStructure r = msg_queue.front();
    msg_queue.pop();
    cout << "Thread:  " << thread_id << " completed. Request:   " << r.request_id << " requesting Webpage: " << r.page_requested << endl;
    lock.unlock();
    
    };
    cv.notify_one();
}; 



int main() {
    thread listener(listen); // generate a listen class thning
    // generate the ip addresses
    const int num_threads = 10;
    //generate the threads
    thread threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {
    threads[i] = thread(do_request, i + 1); // i can be the thread id cuz rn we have no way of keepin track of that
    }
    // join the threads
    for (int i = 0; i < num_threads; ++i) {
    threads[i].join();
    }
    return 0;
}