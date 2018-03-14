#ifndef ROOT_TSysLimitResultLogL
#define ROOT_TSysLimitResultLogL

#include "TSysLimitResult.h"

class TSysLimitResultLogL : public TSysLimitResult {
public:
protected:
   virtual void Initialize(TVectorD const &b,TVectorD const &sb,
                           TMatrixD const &errB,TMatrixD const &errS);
   virtual Double_t BinContribution(Double_t weight,Double_t n) const;

//   ClassDef(TSysLimitResultLogL, 0) //Limit calculation results
};

#endif
