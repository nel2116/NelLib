#include "TimeManger.h"
#include <Windows.h>

// timeGetTimeŽü‚è‚ÌŽg—p
#pragma comment(lib, "winmm.lib")

void TimeManager::Init()
{
	timeBeginPeriod(1);
	m_lastTime = m_startTime = timeGetTime();
}

void TimeManager::Update()
{
	m_currentTime = timeGetTime();
	m_deltaTime = static_cast<float>(m_currentTime - m_lastTime);
}

void TimeManager::Finalize()
{
	timeEndPeriod(1);
}
