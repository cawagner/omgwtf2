#pragma once
class CDecisionEngine
{
public:
	CDecisionEngine(void);
	virtual ~CDecisionEngine(void);

	virtual BOOL GetDecision() = 0;

	virtual LPCSTR GetName() = 0;
	virtual LPCSTR GetDescription();
	virtual LPCSTR GetAuthor();
	virtual LPCSTR GetCopyright();
};

#define YES TRUE
#define NO FALSE
#define THEN_DECIDE(X) return X;
#define ELSE_DECIDE(X) else return(X);