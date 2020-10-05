#include "TSysLimitChannel.h"


#include <TCanvas.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TObjString.h>
#include <iostream>

#define DEBUG

//ClassImp(TSysLimitChannel)

TSysLimitChannel::TSysLimitChannel(Bool_t includeOverflow) {
	fIncludeOverflowBins=includeOverflow;
	fTemplate=0;
	fSignalSys.SetOwnerKeyValue();
	fBgrSys.SetOwnerKeyValue();
	fDataError=0;
	fDataErrorType=kDataErrorTypePoisson;
}

TSysLimitChannel::~TSysLimitChannel(void) {
	if(fTemplate) delete fTemplate;
	fTemplate=0;
	if(fDataError) delete fDataError;
	fDataError=0;
}

TSysLimitChannel::TSysLimitChannelError
TSysLimitChannel::UnpackHistogram(const TH1 *h,TVectorD *c,TVectorD *e) {
	TSysLimitChannelError error=kErrorNone;
	if(!fTemplate) {
		// need to give cloned histogram another name, otherwise memory leak
		TString hname = h->GetName();
		hname.Append("_clone");
		fTemplate=(TH1 *)h->Clone(hname);
	}
	if(fTemplate->GetDimension()!=h->GetDimension())
		error=kErrorBinning;
	// check number of bins in X
	if(fTemplate->GetNbinsX()!=h->GetNbinsX())
		error=kErrorBinning;



	Int_t startBinX=1;
	Int_t endBinX=fTemplate->GetNbinsX()+1;
	if(fIncludeOverflowBins) {
		startBinX--;
		endBinX++;
	}
	Int_t n=endBinX-startBinX;
	if(fTemplate->GetDimension()<=1) {
		// copy content of 1-dimensional histogram
		c->ResizeTo(n);
		if(e) e->ResizeTo(n);
		n=0;
		for(Int_t ix=startBinX;ix<endBinX;ix++) {
			(*c)[n]=h->GetBinContent(ix);
			if(e) (*e)[n]=h->GetBinError(ix);
			n++;
		}
	} else {
		if(fTemplate->GetNbinsY()!=h->GetNbinsY())
			error=kErrorBinning;
		Int_t startBinY=1;
		Int_t endBinY=fTemplate->GetNbinsY()+1;
		if(fIncludeOverflowBins) {
			startBinY--;
			endBinY++;
		}
		if(fTemplate->GetDimension()==2) {
			n *= (endBinY-startBinY);
			c->ResizeTo(n);
			if(e) e->ResizeTo(n);
			n=0;
			for(Int_t ix=startBinX;ix<endBinX;ix++) {
				for(Int_t iy=startBinY;iy<endBinY;iy++) {
					(*c)[n]=h->GetBinContent(ix,iy);
					if(e) (*e)[n]=h->GetBinError(ix,iy);
					n++;
				}
			}
		} else {
			if(fTemplate->GetNbinsZ()!=h->GetNbinsZ())
				error=kErrorBinning;
			Int_t startBinZ=1;
			Int_t endBinZ=fTemplate->GetNbinsZ()+1;
			if(fIncludeOverflowBins) {
				startBinZ--;
				endBinZ++;
			}
			n *= (endBinZ-startBinZ);
			c->ResizeTo(n);
			if(e) e->ResizeTo(n);
			n=0;
			for(Int_t ix=startBinX;ix<endBinX;ix++) {
				for(Int_t iy=startBinY;iy<endBinY;iy++) {
					for(Int_t iz=startBinZ;iz<endBinZ;iz++) {
						(*c)[n]=h->GetBinContent(ix,iy,iz);
						if(e) (*e)[n]=h->GetBinError(ix,iy,iz);
						n++;
					}
				}
			}
		}
	}
	return error;
}

TH1 *TSysLimitChannel::ToHistogram(Int_t offset,TVectorD const *content,
		TVectorD const *error) const {
	TH1 *r = 0;
	if (fTemplate) {
		// need to give cloned histogram another name, otherwise memory leak
		TString hname = fTemplate->GetName();
		hname.Append("_clone");
		r = (TH1 *)fTemplate->Clone(hname);
	}  
	if(r) {
		Int_t startBinX=1;
		Int_t endBinX=r->GetNbinsX()+1;
		if(fIncludeOverflowBins) {
			startBinX--;
			endBinX++;
		}
		Int_t n=offset;
		if(r->GetDimension()<=1) {
			// copy content of 1-dimensional histogram
			for(Int_t ix=startBinX;ix<endBinX;ix++) {
				if(content) r->SetBinContent(ix,(*content)[n]);
				if(error) r->SetBinError(ix,(*error)[n]);
				n++;
			}
		} else {
			Int_t startBinY=1;
			Int_t endBinY=r->GetNbinsY()+1;
			if(fIncludeOverflowBins) {
				startBinY--;
				endBinY++;
			}
			if(r->GetDimension()==2) {
				for(Int_t ix=startBinX;ix<endBinX;ix++) {
					for(Int_t iy=startBinY;iy<endBinY;iy++) {
						if(content) r->SetBinContent(ix,iy,(*content)[n]);
						if(error) r->SetBinError(ix,iy,(*error)[n]);
						n++;
					}
				}
			} else {
				Int_t startBinZ=1;
				Int_t endBinZ=r->GetNbinsZ()+1;
				if(fIncludeOverflowBins) {
					startBinZ--;
					endBinZ++;
				}
				for(Int_t ix=startBinX;ix<endBinX;ix++) {
					for(Int_t iy=startBinY;iy<endBinY;iy++) {
						for(Int_t iz=startBinZ;iz<endBinZ;iz++) {
							if(content) r->SetBinContent(ix,iy,iz,(*content)[n]);
							if(error) r->SetBinError(ix,iy,iz,(*error)[n]);
							n++;
						}
					}
				}
			}
		}
	}
	return r;
}

TSysLimitChannel::TSysLimitChannelError TSysLimitChannel::SetData(TH1 const *data,TSysLimitChannelDataErrorType dataErrorType) {
	TSysLimitChannelError error;
	if(fDataError) delete fDataError;
	fDataError=0;
	fDataErrorType=dataErrorType;
	if(fDataErrorType!=kDataErrorTypePoisson) {
		fDataError=new TVectorD();
	}
	error=UnpackHistogram(data,&fData,fDataError);
	// ensure that all data points are >0
	for(Int_t i=0;i<fData.GetNoElements();i++) {
		if(error!=kErrorNone) break;
		switch(fDataErrorType) {
			case kDataErrorTypePoisson:
				if(fData[i] != TMath::Floor(fData[i]))
					error=kErrorContent;
				if(fData[i]<0.0) error=kErrorContent;
				break;
			case kDataErrorTypeAbsolute:
				if(!((*fDataError)[i]>0.0)) error=kErrorContent;
				break;
			case kDataErrorTypeRelative:
			case kDataErrorTypeMeasured:
				if(!((*fDataError)[i]>0.0)) error=kErrorContent;
				if(fData[i]==0.0) error=kErrorContent;
				break;
		}
	}
	return error;
}

TSysLimitChannel::TSysLimitChannelError TSysLimitChannel::SetPrediction (TH1 const *signal,TH1 const *bgr,Bool_t useErrors) {
	TSysLimitChannelError error,error2;
	error=UnpackHistogram(signal,&fSignal,&fSignalError);
	error2=UnpackHistogram(bgr,&fBgr,&fBgrError);
	if((error == kErrorNone)&&(error2 != kErrorNone)) error=error2;
	// ensure all bins bage bgr>0 and sig+bgr>0, clear error if requested
	for(Int_t i=0;i<fBgr.GetNoElements();i++) {
		if((fBgr[i]+fSignal[i]<0.0)&&(!error)) error=kErrorContent;
		if((fSignal[i]<0.0)&&(!error)) error=kErrorContent;
		if(!useErrors) {
			fBgrError[i]=0.0;
			fSignalError[i]=0.0;
		}
	}
	return error;
}

TSysLimitChannel::TSysLimitChannelError TSysLimitChannel::AddSysUpDown
(TH1 const *signalUp,TH1 const *signalDown,TH1 const *backgroundUp,
 TH1 const *backgroundDown,char const *name,
 Double_t uncorrFrac,Double_t scale) {
	TSysLimitChannelError error,error2;
	TObject *exists=fSignalSys.FindObject(name);
	if(exists) return kErrorName;
	// create new arrays and add them to the lists of errors
	TVectorD signalUpVec,signalDownVec;
	TVectorD bgrUpVec,bgrDownVec;
	// unpack histograms
	error=UnpackHistogram(signalUp,&signalUpVec,0);
	error2=UnpackHistogram(signalDown,&signalDownVec,0);
	if((error == kErrorNone)&&(error2 != kErrorNone)) error=error2;
	error2=UnpackHistogram(backgroundUp,&bgrUpVec,0);
	if((error == kErrorNone)&&(error2 != kErrorNone)) error=error2;
	error2=UnpackHistogram(backgroundDown,&bgrDownVec,0);
	if((error == kErrorNone)&&(error2 != kErrorNone)) error=error2;

	//
	TVectorD *signalVec=new TVectorD();
	TVectorD *bgrVec=new TVectorD();
	signalVec->ResizeTo(signalUpVec.GetNoElements());
	bgrVec->ResizeTo(bgrUpVec.GetNoElements());
	fSignalSys.Add(new TObjString(name),signalVec);
	fBgrSys.Add(new TObjString(name),bgrVec);

	// loop over arrays, symmetrize errors, apply scaling
	Double_t fcorr;
	if(uncorrFrac<0.0) {
		uncorrFrac=0.0;
		fcorr=1.0;
	} else if(uncorrFrac>=1.0) {
		uncorrFrac=1.0;
		fcorr=0.0;
	} else {
		fcorr=TMath::Sqrt(1.-uncorrFrac*uncorrFrac);
	}
	Double_t e;
	for(Int_t i=0;i<signalVec->GetNoElements();i++) {

		e=(signalUpVec[i]-signalDownVec[i])*0.5*scale;
		if(uncorrFrac>0.0)
			fSignalError[i] = hypot( fSignalError[i],e*uncorrFrac);
		(*signalVec)[i] = e*fcorr;

		e=(bgrUpVec[i]-bgrDownVec[i])*0.5*scale;
		if(uncorrFrac>0.0) fBgrError[i] = hypot(fBgrError[i],e*uncorrFrac);
		(*bgrVec)[i] = e*fcorr;
#ifdef DEBUG
		std::cout<<"TSysLimitChannel::AddSysUpDown: fSignalError[" << i << "]=" <<fSignalError[i]<<", fBgrError[" << i << "]=" <<fBgrError[i]<<std::endl;
		std::cout<<"TSysLimitChannel::AddSysUpDown: (*signalVec)[" << i << "]=" <<(*signalVec)[i]<<", (*bgrVec)[" << i << "]=" <<(*bgrVec)[i]<<std::endl;
#endif
	}
	return error;
}

TSysLimitChannel::TSysLimitChannelError TSysLimitChannel::AddSysAbsolute
(TH1 const *deltaSignal,TH1 const *deltaBackground,char const *name,
 Double_t uncorrFrac,Double_t scale) {
	TSysLimitChannelError error,error2;
	TObject *exists=fSignalSys.FindObject(name);
	if(exists) return kErrorName;
	// create new arrays and add them to the lists of errors
	TVectorD *signalVec=new TVectorD();
	TVectorD *bgrVec=new TVectorD();
	fSignalSys.Add(new TObjString(name),signalVec);
	fBgrSys.Add(new TObjString(name),bgrVec);
	// unpack histograms
	error=UnpackHistogram(deltaSignal,signalVec,0);
	error2=UnpackHistogram(deltaBackground,bgrVec,0);
	if((error == kErrorNone)&&(error2 != kErrorNone)) error=error2;
	// loop over arrays, apply scale, subtract correlated error,
	// duplicate to down array
	Double_t fcorr;
	if(uncorrFrac<0.0) {
		uncorrFrac=0.0;
		fcorr=1.0;
	} else if(uncorrFrac>=1.0) {
		uncorrFrac=1.0;
		fcorr=0.0;
	} else {
		fcorr=TMath::Sqrt(1.-uncorrFrac*uncorrFrac);
	}
	Double_t e;
	for(Int_t i=0;i<signalVec->GetNoElements();i++) {

		e=(*signalVec)[i]*scale;
		fSignalError[i] = hypot( fSignalError[i],e*uncorrFrac);
		(*signalVec)[i] = e*fcorr;

		e=(*bgrVec)[i] * scale;
		fBgrError[i] = hypot(fBgrError[i],e*uncorrFrac);
		(*bgrVec)[i] = e*fcorr;
	}
	return kErrorNone;
}

TSysLimitChannel::TSysLimitChannelError TSysLimitChannel::AddSysRelative
(TH1 const *relSignal,TH1 const *relBackground,char const *name,
 Double_t uncorrFrac,Double_t scale) {
	TSysLimitChannelError error,error2;
	TObject *exists=fSignalSys.FindObject(name);
	if(exists) return kErrorName;
	// create new arrays and add them to the lists of errors
	TVectorD *signalVec=new TVectorD();
	TVectorD *bgrVec=new TVectorD();
	fSignalSys.Add(new TObjString(name),signalVec);
	fBgrSys.Add(new TObjString(name),bgrVec);
	// unpack histograms
	error=UnpackHistogram(relSignal,signalVec,0);
	error2=UnpackHistogram(relBackground,bgrVec,0);
	if((error == kErrorNone)&&(error2 != kErrorNone)) error=error2;
	// loop over arrays, apply scale, convert to absolute,
	//  subtract correlated error, duplicate to down array
	Double_t fcorr;
	if(uncorrFrac<0.0) {
		uncorrFrac=0.0;
		fcorr=1.0;
	} else if(uncorrFrac>=1.0) {
		uncorrFrac=1.0;
		fcorr=0.0;
	} else {
		fcorr=TMath::Sqrt(1.-uncorrFrac*uncorrFrac);
	}
	Double_t e;
	for(Int_t i=0;i<signalVec->GetNoElements();i++) {

		e=(*signalVec)[i]*scale*fSignal[i];
		fSignalError[i] = hypot( fSignalError[i],e*uncorrFrac);
		(*signalVec)[i] = e*fcorr;

		e=(*bgrVec)[i] * scale * fBgr[i];
		fBgrError[i] = hypot(fBgrError[i],e*uncorrFrac);
		(*bgrVec)[i] = e*fcorr;
#ifdef DEBUG
		std::cout<<"TSysLimitChannel::AddSysRelative: fSignalError[" << i << "]=" <<fSignalError[i]<<", fBgrError[" << i << "]=" <<fBgrError[i]<<std::endl;
		std::cout<<"TSysLimitChannel::AddSysRelative: (*signalVec)[" << i << "]=" <<(*signalVec)[i]<<", (*bgrVec)[" << i << "]=" <<(*bgrVec)[i]<<std::endl;
#endif

	}
	return kErrorNone;
}

void TSysLimitChannel::AddSysNames(THashTable *table) const {
	TMapIter i(&fSignalSys);
	TObjString const *key;
	for(key=(TObjString const *)i.Next();key;key=(TObjString const *)i.Next()) {
		if(!table->FindObject(key->GetString())) {
			table->Add(key->Clone());
#ifdef DEBUG
			std::cout<<"TSysLimitChannel::AddSysNames adding "
				<<key->GetString()<<"\n";
#endif
		} else {
#ifdef DEBUG
			std::cout<<"TSysLimitChannel::AddSysNames name "
				<<key->GetString()<<" already exists\n";
#endif
		}
	}
}

TVectorD const *TSysLimitChannel::GetBgrSys(char const *name) const {
	TVectorD const *r=0;
	TPair const *p=(TPair const *)fBgrSys.FindObject(name);
	if(p) 
		r = (TVectorD const *)p->Value();
	return r;
}

TVectorD const *TSysLimitChannel::GetSignalSys(char const *name) const {
	TVectorD const *r=0;
	TPair const *p=(TPair const *)fSignalSys.FindObject(name);
	if(p) 
		r = (TVectorD const *)p->Value();
	return r;
}
