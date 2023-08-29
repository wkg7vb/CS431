#include <iostream>
#include <thread>
using namespace std;

// these functions will simulate work for each thread to execute
//they have varying amounts of work to do so they will start and finish at different times
void WorkSim1() 
{
    cout << "Thread 1 started." << endl;

    for (int i = 0; i < 10000000; ++i) 
    {
        // do nothing
    }

    cout << "Thread 1 finished." << endl;
    return;
}

void WorkSim2()
{
    cout << "Thread 2 started." << endl;

    for (int i = 0; i < 10000; ++i)
    {
        // do nothing
    }

    cout << "Thread 2 finished." << endl;
    return;
}

void WorkSim3()
{
    cout << "Thread 3 started." << endl;

    for (int i = 0; i < 10; ++i)
    {
        // do nothing
    }

    cout << "Thread 3 finished." << endl;
    return;
}

int main() 
{
    // creates 3 threads, one for each of the above functions
    thread t1(WorkSim1);
    thread t2(WorkSim2);
    thread t3(WorkSim3);

    // waits for each thread to finish before exiting main
    t1.join();
    t2.join();
    t3.join();

    cout << "All threads finished." << endl;

    return 0;
}
