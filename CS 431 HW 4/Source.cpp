#include <iostream>
#include <thread>
#include <semaphore>
#include <queue>
#include <chrono>
using namespace std;

//global semaphores and buffer
counting_semaphore<3> emptySem{ 3 };
counting_semaphore<3> fullSem{ 0 };
binary_semaphore mutexSem{ 1 };
queue<int> buffer;

void producer()
{
	for(int p = 1; p <= 10; p++)
	{
		//produce
		cout << "Produced " << p << endl;

		//wait for empty buffer slot
		emptySem.acquire();
		
		//add to buffer (critical section)
		mutexSem.acquire();

		buffer.push(p);

		mutexSem.release();
		
		//signal that buffer slot is full
		fullSem.release();

		//wait .1 seconds
		this_thread::sleep_for(chrono::milliseconds(100));
	}

	return;
}

void consumer()
{
	int temp = 0;
	for(int c = 1; c <= 10; c++)
	{
		//wait for buffer to have a full slot
		fullSem.acquire();
		
		//remove from buffer (critical section)
		mutexSem.acquire();

		temp = buffer.front();
		buffer.pop();

		mutexSem.release();

		//signal that buffer has an empty slot
		emptySem.release();

		//consume
		cout << "Consumed " << temp << endl;
		temp = 0;

		//wait .3 second
		this_thread::sleep_for(chrono::milliseconds(300));
	}
	return;
}

int main()
{
	thread consumerTh(consumer);
	thread producerTh(producer);
	
	consumerTh.join();
	producerTh.join();

	return 0;
}