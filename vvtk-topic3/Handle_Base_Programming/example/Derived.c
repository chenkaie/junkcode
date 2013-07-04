SCODE DerivedWork1(HANDLE hHandle, int nTimes);
SCODE DerivedWork2(HANDLE hHandle, const char *pszName);
SCODE DerivedRelease(HANDLE *phHandle);
static TMyVirtual g_tDerivedVirtual = {DerivedWork1, DerivedWork2, DerivedRelease};

SCODE InitDerived(HANDLE *phHandle, TDerivedOptions *ptOpt)
{
  TDerivedInternal *ptDerived = (TDerivedInternal *) malloc(sizeof(TDerivedInternal));
  
  if (ptDerived == NULL)
      return ERR_MEMORY_ALLOC;
  
  //...
  // do init
  ptDerived->tC.ptVFunc = g_tDerivedVirtual;
  
  //...
  
  return S_OK;
}
 
SCODE DerivedWork1(HANDLE hHandle, int nTimes)
{
  TDerivedInternal *ptDerived = (TDerivedInternal *) hHandle;
  SCODE scRet = S_OK;

  if (ptDerived == NULL)
      return ERR_INVALID_HANDLE;

  // do the work
  //...
  
  return S_OK;
}

SCODE DerivedWork2(HANDLE hHandle, const char *pszName)
{
  TDerivedInternal *ptDerived = (TDerivedInternal *) hHandle;
  SCODE scRet = S_OK;
  
  if (ptDerived == NULL)
      return ERR_INVALID_HANDLE;

  // do the work
  //...
     
  
  // When calling virtual function, remember to use call wrapper instead of call directly
  scRet = CallVirtualWork1(ptDerived->tC.ptVFunc,  hHandle, 1);

  return S_OK;
}

SCODE DerivedRelease(HANDLE *phHandle)
{
  TDerivedInternal *ptDerived;
  
  if (!phHandle || !*phHandle)
      return ERR_INVALID_HANDLE;
  ptDerived = (TDerivedInternal *) hHandle;

  // do the work
  //...
  
  return S_OK;
}
