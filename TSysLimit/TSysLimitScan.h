#ifndef ROOT_TSysLimitScan
#define ROOT_TSysLimitScan

#include <TObjArray.h>

class TSysLimit;
class TSysLimitResult;

class TSysLimitScan : public TObject {
public:
   TSysLimitScan(TSysLimit &limit,Int_t scanMax=50);
   ~TSysLimitScan(void);
   enum EConficenceLevelType {
      kConficenceLevelTypeCLS=0,
      kConficenceLevelTypeCLSB=1
   };
   void DoScan(Double_t cl,Double_t scartScale=1.0,
               Int_t method=-1,Double_t signalScalePrecision=0.01,
               EConficenceLevelType cltype=kConficenceLevelTypeCLS,
               Int_t nTotal=50000,Int_t nSysPrescale=10,
               Bool_t generateFakeData=kFALSE);
   TSysLimitResult const *GetDataLimit(void) const;
   TSysLimitResult const *GetExpectedLimit(void) const;
   inline Int_t GetScanSize(void) const { return fResults.GetEntries(); }
   inline TSysLimitResult const *GetLimit(Int_t index) const {
      	return (TSysLimitResult const *)fResults[index]; 
    	}
   void Print(Int_t verbose=1) const;
protected:
   FILE *logFile;
   TObjArray fResults;
   TSysLimit &fSysLimit;
   Int_t fData,fExpected,fScanMax;
   Int_t GetCL(Double_t scale,Int_t method,
               Int_t nTotal,Int_t nSysPrescale);
//   ClassDef(TSysLimitScan,0) // Conficence level scan
};

#endif
