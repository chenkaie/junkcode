#include "header.h"
SCODE InitBase(HANDLE *phHandle, TBaseOptions *ptOpt);
SCODE InitDerived(HANDLE *phHandle, TDerivedOptions *ptOpt);

SCODE Work1(HANDLE hHandle, int nTimes);
SCODE Work2(HANDLE hHandle, const char *pszName);

SCODE Release(HANDLE *phHandle);
