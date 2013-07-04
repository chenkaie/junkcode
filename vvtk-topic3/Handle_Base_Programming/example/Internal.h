SCODE (*PFWork1)(HANDLE, int);
SCODE (*PFWork2)(HANDLE, const char *);
SCODE (*PFRelease)(HANDLE *);

typedef struct _TMyVirtual
{
   PFWork1 pfWork1;
   PFWork2 pfWork2;
   PFRelease pfRelease;
} TMyVirtual;

typedef struct _TInternalCommon
{
   DWORD dwID;
   TMyVirtual *ptVFunc;
} TInternalCommon;

typedef struct _TBaseInternal
{
   TInternalCommon tC;
   //...    
} TBaseInternal;

typedef struct _TDerivedInternal
{
   TInternalCommon tC;
   //...    
} TDerivedInternal;

SCODE CallVirtualWork1(TMyVirtual *ptVF, HANDLE hHandle, int nTimes);
SCODE CallVirtualWork2(TMyVirtual *ptVF, HANDLE hHandle, const char *pszName);
SCODE CallVirtualRelease(TMyVirtual *ptVF, HANDLE *phHandle);
