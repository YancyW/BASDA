#include "TSysLimitResult.h"
#include <TMath.h>
#include <iostream>

#include <TArrayI.h>
#include <TH1.h>

//ClassImp(TSysLimitResult)

using namespace std;

TSysLimitResult::TSysLimitResult() {
	fXb=0;
	fXsb=0;
}

TSysLimitResult::~TSysLimitResult(void) {
}

void TSysLimitResult::Initialize(Double_t scale,
		TVectorD const &b,TVectorD const &sb,
		TMatrixD const &errB,TMatrixD const &errSB) {
	fSignalScale=scale;
	fWeight.ResizeTo(b.GetNoElements());
	fXdata=0.;
	if(fXb) {
		delete fXb;
	}
	if(fXsb) {
		delete fXsb;
	}
	fXb=new TToyDistribution();
	fXsb=new TToyDistribution();
	Initialize(b,sb,errB,errSB);
}

Double_t TSysLimitResult::GetX(TVectorD const &exp) const {
	Double_t r=0.;
	for(Int_t i=0;i<fWeight.GetNrows();i++) {
		r += fWeight[i]*exp[i];
	}
	return r;
}

void TSysLimitResult::Initialize(TVectorD const &b,TVectorD const &sb,
		TMatrixD const &errB,TMatrixD const &errSB) {
	for(Int_t i=0;i<b.GetNoElements();i++) {
		if((sb[i]>0.0)&&(b[i]>0.0))
			fWeight[i]=TMath::Log(sb[i]/b[i]);
		else
			fWeight[i]=0.0;
	}
}

void TSysLimitResult::SetDataExperiment(TVectorD const &bins) {
	fXdata=GetX(bins);
}

void TSysLimitResult::AddBExperiment(TVectorD const &bins) {
	fXb->Add(GetX(bins));
}

void TSysLimitResult::AddSBExperiment(TVectorD const &bins) {
	fXsb->Add(GetX(bins));
}

void TSysLimitResult::Finalize(void) {
	cout<<"Xdata="<<fXdata<<"\n";
	fXb->Finalize();
	cout<<"<Xb>="<<fXb->GetAvgX()<<" RMS="<<fXb->GetRmsX()<<"\n";
	fXsb->Finalize();
	cout<<"<Xsb>="<<fXsb->GetAvgX()<<" RMS="<<fXsb->GetRmsX()<<"\n";
}

Double_t TSysLimitResult::GetDataCLs(Double_t powerConstraint) const {
	Double_t Xpco=GetXPowerConstraint(fXdata,powerConstraint);
	return (1.-fXsb->GetPValue(Xpco))/(1.-fXb->GetPValue(Xpco));
}

Double_t TSysLimitResult::GetDataCLb(Double_t powerConstraint) const {
	Double_t Xpco=GetXPowerConstraint(fXdata,powerConstraint);
	return 1.-fXb->GetPValue(Xpco);
}

Double_t TSysLimitResult::GetDataCLsb(Double_t powerConstraint) const {
	Double_t Xpco=GetXPowerConstraint(fXdata,powerConstraint);
	// J.L. return 1.-fXb->GetPValue(Xpco);
	return 1.-fXsb->GetPValue(Xpco);
}

Double_t TSysLimitResult::GetExpectedCLs(void) const {
	Double_t Xbg=fXb->GetXForPvalue(0.5);
	return (1.-fXsb->GetPValue(Xbg))/(1.-fXb->GetPValue(Xbg));
}

Double_t TSysLimitResult::GetExpectedCLb(void) const {
	Double_t Xbg=fXb->GetXForPvalue(0.5);
	return (1.-fXb->GetPValue(Xbg));
}

Double_t TSysLimitResult::GetExpectedCLsb(void) const {
	Double_t Xbg=fXb->GetXForPvalue(0.5);
	return (1.-fXsb->GetPValue(Xbg));
}

Double_t TSysLimitResult::GetXPowerConstraint
(Double_t xIn,Double_t powerConstraint) const {
	Double_t x=xIn;
	if(powerConstraint>0.0) {
		Double_t x2=fXb->GetXForPvalue(1-powerConstraint);
		//       if(x2>x) {
		//         cout << "X(1sigma) = " << x2 << " > X(data) = " << x << "=> applying power constraint! " << endl;
		//         x=x2;
		//       }
		if(x2>x) {
			cout << "X(1sigma) = " << x2 << " > X(data) = " << x << "=> applying power constraint! " << endl;
			x=x2;
		}
	} else if(powerConstraint<0.0) {
		cout << "powerConstraint = " << powerConstraint << " < 0.0, calculating -1 sigma band" << endl;
		x=fXb->GetXForPvalue(-(1-powerConstraint));
	}
	return x;
}

void TSysLimitResult::GetTestStatHistograms(TH1 *bLtData,TH1* bGtData,
		TH1 *sbLtData,TH1* sbGtData,
		TH1 *bLtToy,TH1 *bGtToy,
		TH1 *sbLtToy,TH1 *sbGtToy,
		Double_t powerConstraint) {
	Double_t xdata=GetXPowerConstraint(fXdata,powerConstraint);
	Double_t xbg=fXb->GetXForPvalue(0.5);
	fXb->FillHistograms(xdata,bLtData,bGtData);
	fXb->FillHistograms(xbg,bLtToy,bGtToy);
	fXsb->FillHistograms(xdata,sbLtData,sbGtData);
	fXsb->FillHistograms(xbg,sbLtToy,sbGtToy);
}

void TToyDistribution::Add(Double_t x) {
	fXmult[x]++;
}

// #define WRITE_DISTRIBUTION

void TToyDistribution::Finalize(void) {
#ifdef WRITE_DISTRIBUTION
	static int number=0;
	TString name=TString::Format("probability_%03d.vec",number);
	++number;
	ofstream output(name);
#endif
	Double_t nEvent=0;
	for(map<Double_t,Int_t>::const_iterator i=fXmult.begin();i!=fXmult.end();++i) {
		nEvent += (*i).second;
	}
	Double_t p0=1.0;
	for(map<Double_t,Int_t>::const_iterator i=fXmult.begin();i!=fXmult.end();++i) {
		Double_t p1=p0-(*i).second/nEvent;
		Double_t p=0.5*(p0+p1);
		fXtoP[(*i).first]=p;
		fPtoX[p]=(*i).first;
#ifdef WRITE_DISTRIBUTION
		output<<p0<<" "<<p1<<" "<<(*i).first<<"\n";
#endif
		p0=p1;
	}
}

Double_t TToyDistribution::GetPValue(Double_t x) const {
	if(fXtoP.size()==0) return 0.;
	if(fXtoP.size()==1) return (*fXtoP.begin()).second;

	map<Double_t,Double_t>::const_iterator i1=fXtoP.lower_bound(x);
	// x<= lower_bound
	// or x> end
	if(i1==fXtoP.end()) --i1;
	map<Double_t,Double_t>::const_iterator i0=i1;
	if(i1!=fXtoP.begin()) --i0;
	else ++i0;
	Double_t x0=(*i0).first;
	Double_t x1=(*i1).first;
	Double_t p0=(*i0).second;
	Double_t p1=(*i1).second;
	Double_t r=(x-x0)/(x1-x0)*(p1-p0)+p0;
	if(r<0.0) {
		r=0.0;
	}
	if(r>1.0) {
		r=1.0;
	}
	return r;
}

Double_t TToyDistribution::GetRmsX(void) const {
	Double_t sw=0.,sx=0.,sx2=0.;
	for(map<Double_t,Int_t>::const_iterator i=fXmult.begin();
			i!=fXmult.end();++i) {
		Double_t w=(*i).second;
		sw += w;
		sx += (*i).first * w;
		sx2 += (*i).first*(*i).first *w;
	}
	sx /= sw;
	sx2 /= sw;
	if(sx2<=sx*sx) {
		cout<<"TToyDistribution::GetRmsX "
			<<sx2<<" "<<sx*sx<<"\n";
		for(map<Double_t,Int_t>::const_iterator i=fXmult.begin();
				i!=fXmult.end();++i) {
			cout<<(*i).first<<" "<<(*i).second<<"\n";
		}
		exit(0);
	}
	return TMath::Sqrt(sx2-sx*sx);
}

Double_t TToyDistribution::GetAvgX(void) const {
	Double_t sw=0.,sx=0.;
	for(map<Double_t,Int_t>::const_iterator i=fXmult.begin();
			i!=fXmult.end();++i) {
		Double_t w=(*i).second;
		sw += w;
		sx += (*i).first;
	}
	return sx / sw;
}

Double_t TToyDistribution::GetAvgXcut(Double_t xcut) const {
	Double_t sw=0.,sx=0.;
	for(map<Double_t,Int_t>::const_iterator i=fXmult.begin();
			i!=fXmult.end();++i) {
		if((*i).first>xcut) {
			Double_t w=(*i).second;
			sw += w;
			sx += (*i).first;
		}
	}
	return sx / sw;
}

Double_t TToyDistribution::GetXForPvalue(Double_t pValue) const {
	if(fPtoX.size()==0) return 0.;
	if(fPtoX.size()==1) return (*fPtoX.begin()).second;
	map<Double_t,Double_t>::const_iterator i1=fPtoX.lower_bound(pValue);
	// x<= lower_bound
	// or x> end
	if(i1==fPtoX.end()) --i1;
	map<Double_t,Double_t>::const_iterator i0=i1;
	if(i0!=fPtoX.begin()) --i0;
	else ++i0;
	Double_t p0=(*i0).first;
	Double_t p1=(*i1).first;
	Double_t x0=(*i0).second;
	Double_t x1=(*i1).second;

	return (pValue-p0)/(p1-p0)*(x1-x0)+x0;
}

Double_t TToyDistribution::GetDensity(Double_t x) const {
	Double_t dx=((*fXtoP.rbegin()).first-(*fXtoP.begin()).first)/
		TMath::Sqrt(fPtoX.size());
	Double_t r=(GetPValue(x-dx)-GetPValue(x+dx))/(2.*dx);
	/* if(error) {
	 *error=1./fP2X.size()/dx;
	 } */
	return r;
}

Double_t TToyDistribution::GetPValueWithcut
(Double_t x,Double_t xmin) const {
	Double_t r;
	Double_t pnorm=GetPValue(xmin);
	Double_t p1=GetPValue(x);
	if(pnorm>0.0) {
		r=p1/pnorm;
	} else {
		r=1.0;
	}
	if(r<0.0) r=0.0;
	if(r>1.0) r=1.0;
	return r;
}

void TToyDistribution::FillHistograms(Double_t x,TH1 *lower,TH1 *higher)
	const {
		for(map<Double_t,Int_t>::const_iterator i=fXmult.begin();
				i!=fXmult.end();++i) {
			if((*i).first>x) {
				if(higher) higher->Fill((*i).first, (*i).second);
			} else {
				if(lower) lower->Fill((*i).first, (*i).second);
			}
		}
	}
