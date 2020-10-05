#ifndef ROOT_TSysLimitResult
#define ROOT_TSysLimitResult

#include <TObject.h>
#include <TVectorD.h>
#include <TMatrixD.h>
#include <TArrayI.h>
#include <TArrayD.h>
#include <TH2D.h>
#include <cmath>
#include <map>

class TToyDistribution {
	public:
		void Add(Double_t);
		void Finalize(void);
		Double_t GetPValue(Double_t x) const;
		Double_t GetAvgX(void) const;
		Double_t GetAvgXcut(Double_t xmin) const;
		Double_t GetPValueWithcut(Double_t x,Double_t xmin) const;
		// Double_t GetXForPvalueWithcut(Double_t pvalue,Double_t xmin) const;
		Double_t GetRmsX(void) const;
		Double_t GetXForPvalue(Double_t pvalue) const;
		Double_t GetDensity(Double_t x) const;
		void FillHistograms(Double_t x,TH1 *lower,TH1 *higher) const;
	protected:
		std::map<Double_t,Int_t> fXmult;
		std::map<Double_t,Double_t> fXtoP,fPtoX;
};

class TSysLimitResult : public TObject {
	public:
		TSysLimitResult(void);
		virtual ~TSysLimitResult(void);
		void Initialize(Double_t scale,
				TVectorD const &b,TVectorD const &sb,
				TMatrixD const &errB,TMatrixD const &errSB);
		void SetDataExperiment(TVectorD const &bins);
		void AddSBExperiment(TVectorD const &bins);
		void AddBExperiment(TVectorD const &bins);

		inline Double_t GetSignalScale(void) const { return fSignalScale; }

		inline double GetWeight(int bin) const {
			if (bin<fWeight.GetNoElements()) return fWeight[bin];
			else return -1.0;
		}
		inline TVectorD const *GetWeights(void) const { return &fWeight; }

		Double_t GetDataCLs(Double_t powerConstraint=0.0) const;
		Double_t GetDataCLb(Double_t powerConstraint=0.0) const;
		Double_t GetDataCLsb(Double_t powerConstraint=0.0)
			const;
		Double_t GetExpectedCLs(void) const;
		Double_t GetExpectedCLb(void) const;
		Double_t GetExpectedCLsb(void) const;

		void GetTestStatHistograms(TH1 *bLtData,TH1* bGtData,
				TH1 *sbLtData,TH1* sbGtData,
				TH1 *bLtToy,TH1 *bGtToy,
				TH1 *sbLtToy,TH1 *sbGtToy,
				Double_t powerConstraint=0.0);
		void Finalize(void);
	protected:
		virtual Double_t GetX(TVectorD const &exp) const;
		Double_t GetXPowerConstraint(Double_t x,Double_t powerConstraint) const;
		virtual void Initialize(TVectorD const &b,TVectorD const &sb,
				TMatrixD const &errB,TMatrixD const &errS);
		TVectorD fWeight;
		Double_t fSignalScale;
		Double_t fXdata;
		TToyDistribution *fXb,*fXsb;

		//   ClassDef(TSysLimitResult, 0) //Limit calculation results
};

#endif
