#include "stdafx.h"
#include "EngineBox.h"

#include "stdlib.h"

#define ENGINE(X, nm, dd) class X : public CDecisionEngine { LPCSTR GetName() { return nm; } LPCSTR GetDescription() { return dd; }
#define DECIDE BOOL GetDecision() { 
#define ENGINEEND }};

ENGINE(CCoinFlipEngine, "Coin Flip", "Simulates a coin flip (50/50).")
	DECIDE if (rand() % 2 == 0) THEN_DECIDE(YES) ELSE_DECIDE(NO);
ENGINEEND

ENGINE(CYesManEngine, "Yes Man", "He always says yes.")
	DECIDE return YES;
ENGINEEND

ENGINE(CNaysayerEngine, "Naysayer", "He always says no.")
	DECIDE return NO;
ENGINEEND

ENGINE(CFriendEngine, "Supportive Friend", "He usually says yes but is sometimes firm.")
	DECIDE if (rand() % 3 > 0) THEN_DECIDE(YES) ELSE_DECIDE(NO);
ENGINEEND

ENGINE(CSpouseEngine, "Sitcom Spouse", "She is usually a nag but sometimes is sweet.")
	DECIDE if (rand() % 3 > 0) THEN_DECIDE(NO) ELSE_DECIDE(YES);
ENGINEEND

static BOOL m_fFlip;
ENGINE(CFlipFlopEngine, "Flip Flopper", "John Kerry, is that you?")
	DECIDE
		if (m_fFlip == TRUE)
		{
			m_fFlip = FALSE;
		}
		else if (m_fFlip == FALSE)
		{
			m_fFlip = TRUE;
		}
		else
		{
			// not sure why we're ever getting in here, but true flip floppers say 'no' first, so we should be okay
			m_fFlip = FALSE;
		}
		return m_fFlip;
ENGINEEND

CEngineBox::CEngineBox(void)
{
	m_dcEngines = 0;
	m_diEngines = 0;
}


CEngineBox::~CEngineBox(void)
{
	memset(this, 0, sizeof CEngineBox);
}

void CEngineBox::LoadEngines()
{
	int i = 0;
	if (m_dcEngines <= 0) // only load engines if they haven't been loaded yet
	{
		// too long to type repeatedly...
#define PSHNGN(EEE); m_lpcdeEngines[++i-1] = new C ## EEE();
		PSHNGN(CoinFlipEngine)
		PSHNGN(YesManEngine)
		PSHNGN(NaysayerEngine)
		PSHNGN(FriendEngine)
		PSHNGN(SpouseEngine)
		PSHNGN(FlipFlopEngine)
#undef PUSHENGINE
		m_dcEngines = 5;
	}
}

void CEngineBox::BeginEnumerateEngines()
{
	m_diEngines = 0;
}

CDecisionEngine* CEngineBox::GetNextEngine()
{
	CDecisionEngine *engine(NULL);
	if (m_diEngines <= m_dcEngines) {
		engine = m_lpcdeEngines[m_diEngines];
		m_diEngines = m_diEngines += 1;
	}
	return engine;
}

CDecisionEngine* CEngineBox::operator*(int scalar)
{
	return m_lpcdeEngines[scalar];
}