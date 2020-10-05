#ifndef ROOT_TSysLimitChannel
#define ROOT_TSysLimitChannel

#include <TObject.h> 
#include <TVectorD.h>
#include <TMap.h>

class TH1;
class TObjError;
class THashList;
class TRandom;

class TSysLimitChannel : public TObject {
	public:
		TSysLimitChannel(Bool_t includeOverflowBins=kFALSE);
		virtual ~TSysLimitChannel(void);

		enum TSysLimitChannelError {
			kErrorNone=0,
			kErrorBinning=1, // inconsistent histogram binning
			kErrorContent=2, // invalid histogram content (e.g. bgr<0)
			kErrorName=3     // duplicate error name
		};


		// define measured data
		//   kDataErrorTypePoisson:
		//       histogram errors are ignored, data points must be integer
		//       Use this if the data are plain event counts
		//   kDataErrorTypeAbsolute:
		//       histogram errors are taken as they are
		//   kDataErrorTypeRelative:
		//       when doing toy experiments, they fluctuate
		//       around the expected value with sigma = e* toy/data
		//   kDataErrorTypeMeasured
		//       when doing toy experiments, they fluctuate
		//       around the expected value with sigma = e* sqrt(toy/data)
		//       Use this if the data points are cross sections
		//       with "statistical uncertainties" derived from sqrt(Ndata)
		enum TSysLimitChannelDataErrorType {
			kDataErrorTypePoisson=0, // poisson errors, data points are integers
			kDataErrorTypeAbsolute=1, // Gaussian errors, e>0 required
			kDataErrorTypeRelative=2, // Relative errors, e>0 and |d|>0 required
			kDataErrorTypeMeasured=3, // measured errors, e>0 and d>0 required
		};
		


		/*********************************************************************r
		 * rContent
		 * @Name: SetData    --- get data and error from a histogram, and check whether the data are correct
		 *
		 * @Param: data            --- data in the histogram
		 * @Param: dataErrorType   --- which error type of the data
		 *
		 * @Returns:               --- whether wrong for format or content
		 **********************************************************************/
		TSysLimitChannelError SetData(TH1 const *data, TSysLimitChannelDataErrorType dataErrorType=	kDataErrorTypePoisson);



		/**********************************************************************
		 * @Name: SetPrediction ---define prediction for signal and background, check sig and bkg format are the same or not
		 *
		 * @Param: signal
		 * @Param: background
		 * @Param: useErrors    --- if true, the histogram errors are treated as uncorrelated systematic errors
		 *
		 * @Returns: 
		 **********************************************************************/
		TSysLimitChannelError SetPrediction(TH1 const *signal,TH1 const *background, Bool_t useErrors=kTRUE);



		// add a systematic error. The histograms contain the new
		// signal and bgr prediction obtained when varying the paremeter by
		//   +/- 1 sigma
		// uncorrFrac: define which fraction of the error is uncorrelated between bins
		// scale: global scale factor applied to the observed shifts
		TSysLimitChannelError AddSysUpDown
			(TH1 const *signalUp,TH1 const *signalDown,
			 TH1 const *backgroundUp,TH1 const *backgroundDown,char const *name,
			 Double_t uncorrFrac=0.0,Double_t scale=1.0);




		// add a systematic error
		// the histograms contain absolute offsets to be applied for a 1 sigma
		// shift
		// uncorrFrac: define which fraction of the error is uncorrelated bins
		// scale: global scale factor applied to the errors
		TSysLimitChannelError AddSysAbsolute
			(TH1 const *deltaSignal,TH1 const *deltaBackground,char const *name,
			 Double_t uncorrFrac=0.0,Double_t scale=1.0);




		// add a systematic error
		// the histograms contain relative shifts to be applied for a 1 sigma
		// variation
		// uncorrFrac: define which fraction of the error is uncorrelated bins
		// scale: global scale factor applied to the errors
		TSysLimitChannelError AddSysRelative
			(TH1 const *relSignal,TH1 const *relBackground,char const *name,
			 Double_t uncorrFrac=0.0,Double_t scale=1.0);



		inline Int_t GetNBin(void) const { 
			return fData.GetNoElements(); 
		}

		inline Double_t GetData(int ibin) const { 
			return fData[ibin]; 
		}

		inline TSysLimitChannelDataErrorType GetDataErrorType(void) const {
			return fDataErrorType;
		}

		Double_t GetDataError(int ibin) const { 
			return (*fDataError)[ibin]; 
		}

		inline Double_t GetSignal(int ibin) const { 
			return fSignal[ibin]; 
		}

		inline Double_t GetBgr(int ibin) const { 
			return fBgr[ibin]; 
		}

		inline Double_t GetSignalUncErr(int ibin) const {
			return fSignalError[ibin]; 
		}

		inline Double_t GetBgrUncErr(int ibin) const { 
			return fBgrError[ibin]; 
		}



		void AddSysNames(THashTable *table) const;

		TVectorD const *GetBgrSys(char const *name) const;

		TVectorD const *GetSignalSys(char const *name) const;

		/**********************************************************************
		 * @Name: ToHistogram  put data into a histogram
		 *
		 * @Param: offset    -- from which bin begin to fill data
		 * @Param: content   -- central value
		 * @Param: error     -- error
		 *
		 * @Returns:         -- the histogram
		 **********************************************************************/
		TH1 *ToHistogram(Int_t offset,TVectorD const *content,
				TVectorD const *error) const;
	protected:
		Bool_t fIncludeOverflowBins;
		TH1 const *fTemplate;
		TVectorD fData;
		TVectorD *fDataError;
		TSysLimitChannelDataErrorType fDataErrorType;
		TVectorD fBgr,fBgrError;
		TVectorD fSignal,fSignalError;
		TMap fSignalSys,fBgrSys;

		/**********************************************************************
		 * @Name: UnpackHistogram   get data from a Histogram
		 *
		 * @Param: h  -- input histogram
		 * @Param: c  -- output central value
		 * @Param: e  -- output error
		 *
		 * @Returns: whether succes 
		 **********************************************************************/
		TSysLimitChannelError UnpackHistogram(const TH1 *h,TVectorD *c,TVectorD *e);

		//    ClassDef(TSysLimitChannel, 0) //Limit calculation input for one channel
};

#endif
