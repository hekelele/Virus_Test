#pragma once
class TestGroup
{
public:
	TestGroup(int sampleNum, float positiveRate);
	~TestGroup();
	int test(int sample[], int length);
	int checkAnswer(int* answers);

private:
	int*	samples;
	int		sampleNum;
	float	positiveRate;
};


#define DEFAULT_TEST_NUMBER		10000
#define DEFAULT_POSITIVE_RATE	0.1

class TestGroup;

class  TestAgent
{
	typedef int* (*SolveFunction)(TestAgent*);
public:
	TestAgent(SolveFunction sf);
	~TestAgent();
	int test(int sample[], int length);
	int getSampleNumber();
	void getResult();

private:
	SolveFunction solve;
	TestGroup* group;
	int testTimes;
	int length;
	float positiveRate;
};




