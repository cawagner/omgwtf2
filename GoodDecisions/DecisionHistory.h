#pragma once

#ifdef PROFESSIONAL_EDITION
#define DECISION_STORAGE_TYPE int
#else
#define DECISION_STORAGE_TYPE short
#endif

class CDecisionHistory
{
public:
	CDecisionHistory(void);
	~CDecisionHistory(void);

	BOOL IsHostoryFull(void);
	BOOL PushDecision(BOOL bDecision);
	BOOL PopDecision(BOOL* lpbDecision);
	BOOL ClearDecisions();

	unsigned char GetDecisions(BOOL** lpbaDecicions);

	BOOL Save();
	BOOL Load();
private:
	int Encript(int datum);
	int Decript(int mutad);

	unsigned char m_ubcDecision;
	DECISION_STORAGE_TYPE m_llDecision;
};

