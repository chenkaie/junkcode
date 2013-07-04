SCODE BaseWork1(HANDLE hHandle, int nTimes);
SCODE BaseWork2(HANDLE hHandle, const char *pszName);
SCODE BaseRelease(HANDLE *phHandle);
static TMyVirtual g_tBaseVirtual = {BaseWork1, BaseWork2, BaseRelease};

SCODE InitBase(HANDLE *phHandle, TBaseOptions *ptOpt)
{
  TBaseInternal *ptBase = (TBaseInternal *) malloc(sizeof(TBaseInternal));
  
  if (ptBase == NULL)
      return ERR_MEMORY_ALLOC;
  
  //...
  // do init
  ptBase->tC.ptVFunc = g_tBaseVirtual;
  
  //...
  
  return S_OK;
}
 
SCODE BaseWork1(HANDLE hHandle, int nTimes)
{
  TBaseInternal *ptBase = (TBaseInternal *) hHandle;
  SCODE scRet = S_OK;

  if (ptBase == NULL)
      return ERR_INVALID_HANDLE;
 
  // do the work
  //...
  
  return scRet;
}

SCODE BaseWork2(HANDLE hHandle, const char *pszName)
{
  TBaseInternal *ptBase = (TBaseInternal *) hHandle;
  SCODE scRet = S_OK;
  
  if (ptBase == NULL)
      return ERR_INVALID_HANDLE;

  // do the work
  //...
  
  // When calling virtual function, remember to use call wrapper instead of call directly
  scRet = CallVirtualWork1(ptBase->tC.ptVFunc, hHandle, 1);   
   
  return scRet;
}

SCODE BaseRelease(HANDLE *phHandle)
{
  TBaseInternal *ptBase;
  
  if (!phHandle || !*phHandle)
      return ERR_INVALID_HANDLE;
  ptBase = (TBaseInternal *) hHandle;

  // do the work
  //...
  
  return S_OK;
}
