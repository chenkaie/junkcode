SCODE CallVirtualWork1(TMyVirtual *ptVF, HANDLE hHandle, int nTimes)
{
   return ptVF->pfWork1(hHandle, nTimes);
}
 
SCODE Work1(HANDLE hHandle, int nTimes)
{
  TInternalCommon *ptComm = (TInternalCommon *) hHandle;
    
  // check if ptComm is valid by nullity and the Id checking
    
  return CallVirtualWork1(ptComm->ptVFunc, hHandle, nTimes);
}
 
SCODE CallVirtualWork2(TMyVirtual *ptVF, HANDLE hHandle, const char *pszName)
{
   return ptVF->pfWork2(hHandle, pszName);
}

SCODE Work2(HANDLE hHandle, const char *pszName)
{
  TInternalCommon *ptComm = (TInternalCommon *) hHandle;
 
  // check if ptComm is valid by nullity and the Id checking
 
  return CallVirtualWork2(ptComm->ptVFunc, hHandle, pszName);
}

SCODE CallVirtualRelease(TMyVirtual *ptVF, HANDLE *phHandle)
{
   return ptVF->pfRelease(phHandle);
}

SCODE Release(HANDLE *phHandle)
{
  TInternalCommon *ptComm = (TInternalCommon *) hHandle;

  // check if ptComm is valid by nullity and the Id checking
  return CallVirtualRelease(ptComm->ptVFunc, phHandle);
}
