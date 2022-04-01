#include "BestScoresTableClass.h"

BestScoresTableClass::BestScoresTableClass()
{
	Lines = new BestScoresLineClass[10];
}

int BestScoresTableClass::BufferSize()
{
	return Lines[0].LineSize() * 10;
}

void BestScoresTableClass::LoadFrom(char* Buffer)
{
	char* b = Buffer;
	for (int i = 0; i < 10; i++)
	{
		Lines[i].LoadFrom(b);
		b = b + Lines[i].LineSize();
	}
}

void BestScoresTableClass::SaveTo(char* Buffer)
{
	char* b = Buffer;
	for (int i = 0; i < 10; i++)
	{
		Lines[i].SaveTo(b);
		b = b + Lines[i].LineSize();
	};
}

BestScoresTableClass::~BestScoresTableClass()
{
	delete[] Lines;
}
