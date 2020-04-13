#include "vt.h"
#include <iostream>
using namespace std;

int groupNumber = 10;

int* solve(TestAgent* agent) 
{
	
	int length = agent->getSampleNumber();
	int* result = new int[length];
	int start = 0;
	int end = start + groupNumber;
	int* tests = new int[groupNumber];
	int exitFlag = 0;
	while (1) {
		if (end>=length) {
			exitFlag = 1;
			end = length;
		}

		int len = end - start;
		for (int i = 0; i < len; i++) {
			tests[i] = start + i;
		}

		int temp = agent->test(tests,len);

		if (temp == 0) {
			for (int i = 0; i < len; i++) {
				result[start + i] = 0;
			}
		}
		else
		{
			for (int i = 0; i < len; i++) {
				tests[0] = start + i;
				result[start + i] = agent->test(tests,1);
			}
		}

		if (exitFlag) {
			break;
		}
		start += groupNumber;
		end += groupNumber;
	}
	
	return result;
}


int main()
{
	TestAgent* agent;
	
	for (int i = 2; i < 21; i++) {
		groupNumber = i;
		agent = new TestAgent(solve);
		agent->getResult();
		delete agent;
	}

	
	return 0;
}