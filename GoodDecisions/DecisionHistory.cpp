#pragma once
#include "stdafx.h"
#include "DecisionHistory.h"
#include <string.h>

#define MAX_DECISION_HISTORY_SIZE sizeof(DECISION_STORAGE_TYPE) * 8
#define CRYPTOKEY 7

CDecisionHistory::CDecisionHistory(void)
{
	m_ubcDecision = 0;
	m_llDecision = 0;
}


CDecisionHistory::~CDecisionHistory(void)
{
	m_ubcDecision = 0;
	m_llDecision = 0;
}

unsigned char CDecisionHistory::GetDecisions(BOOL** lpfaDecicions)
{
	 // Since it's auto the garbage collector will handle deleting this.
	auto lpfDecisions = new BOOL[MAX_DECISION_HISTORY_SIZE + 1];

	if (lpfaDecicions != NULL)
	{
		(*lpfaDecicions) = lpfDecisions;
	}

	int bit = 1;
	for (int i = 0; i < MAX_DECISION_HISTORY_SIZE; i++)
	{
		lpfDecisions[i] = m_llDecision & bit;
		bit = bit + bit;
	}

	return m_ubcDecision;
}


BOOL CDecisionHistory::PushDecision(BOOL fDecision)
{
	int newDecision = m_ubcDecision + 1;

	if (newDecision < MAX_DECISION_HISTORY_SIZE)
	{
		int bit = 1;
		for (int i = 1; i < newDecision; ++i)
		{
			bit = bit + bit;
		}
		if (fDecision)
		{
			m_llDecision = m_llDecision | bit;
		}
		else
		{
			m_llDecision = m_llDecision & ~bit;
		}
		m_ubcDecision = newDecision;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDecisionHistory::PopDecision(BOOL* lpfDecision)
{
	if (m_ubcDecision <= 0)
	{
		return FALSE;
	}
	m_ubcDecision = m_ubcDecision - 1;

	int bit = 1;
	for (int i = 1; i < m_ubcDecision; i++)
	{
		bit = bit + bit;
	}
	lpfDecision = new BOOL(m_llDecision & bit);
	return TRUE;
}

BOOL CDecisionHistory::IsHostoryFull()
{
	if (m_ubcDecision + 1 >= MAX_DECISION_HISTORY_SIZE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDecisionHistory::ClearDecisions()
{
	memset(&m_ubcDecision, 0, sizeof(m_ubcDecision));
	memset(&m_llDecision, 0, sizeof(m_llDecision));
	return BOOL();
}

BOOL CDecisionHistory::Save()
{
	// auto is a lifesaver!
	auto folder = new TCHAR[MAX_PATH + 1];
	memset(folder, 0, MAX_PATH * sizeof TCHAR);

	if (SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, folder) == S_OK)
	{
		auto folder2 = new TCHAR[MAX_PATH + 1];
		memset(folder2, 0, MAX_PATH * sizeof TCHAR);
		if (PathCombine(folder2, folder, "MyApp") != NULL)
		{
			if (CreateDirectory(folder2, NULL) == FALSE)
			{
				if (GetLastError() == ERROR_ALREADY_EXISTS) 
				{
					// this one is fine!
				}
				else
				{
					// there ARE legitimate use cases for goto
					goto botched;
				}
			}
			if (PathCombine(folder2, folder, "MyApp\\Datum2.txt") != NULL)
			{
				if (HANDLE file = CreateFile(folder2, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL))
				{
					char buffer[200] = "";
					sprintf(buffer, "%d %d", Encript(m_ubcDecision), Encript(m_llDecision));
					if (WriteFile(file, buffer, strlen(buffer) * sizeof(char) + 1, NULL, NULL) == TRUE)
					{
						if (CloseHandle(file) == TRUE)
							{
								return TRUE;
						}
					}
				}
			}
		}
	}
botched:
	return FALSE;
}

BOOL CDecisionHistory::Load()
{
	// auto is a lifesaver!
	auto folder = new TCHAR[MAX_PATH + 1];
	memset(folder, 0, MAX_PATH * sizeof TCHAR);

	if (SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, folder) == S_OK)
	{
		auto folder2 = new TCHAR[MAX_PATH + 1];
		memset(folder2, 0, MAX_PATH * sizeof TCHAR);
		if (PathCombine(folder2, folder, "MyApp") != NULL)
		{
			//if (CreateDirectory(folder2, NULL) == FALSE)
			//{
			//	if (GetLastError() == ERROR_ALREADY_EXISTS) 
			//	{
			//		// this one is fine!
			//	}
			//	else
			//	{
			//		// there ARE legitimate use cases for goto
			//		goto botched;
			//	}
			//}
			if (PathCombine(folder2, folder, "MyApp\\Datum.txt") != NULL)
			{
				if (HANDLE file = CreateFile(folder2, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL))
				{
					char buffer[200] = "";
					if (ReadFile(file, buffer, sizeof(char) * (200 - 1), NULL, NULL) == TRUE)
					{
						int a, b;
						sscanf(buffer, "%d %d", &a, &b);
						m_ubcDecision = Decript(a);
						m_llDecision = Decript(b);
						
						if (CloseHandle(file) == TRUE)
						{
							return TRUE;
						}
					}
					else
					{
						goto botched;
					}
				}
			}
		}
	}
botched:
	return FALSE;
}

int CDecisionHistory::Encript(int lData)
{
	// you casn't protect all your date form every hackyer, but you might as well slow them down a little
	return lData ^ CRYPTOKEY;
}

int CDecisionHistory::Decript(int lData)
{
	return CRYPTOKEY ^ lData;
}