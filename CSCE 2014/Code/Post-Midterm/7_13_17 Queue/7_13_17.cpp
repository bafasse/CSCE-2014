// 7_13_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include "Queue.h"

void iterate(Queue<int> queue[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (!queue[i].isEmpty())
		{
			int value;
			queue[i].front(value);
			queue[i].update(value - 1);
			

			if (value - 1 <= 0)
			{
				queue[i].remove(value);
			}
		}
	}

}

void printAll(Queue<int> queue[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << (i + 1) << ": ";
		queue[i].print();
	}
	cout << endl;
}

int main()
{
	const int SIZE = 3;
	const int TIME_STEPS = 20;
	const int MAX_ITEMS = 20;
	const int CUSTOMER_PROB = 40;
	Queue<int> queue[SIZE];

	for (int i = 0; i < TIME_STEPS; ++i)
	{
		//cout << "0 = " <<queue[0].getSize() << endl;
		//cout << "1 = " << queue[1].getSize() << endl;
		// If a customer should arrive
		// create a customer and add them to the shortest queue
		if (rand() % 100 < CUSTOMER_PROB)
		{
			// Figure out which queue is the shortest
			// Insert into the shortest queue
			int small = 0;
			for (int j = 0; j < SIZE; ++j)
			{
				if (queue[j].getSize() < queue[small].getSize())
					small = j;
			}
			queue[small].insert(rand() % MAX_ITEMS);
		}
			
		iterate(queue, SIZE);

		printAll(queue, SIZE);
	}

	// Store closing
	bool done = false;
	while (!done)
	{
		iterate(queue, SIZE);

		printAll(queue, SIZE);

		done = true;
		for (int i = 0; i < SIZE; ++i)
			if (!queue[i].isEmpty())
				done = false;
	}
	 
		
    return 0;
}

