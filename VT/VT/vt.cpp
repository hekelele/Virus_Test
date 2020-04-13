#include "vt.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
using namespace std;

TestGroup::TestGroup(int sampleNum, float positiveRate)
{
	this->sampleNum = sampleNum;
	this->positiveRate = positiveRate;
	this->samples = new int[sampleNum];
	srand((unsigned)time(NULL));
	int positive = positiveRate * 100;
	for (int i = 0; i < sampleNum; i++) {
		this->samples[i] = rand() % 100 < positive;
	}
}

TestGroup::~TestGroup()
{
	delete this->samples;
}

int TestGroup::test(int sample[], int length)
{
	for (int i = 0; i < length; i++) {
		if (this->samples[sample[i]]) {
			return 1;
		}
	}

	return 0;
}

int TestGroup::checkAnswer(int * answers)
{
	for (int i = 0; i < this->sampleNum; i++) {
		if (this->samples[i] != answers[i]) {
			return 0;
		}
	}
	return 1;
}


TestAgent::TestAgent(SolveFunction sf)
{
	this->group = new TestGroup(DEFAULT_TEST_NUMBER, DEFAULT_POSITIVE_RATE);
	this->testTimes = 0;
	this->length = DEFAULT_TEST_NUMBER;
	this->positiveRate = DEFAULT_POSITIVE_RATE;
	this->solve = sf;
}

TestAgent::~TestAgent()
{
	delete this->group;
}

int TestAgent::test(int sample[], int length)
{
	this->testTimes++;
	return this->group->test(sample,length);
}

int TestAgent::getSampleNumber()
{
	return this->length;
}

void TestAgent::getResult()
{
	this->testTimes = 0;
	int* answer = this->solve(this);
	if (this->group->checkAnswer(answer)) {
		cout << "Results:"
			<< endl
			
			<< "Sample Number: " << this->length
			<< endl
			
			<< "Positive Rate: " 
			<< setprecision(5)
			<< this->positiveRate
			<< endl

			<< "Average Test Time Per Sample: "
			<< setprecision(5)
			<< this->testTimes * 1.0 / this->length
			<< endl;
	}
	else
	{
		cout << "This answer is NOT CORRECT!" << endl;
		int* one = new int[1];
		for (int i = 0; i < (this->length > 20 ? 20 : this->length); i++) {
			one[0] = i;
			cout << this->group->test(one, 1) << " - " << answer[i] << endl;
		}
	}
	
	delete answer;
	return;
}

