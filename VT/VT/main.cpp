#include "vt.h"
#include <iostream>
using namespace std;

int* solve(TestAgent* agent) 
{
	int length = agent->getSampleNumber();
	int* result = new int[length];
	int* one = new int[1];
	for(int i = 0; i < length; i++) {
		one[0] = i;
		result[i] = agent->test(one, 1);
	}
	
	return result;
}

int main()
{
	TestAgent* agent = new TestAgent(solve);
	agent->getResult();
	delete agent;
	return 0;
}