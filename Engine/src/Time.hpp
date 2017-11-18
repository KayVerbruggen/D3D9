#pragma once
#include <stdint.h>
#include <Windows.h>

static float DeltaTime;

int64_t CountsPerSecond;
float SecondsPerCount;
int64_t PrevTime = 0;
__int64 CurrentTime = 0;

void StartTimer()
{
	// System for getting DeltaTime and FPS
	QueryPerformanceFrequency((LARGE_INTEGER*)&CountsPerSecond);
	SecondsPerCount = 1.0f / CountsPerSecond;

	QueryPerformanceCounter((LARGE_INTEGER*)&PrevTime);
}

void UpdateTimer()
{
	// Capture current time
	QueryPerformanceCounter((LARGE_INTEGER*)&CurrentTime);

	// Calculate delta time
	DeltaTime = (CurrentTime - PrevTime) * SecondsPerCount;
}

void SetPrevTime()
{
	PrevTime = CurrentTime;
}