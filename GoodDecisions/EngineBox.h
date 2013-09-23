#pragma once

#include "DecisionEngine.h"
#define MAX_SUPPORTED_DECISION_ENGINES 1024

class CEngineBox
{
public:
	CEngineBox(void);
	~CEngineBox(void);

	void LoadEngines();

	void BeginEnumerateEngines();
	CDecisionEngine* GetNextEngine();
	CDecisionEngine* operator*(int scalar);

private:
	int m_dcEngines;
	int m_diEngines;
	CDecisionEngine* m_lpcdeEngines[MAX_SUPPORTED_DECISION_ENGINES];
};

