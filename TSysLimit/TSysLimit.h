#ifndef ROOT_TSysLimit
#define ROOT_TSysLimit

#include <TObject.h>
#include <TVectorD.h>
#include <TMatrixD.h>
#include <TObjArray.h>
#include <THashTable.h>
#include <TArrayI.h>
#include "Lib/MessageFormat.h" 

class TSysLimitChannel;
class TSysLimitResult;
class TRandom;
class TH1;

class TSysLimit : public TObject {
	public:
		TSysLimit(Int_t printLevel=1);
		virtual ~TSysLimit(void);
		void SetRandom(TRandom *random);
		void SetChannelOwner(bool isOwner);
		Int_t AddChannel(TSysLimitChannel *channel);
		inline Double_t GetSignalScale(void) const { return fSignalScale; }
		void SetFakeData(Bool_t fakeData=kTRUE) { fUseFakeData=fakeData; }
		void GenerateFakeData(void) { fGenerateFakeData=kTRUE; }
		void CalculateCL(Double_t signalScale=1.0,
				Int_t nTotal=50000,Int_t nSysPrescale=10);
		// method number for P.Bock method not optimized for
		// systematic errors: S/(S+2*B)
		inline Int_t GetIndexSoverS2B(void) const { return fMethodSoverSB; }
		// method number for T.Junk method not optimized for
		// systematic errors: Log((S+B)/B)
		inline Int_t GetIndexLogSB(void) const { return fMethodLogSB; }
		// method number for T.Junk method with sys error variation of weights
		// systematic errors: Log((S+B)/B)
		inline Int_t GetIndexLogSBsys(void) const { return fMethodLogSBsys; }
		// method number for P.Bock method k1=k2=1:  S/(S+2*B)+sys
		inline Int_t GetIndexPBock(void) const { return fMethodPBock; }
		// method number for summing -log(likelihood)
		inline Int_t GetIndexLogL(void) const { return fMethodLogL; }
		// total number of methods
		inline Int_t GetNMethod(void) const { return fResults.GetEntries(); }
		// get weight distributions to histogram
		void GetTestStatHistograms(Int_t iMethod,
				TH1 *bLtData,TH1 *bGtData,
				TH1 *sbLtData,TH1 *sbGtData,
				TH1 *bLtToy,TH1 *bGtToy,
				TH1 *sbLtToy,TH1 *sbGtToy,
				Double_t powerConstraint=0.0);

		// get bin weights for a given method/channel as a histogram
		TH1 *GetWeightHistogram(char const *name,Int_t iMethod,Int_t iChannel) const;

		// get result of the limit calculation
		TSysLimitResult const *GetResult(Int_t iMethod);
		inline TSysLimitResult const *GetDefaultResult(void) {
			return GetResult(GetIndexPBock());
		}

		inline void Print(const TSysLimitResult* res) {
			return Print(res,NULL);
		};
		void Print(const TSysLimitResult*, FILE*);
	protected:
		// for adding a new method of limit calculation
		// returns index where to find this new method
		Int_t AddMethod(TSysLimitResult *method);

		TRandom *GetRandom(void);

		void ClearResults(Int_t nTotal);
		void RandomSysShifts(void);
		void RandomExperiment(const TVectorD &src,TVectorD &dest);

		Double_t fSignalScale;

		TRandom *fRnd,*fOwnedRnd;;

		TObjArray fChannels;
		TObjArray fResults;

		TArrayI fUseBin;
		TVectorD fData,fDataErrorAbs,fDataErrorRel,fDataErrorSqrt;

		TVectorD fB,fSB;
		TMatrixD fErrB,fErrSB;

		TVectorD fBSys,fSBSys;

		TVectorD fToyB,fToySB;

		THashTable fSysErrors;

		Int_t fMethodSoverSB,fMethodLogSB,fMethodLogSBsys,fMethodPBock,fMethodLogL;
		Int_t fVerbose;

		Bool_t fUseFakeData;
		Bool_t fGenerateFakeData;

		//    ClassDef(TSysLimit, 0) // Confidence level calculation
};

#endif
