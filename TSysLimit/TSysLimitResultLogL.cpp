#include <iostream>
#include "TSysLimitResultLogL.h"
#include <TMath.h>

//ClassImp(TSysLimitResultLogL)

void TSysLimitResultLogL::Initialize(TVectorD const &b,TVectorD const &sb,
                                     TMatrixD const &errB,TMatrixD const &errSB) {
   for(Int_t i=0;i<b.GetNoElements();i++) {
      fWeight[i]=sb[i];
   }
}

Double_t TSysLimitResultLogL::BinContribution(Double_t weight,Double_t n)
   const {
   return TMath::Log(weight)*n-weight-TMath::LnGamma(n+1.);
}
