#include "TSysLimitResultPBock.h"
#include <TMath.h>
#include <iostream>

//ClassImp(TSysLimitResultPBock)

using namespace std;

TSysLimitResultPBock::TSysLimitResultPBock(Double_t k1,Double_t k2,
                                           Bool_t includeSys) :
   fUseSys(includeSys),fK1(k1),fK2(k2) {
}

void TSysLimitResultPBock::Initialize
(TVectorD const &b,TVectorD const &sb,
 TMatrixD const &errB,TMatrixD const &errSB) {
   if(!fUseSys) {
      for(Int_t i=0;i<b.GetNoElements();i++) {
         if(sb[i]+b[i]>0.0)
            fWeight[i]=(sb[i]-b[i])/(sb[i]+b[i]);
         else
            fWeight[i]=0.0;
      }
   } else {
      Int_t n=fWeight.GetNoElements();
      TArrayI m2bin(n),bin2m(n);
      Int_t m=0;
      // get valid bins
      for(Int_t i=0;i<n;i++) {
         if(sb[i]+b[i]>0.0) {
            m2bin[m]=i;
            bin2m[i]=m;
            m++;
         } else {
            bin2m[i]=-1;
         }
      }
      TMatrixD a(m,m),rhs(m,1);
      for(Int_t i=0;i<m;i++) {
         Int_t iBin=m2bin[i];
         a(i,i)=fK1*sb[iBin]+fK2*b[iBin];
         rhs(i,0)=sb[iBin]-b[iBin];
         for(Int_t j=0;j<m;j++) {
            Int_t jBin=m2bin[j];
            a(i,j) += fK1*errSB(iBin,jBin)+fK2*errB(iBin,jBin);
         }
      }
      a.Invert();
      TMatrixD w(a,TMatrixD::kMult,rhs);
      for(Int_t i=0;i<n;i++) {
         Int_t m=bin2m[i];
         if(m>=0) fWeight[i]=w(m,0);
         else fWeight[i]=0.0;
      }
   }
}
