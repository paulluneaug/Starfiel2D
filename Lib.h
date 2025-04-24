#pragma once
#include <ctime>
#include <chrono>

using namespace std::chrono;

class Lib
{
public:
	static double GetTimeStampNs();
	static double GetTimeStamp();
};

