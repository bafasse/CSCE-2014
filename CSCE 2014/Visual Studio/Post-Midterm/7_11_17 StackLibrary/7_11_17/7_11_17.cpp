// 7_11_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stack>
#include <ctime>
#include <iostream>
using namespace std;

void tower(int count, char src, char dest, char extra)
{
	if (count == 1)
	{
		cout << "Move disk from " << src << " to " << dest << endl;
	}

	else
	{
		tower(count - 1, src, extra, dest); // first
		tower(1, src, dest, extra);
		tower(count - 1, extra, dest, src); // last
	}
}

void stackTower(int count, char src, char dest, char extra)
{
	stack<int> sCount;
	stack<char> sSrc;
	stack<char> sDest;
	stack<char> sExtra;
	sCount.push(count);
	sSrc.push(src);
	sDest.push(dest);
	sExtra.push(extra);

	while (!sCount.empty())
	{
		int curCount = sCount.top();
		char curSrc = sSrc.top();
		char curDest = sDest.top();
		char curExtra = sExtra.top();
		sCount.pop(); sSrc.pop(); sExtra.pop(); sDest.pop();

		if (curCount == 1)
		{
			cout << "Move disk from " << curSrc << " to " << curDest << endl;
		}

		else
		{
			//Make sure that for stack the order is flipped
			sCount.push(curCount - 1);	sSrc.push(curExtra);   sDest.push(curDest);   sExtra.push(curSrc); // last
			sCount.push(1);				sSrc.push(curSrc);	   sDest.push(curDest);   sExtra.push(curExtra); 
			sCount.push(curCount - 1);  sSrc.push(curSrc);     sDest.push(curExtra);  sExtra.push(curDest);// first
			
			
		}
	}
}

int main()
{

	clock_t start = clock();

	// Code to be timed here
	stackTower(3, 'A', 'C', 'B');
	cout << endl;
	tower(3, 'A', 'C', 'B');
	// ...

	clock_t end = clock();

	double runTime = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Run time: (s)" << runTime << endl;
    return 0;
}

