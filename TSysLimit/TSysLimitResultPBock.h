#ifndef ROOT_TSysLimitResultPBock
#define ROOT_TSysLimitResultPBock

#include "TSysLimitResult.h"

class TSysLimitResultPBock : public TSysLimitResult {
public:
   TSysLimitResultPBock(Double_t k1,Double_t k2,Bool_t includeSys);
protected:
   virtual void Initialize(TVectorD const &b,TVectorD const &sb,
                           TMatrixD const &errB,TMatrixD const &errSB);
   Bool_t fUseSys;
   Double_t fK1,fK2;
//   ClassDef(TSysLimitResultPBock, 0) //Limit calculation results
};

#endif
