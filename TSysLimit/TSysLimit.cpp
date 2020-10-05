#include <iostream>
#include <cmath>
#include <TRandom3.h>
#include <TObjString.h>
#include <TMath.h>

#include "TSysLimit.h"
#include "TSysLimitChannel.h"
#include "TSysLimitResultPBock.h"
#include "TSysLimitResultLogL.h"
#include "TSysLimitResult.h"

#include <TObjArray.h>

// This option enables the usage of bins with zero B or S+B
// if they have non-zero systematic uncertainties
// !!! use with care. It may slow down the calculation a lot !!!
//   #define INCLUDE_ZERO_BIN_WITH_SYS

//#define DEBUG

//ClassImp(TSysLimit)

using namespace std;

TSysLimit::TSysLimit(Int_t printLevel) {
	fResults.SetOwner(kTRUE);
	fSysErrors.SetOwner(kTRUE);
	fMethodSoverSB=AddMethod(new TSysLimitResultPBock(1.,1.,kFALSE));
	fMethodLogSB=AddMethod(new TSysLimitResult());
	fMethodLogL=AddMethod(new TSysLimitResultLogL());
	fMethodPBock=AddMethod(new TSysLimitResultPBock(1.,1.,kTRUE));
	fRnd=0;
	fOwnedRnd=0;
	fSignalScale=1.0;
	fVerbose=printLevel;
	//fVerbose=2;
	cout << "TSysLimit::TSysLimit: fVerbose = " << fVerbose << endl;
	fGenerateFakeData=kTRUE;
	fUseFakeData=kFALSE;
}

TSysLimit::~TSysLimit(void) {
	if(fOwnedRnd) delete fOwnedRnd;
}

void TSysLimit::SetChannelOwner(bool isOwner) {
	fChannels.SetOwner(isOwner);
}

Int_t TSysLimit::AddChannel(TSysLimitChannel *channel) {
	fChannels.AddLast(channel);
	return fChannels.GetEntries()-1;
}
Int_t TSysLimit::AddMethod(TSysLimitResult *method) {
	fResults.AddLast(method);
	return fResults.GetEntries()-1;
}

TSysLimitResult const *TSysLimit::GetResult(Int_t method) {
	return (TSysLimitResult *)fResults[method];
}

void TSysLimit::GetTestStatHistograms(Int_t iMethod,
		TH1 *bLtData,TH1 *bGtData,
		TH1 *sbLtData,TH1 *sbGtData,
		TH1 *bLtToy,TH1 *bGtToy,
		TH1 *sbLtToy,TH1 *sbGtToy,
		Double_t powerConstraint) {
	TSysLimitResult *method=(TSysLimitResult *)fResults[iMethod];
	method->GetTestStatHistograms(bLtData,bGtData,
			sbLtData,sbGtData,
			bLtToy,bGtToy,
			sbLtToy,sbGtToy,powerConstraint);
}

void TSysLimit::ClearResults(Int_t nTotal) {
	if(nTotal!=fResults.GetEntries()){
		ShowMessage(2,"in TSysLimit::ClearResults: nTotal != fResults.GetEntries().");
	}
	for(Int_t iMethod=0;iMethod<fResults.GetEntries();iMethod++) {
		TSysLimitResult *method=(TSysLimitResult *)fResults[iMethod];
		method->Initialize(fSignalScale,fB,fSB,fErrB,fErrSB);
	}   
}

TH1* TSysLimit::GetWeightHistogram(char const *name,
		Int_t iMethod, Int_t iChannel) const {
	TH1 *r=0;
	TSysLimitResult *method=(TSysLimitResult *)fResults[iMethod];
	//TSysLimitChannel const *channel=(TSysLimitChannel *)fChannels[iChannel];
	Int_t nBin=0;
	for(Int_t chn=0;chn<fChannels.GetEntries();chn++) {
		TSysLimitChannel const *channel=(TSysLimitChannel *)fChannels[chn];
		if(chn==iChannel) {         
			r=channel->ToHistogram(nBin,method->GetWeights(),0);
			r->SetName(name);
			break;
		}
		nBin += channel->GetNBin();
	}
	return r;
}

void TSysLimit::CalculateCL(Double_t signalScale,
		Int_t nTotal,Int_t nSysPrescale) {
	fSignalScale=signalScale;

	// count total number of bins, set up vectors fSBnoSys, fBnoSys, fData
	int nBin=0;
	for(Int_t chn=0;chn<fChannels.GetEntries();chn++) {
		TSysLimitChannel const *channel=(TSysLimitChannel *)fChannels[chn];
		nBin += channel->GetNBin();
		if (fVerbose>1) cout << "TSysLimit::CalculateCL: channel number " << chn 
			<< " has " << channel->GetNBin() << " bins" << endl;
	}
	fSB.ResizeTo(nBin);
	fB.ResizeTo(nBin);
	fData.ResizeTo(nBin);
	fDataErrorAbs.ResizeTo(nBin);
	fDataErrorRel.ResizeTo(nBin);
	fDataErrorSqrt.ResizeTo(nBin);
	fUseBin.Set(nBin);
	fErrB.Clear();
	fErrSB.Clear();
	fErrB.ResizeTo(nBin,nBin);
	fErrSB.ResizeTo(nBin,nBin);

	nBin=0;
	for(Int_t chn=0;chn<fChannels.GetEntries();chn++) {
		TSysLimitChannel const *channel=(TSysLimitChannel *)fChannels[chn];
		int nBinChan=channel->GetNBin();
		for(Int_t iBin=0;iBin<nBinChan;iBin++) {
			Double_t data=channel->GetData(iBin);
			if(!fUseFakeData) fData[nBin]=data;
			// get data errors
			fDataErrorAbs[nBin]=-1.;
			fDataErrorRel[nBin]=-1.;
			fDataErrorSqrt[nBin]=-1.;
			switch(channel->GetDataErrorType()) {
				case TSysLimitChannel::kDataErrorTypeAbsolute:
					fDataErrorAbs[nBin]=channel->GetDataError(iBin);
					break;
				case TSysLimitChannel::kDataErrorTypeRelative:
					fDataErrorRel[nBin]=channel->GetDataError(iBin)/data;
					break;
				case TSysLimitChannel::kDataErrorTypeMeasured:
					fDataErrorSqrt[nBin]=channel->GetDataError(iBin)
						/TMath::Sqrt(data);
			}
			fB[nBin]=channel->GetBgr(iBin);
			fSB[nBin]=fSignalScale*channel->GetSignal(iBin)+fB[nBin];
			// use bin if it contains positive b and positive s+b
			fUseBin[nBin]=0;
			if(fB[nBin]>0.0) fUseBin[nBin] |= 0x1;  // B>0
			if(fSB[nBin]>0.0) fUseBin[nBin] |= 0x2;  // S+B>0
			Double_t e=channel->GetBgrUncErr(iBin);
			if(e>0.0) {
#ifdef INCLUDE_ZERO_BIN_WITH_SYS
				fUseBin[nBin] |= 0x3; // B and S+B can fluctuate up
#endif
				fErrB(nBin,nBin) += e*e;
				fErrSB(nBin,nBin) += e*e;            
			}
			e=channel->GetSignalUncErr(iBin)*fSignalScale;
			if(e>0.0) {
#ifdef INCLUDE_ZERO_BIN_WITH_SYS
				fUseBin[nBin] |= 0x2; // S+B can fluctuate>0
#endif
				fErrSB(nBin,nBin) += e*e;
			}
			nBin++;
		}
	}

	// initialize list of systematic errors
    	if (fVerbose>1) cout << "TSysLimit::CalculateCL: initialize errors" << endl;
	fSysErrors.Clear();
	for(Int_t chn=0;chn<fChannels.GetEntries();chn++) {
		TSysLimitChannel const *channel=(TSysLimitChannel *)fChannels[chn];
		channel->AddSysNames(&fSysErrors);
	}
	// loop over correlated systematic errors
	THashTableIter isys(&fSysErrors);
	TObjString *name;
	for(name=(TObjString *)isys.Next();name;
			name=(TObjString *)isys.Next()) {
		TMatrixD deltaB(nBin,1),deltaSB(nBin,1);
		nBin=0;
		for(Int_t chn=0;chn<fChannels.GetEntries();chn++) {
			TSysLimitChannel const *channel=
				((TSysLimitChannel *)fChannels[chn]);
			TVectorD const *errB=channel->GetBgrSys(name->GetString());
			TVectorD const *errS=channel->GetSignalSys(name->GetString());
			int nBinChan=channel->GetNBin();
			if(errB) {
				for(Int_t iBin=0;iBin<nBinChan;iBin++) {
					if((*errB)[iBin] !=0.0) {
#ifdef INCLUDE_ZERO_BIN_WITH_SYS
						fUseBin[nBin+iBin] |= 0x3; // B and S_B can fluctuate
#endif
						deltaB(nBin+iBin,0)=(*errB)[iBin];
						deltaSB(nBin+iBin,0)=(*errB)[iBin];
					}
				}
			}
			if(errS) {
				for(Int_t iBin=0;iBin<nBinChan;iBin++) {
					if((*errS)[iBin]*fSignalScale !=0.0) {
#ifdef INCLUDE_ZERO_BIN_WITH_SYS
						fUseBin[nBin+iBin] |= 0x2; // S+B can fluctuate
#endif
						deltaSB(nBin+iBin,0) += (*errS)[iBin]*fSignalScale;
					}
				}
			}
			nBin += nBinChan;
		}
		fErrB += TMatrixD(deltaB,TMatrixD::kMultTranspose,deltaB);
		fErrSB += TMatrixD(deltaSB,TMatrixD::kMultTranspose,deltaSB);
	}
	// flag bins which can not have both S and S+B as unusable
	int spb0=0;
	int sb0=0;
	int b0=0;
	for(Int_t iBin=0;iBin<nBin;iBin++) {
		if(fUseBin[iBin]!=0x3) {
			if(fVerbose) {
				cout<<"TSysLimit::CalculateCL bin "<<iBin;
				if(fUseBin[iBin]==1) {
					cout<<" has S+B=0\n";
					spb0++;
				} else if(fUseBin[iBin]==2) {
					cout<<" has B=0\n";
					b0++;
				} else {
					cout<<" has S=0 and B=0\n";
					sb0++;
				}
			} else {
				if(fUseBin[iBin]==1) spb0++;
				else if(fUseBin[iBin]==2) b0++; 
				else sb0++; 
			}
			fUseBin[iBin]=0;
		}
	}
	if (fVerbose>0) {
		cout<<"\n\n************************************ \n"
			<<TString::Format(" Total number of bins:        %5d\n",nBin)
			<<TString::Format(" Number of bins with S+B=0:   %5d\n",spb0)
			<<TString::Format(" Number of bins with   B=0:   %5d\n",b0)
			<<TString::Format(" Number of bins with S=S+B=0: %5d\n",sb0)
			<<"**************************************** \n";
	}

	// initialize results
	ClearResults(nTotal);
	if(fVerbose) cout<<"TSysLimit: calculate confidence levels, scale="
		<<fSignalScale<<"\n";


	if(fGenerateFakeData && fUseFakeData) {
		if(fVerbose) cout<<"TSysLimit: generate new fake data\n";
		RandomSysShifts();
		RandomExperiment(fBSys,fData);
		fGenerateFakeData=kFALSE;
	} else if(fUseFakeData) {
		// do nothing, data was already set
	}
	// toy experiments (1)
	// create a set of background-only toy experiments
	// these are used for the power constraint
	// and for the expected confidence level
	for(Int_t iMethod=0;iMethod<fResults.GetEntries();iMethod++) {
		TSysLimitResult *method=(TSysLimitResult *)fResults[iMethod];
		method->SetDataExperiment(fData);
	}
	for(Int_t iexp=0;iexp<nTotal;iexp++) {
		if((iexp%nSysPrescale)==0) {
			RandomSysShifts();
		}
		RandomExperiment(fBSys,fToyB);
		for(Int_t iMethod=0;iMethod<fResults.GetEntries();iMethod++) {
			TSysLimitResult *method=(TSysLimitResult *)fResults[iMethod];
			method->AddBExperiment(fToyB);
		}
	}    
	// toy experiments (2)
	// create a set of signal+background toy experiments
	// these are used to test the signal
	for(Int_t iexp=0;iexp<nTotal;iexp++) {
		if(fVerbose>1) if(iexp &&((iexp %1000)==0 || iexp==1)) cout<<iexp<<"\n";
		if((iexp%nSysPrescale)==0) {
			RandomSysShifts();
		}
		RandomExperiment(fSBSys,fToySB);
		for(Int_t iMethod=0;iMethod<fResults.GetEntries();iMethod++) {
			TSysLimitResult *method=(TSysLimitResult *)fResults[iMethod];
			method->AddSBExperiment(fToySB);
		}
	}
	for(Int_t iMethod=0;iMethod<fResults.GetEntries();iMethod++) {
		TSysLimitResult *method=(TSysLimitResult *)fResults[iMethod];
		cout<<"Finalize method "<<iMethod<<"\n";
		method->Finalize();
	}
}

void TSysLimit::SetRandom(TRandom *random) {
	fRnd=random;
}

TRandom *TSysLimit::GetRandom(void) {
	if(!fRnd) {
		if(!fOwnedRnd) fOwnedRnd=new TRandom3();
		fRnd=fOwnedRnd;
	}
	return fRnd;
}

void TSysLimit::RandomSysShifts(void) {
	static Bool_t print=kTRUE;
	TRandom *rnd=GetRandom();
	Int_t invalidBins;
	int ntries = 0;
#ifdef DEBUG
	Int_t nBin=0;
	for(Int_t chn=0;chn<fChannels.GetEntries();chn++) {
		TSysLimitChannel const *channel=
			((TSysLimitChannel *)fChannels[chn]);
		int nBinChan=channel->GetNBin();
		for(Int_t iBin=0;iBin<nBinChan;iBin++) {
			if(!fUseBin[nBin+iBin]) continue;
			cout<<chn<<" "<<iBin<<"/"<<nBinChan
				<<" B="<<fB[nBin+iBin]
				<<" SB="<<fSB[nBin+iBin]
				<<" (+/-mcstat,dB="<<channel->GetBgrUncErr(iBin)
				<<",dS="<<channel->GetSignalUncErr(iBin)*fSignalScale<<")";
			THashTableIter isys(&fSysErrors);
			TObjString *name;
			for(name=(TObjString *)isys.Next();name;
					name=(TObjString *)isys.Next()) {
				cout<<" (+/-"<<name->GetString();
				TVectorD const *errB=channel->GetBgrSys(name->GetString());
				TVectorD const *errS=channel->GetSignalSys(name->GetString());
				if(errB) {
					cout<<",dB="<<(*errB)[iBin];
				}
				if(errS) {
					cout<<",dS="<<fSignalScale*(*errS)[iBin];
				}
				cout<<")";
			}
			cout<<"\n";
		}
		nBin+=nBinChan;
	}
	//exit(0);
#endif
	do {
		// initialize bins
		fBSys.ResizeTo(fB);
		fSBSys.ResizeTo(fSB);
		fBSys=fB;
		fSBSys=fSB;
		// add uncorrelated systematics
		Int_t nBin=0;
		for(Int_t chn=0;chn<fChannels.GetEntries();chn++) {
			TSysLimitChannel const *channel=
				((TSysLimitChannel *)fChannels[chn]);
			int nBinChan=channel->GetNBin();
			Double_t es,eb;
			for(Int_t iBin=0;iBin<nBinChan;iBin++) {
				es=channel->GetSignalUncErr(iBin)*fSignalScale;
				eb=channel->GetBgrUncErr(iBin);
				if(es>0.0) es *= rnd->Gaus();
				if(eb>0.0) eb *= rnd->Gaus();
				fSBSys[nBin] += es+eb;
				fBSys[nBin] += eb;
				if (fVerbose>1 ) {
					cout << "TSysLimit::RandomSysShifts: iBin = " << iBin 
						<< ", fSBSys[nBin] = " << fSBSys[nBin] << ", fBSys[nBin] = " << fBSys[nBin] << endl; 
				}
				nBin++;
			}
		}
		// add correlated systematics
		THashTableIter isys(&fSysErrors);
		TObjString *name;
		for(name=(TObjString *)isys.Next();name;
				name=(TObjString *)isys.Next()) {
			if(print) {
				cout<<"TSysLimit::RandomSysShifts source "
					<<name->GetString()<<"\n";
			}
			Double_t scale= rnd->Gaus();
			Int_t nBin=0;
			for(Int_t chn=0;chn<fChannels.GetEntries();chn++) {
				TSysLimitChannel const *channel=
					((TSysLimitChannel *)fChannels[chn]);
				TVectorD const *errB=channel->GetBgrSys(name->GetString());
				TVectorD const *errS=channel->GetSignalSys(name->GetString());
				Double_t e;
				int nBinChan=channel->GetNBin();
				if(print) {
					cout << "TSysLimit::RandomSysShifts: channel >>" << channel->GetName() 
						<< "<< has " << nBinChan << " bins and scale = " << scale << endl;
				}
				if(errB) {
					for(Int_t iBin=0;iBin<nBinChan;iBin++) {
						if(print) {
							cout << "TSysLimit::RandomSysShifts: (*errB)[" << iBin << "] = " << (*errB)[iBin]<< endl;
						}
						e = (*errB)[iBin]*scale;
						fSBSys[nBin+iBin] += e;
						fBSys[nBin+iBin] += e;
						if(print) {
							cout << "TSysLimit::RandomSysShifts: fBSys[" << nBin+iBin << "] = " << fBSys[nBin+iBin]<< endl;
						}
					}
				}
				if(errS) {
					for(Int_t iBin=0;iBin<nBinChan;iBin++) {
						e = (*errS)[iBin]*fSignalScale*scale;
						fSBSys[nBin+iBin] += e;
					}
				}
				nBin += nBinChan;
			}
		}
		// check whether any of the bins is zero or negative
		// -> can not do Poisson fluctuations
		invalidBins=0;
		Int_t usedBins=0;
		for(Int_t iBin=0;iBin<fBSys.GetNoElements();iBin++) {
			if(!fUseBin[iBin]) {
				fBSys[iBin]=0.0;
				fSBSys[iBin]=0.0;
				continue;
			}
			usedBins++;
			if((!(fBSys[iBin]>=0.0))||(!(fSBSys[iBin]>0.0))) invalidBins++;
		}
		/* if(invalidBins>0) {
		   cout<<invalidBins<<" "<<usedBins<<" "<<fB.GetNoElements()<<"\n";
		   for(Int_t i=0;i<fB.GetNoElements();i++) {
		   cout<<i<<" "<<useBin[i]<<" "<<fB[i]<<" "<<fSB[i]<<"\n";
		   }
		   exit(0);
		   } */
		if(print) print=kFALSE;
		ntries++;
		if (fVerbose>1 && (ntries<10 || ntries%10000 == 0)) {
			cout << "TSysLimit::RandomSysShifts: ntries = " << ntries 
				<< ", usedBins = " << usedBins << endl; 
		}
	} while(invalidBins>0);
	if(fVerbose) {
		cout << "TSysLimit::RandomSysShifts: final ntries = " << ntries << endl;
	}
}

void TSysLimit::RandomExperiment(const TVectorD &src,TVectorD &dest) {
	TRandom *rnd=GetRandom();
	dest.ResizeTo(src);
	for(Int_t iBin=0;iBin<src.GetNoElements();iBin++) {
		Double_t error=-1.;
		if(fDataErrorAbs[iBin]>0.) {
			error=fDataErrorAbs[iBin];
		}
		if(fDataErrorRel[iBin]>0.) {
			if(error<=0.) error=fDataErrorRel[iBin]*src[iBin];
			else error=hypot(error,fDataErrorRel[iBin]*src[iBin]);
		}
		if(fDataErrorSqrt[iBin]>0.) {
			if(error<=0.) error=fDataErrorSqrt[iBin]*TMath::Sqrt(src[iBin]);
			else error=TMath::Sqrt(error*error+fDataErrorSqrt[iBin]*
					fDataErrorSqrt[iBin]*src[iBin]);
		}
		if(error<0.0) {
			if((fUseBin[iBin]==0)||(src[iBin]<=0.0)) {
				dest[iBin]=0.0;
			} else {
				dest[iBin]=rnd->Poisson(src[iBin]);
			}
		} else {
			dest[iBin]=rnd->Gaus(src[iBin],error);
		}
	}
}


void TSysLimit::Print(const TSysLimitResult *res, FILE *file) {
	if (!file) {
		for (int iBin=0; iBin<fData.GetNoElements(); iBin++) {		
			printf(".  %4d  %3.0f  %7.3f  %7.3f  %g", iBin, fData[iBin], fB[iBin], fSB[iBin], res->GetWeight(iBin));
			if (!fUseBin[iBin]) printf("   X\n");
			else printf("\n");
		}
	}
	else {
		for (int iBin=0; iBin<fData.GetNoElements(); iBin++) {		
			//	fprintf(file,"%4d  %3.0f  %7.3f  %7.3f  %g", iBin, fData[iBin], fB[iBin], fSB[iBin], res->getWeight(iBin));
			fprintf(file,"%4d  %3.0f  %g  %g  %g", iBin, fData[iBin], fB[iBin], fSB[iBin], res->GetWeight(iBin));
			if (!fUseBin[iBin]) fprintf(file,"   X\n");
			else fprintf(file,"\n");
		}
	}
	return;
}
