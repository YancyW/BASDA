#include <iostream>
#include "TSysLimit.h"
#include "TSysLimitScan.h"
#include "TSysLimitResult.h"

//#define DEBUG
#define LOGFILE

//ClassImp(TSysLimitScan)

TSysLimitScan::TSysLimitScan(TSysLimit &limit,Int_t scanMax)
	: fSysLimit(limit) {
		fData=-1;
		fExpected=-1;
		fResults.SetOwner();
		fScanMax=scanMax;
#ifdef LOGFILE
		logFile = fopen("_lqlimit.log","w");
		fprintf(logFile,"L(ambda)   CLd CLe   CLdmin CLdmax   CLemin CLemax   Ldmin Ldmax   Lemin Lemax\n");     
#endif
	}

TSysLimitScan::~TSysLimitScan(void) {
#ifdef LOGFILE
	if (logFile) fclose(logFile);
#endif
}


TSysLimitResult const *TSysLimitScan::GetDataLimit(void) const {
	if(fData>=0) return (TSysLimitResult const *)fResults[fData];
	return (NULL);
}

TSysLimitResult const *TSysLimitScan::GetExpectedLimit(void) const {
	if(fExpected>=0) return (TSysLimitResult const *)fResults[fExpected];
	return (NULL);
}

void TSysLimitScan::Print(Int_t verbose) const {
	for(Int_t i=0;i<2;i++) {
		TSysLimitResult const *result=GetDataLimit();
		if(i==0) {
			result=GetDataLimit();
			std::cout<<"data:";
		} else {
			result=GetExpectedLimit();
			std::cout<<"expected:";
		}
		if(result) {
			Double_t cl /* ,dcl */;
			std::cout<<" "<<result->GetSignalScale();
			if(i==0) {
				cl=result->GetDataCLs(/* &dcl */);
			} else {
				cl=result->GetExpectedCLs( /* &dcl */);
			}
			std::cout<<" CLs: "<<cl /* <<" +/- "<<dcl */;
			if(i==0) {
				cl=result->GetDataCLb( /* &dcl */);
			} else {
				cl=result->GetExpectedCLb( /* &dcl */);
			}
			std::cout<<" CLb: "<<cl /* <<" +/- "<<dcl */;
			if(i==0) {
				cl=result->GetDataCLsb( /* &dcl */);
			} else {
				cl=result->GetExpectedCLsb( /* &dcl */);
			}
			std::cout<<" CLsb: "<<cl /* <<" +/- "<<dcl */ <<"\n";;
		} else {
			std::cout<<"[null]\n";
		}
	}
	if(verbose) {
		Double_t cl,dcl;
		std::cout<<"step |   scale  |  CLs(Data)    | CLs(expected) |"
			<<"   CLb(Data)   | CLb(expected) |"
			<<"   CLsb(Data)  | CLsb(expected)\n";
		std::cout<<"=====+==========+===============+===============+"
			<<"===============+===============+"
			<<"===============+===============\n";
		dcl=-0.99;
		for(Int_t i=0;i<fResults.GetEntries();i++) {
			TSysLimitResult const *result=(TSysLimitResult const *)fResults[i];
			std::cout<<TString::Format("%4d | %8.2e",i,result->GetSignalScale());
			cl=result->GetDataCLs( /* &dcl */);
			std::cout<<TString::Format(" | %5.2f +- %4.2f",cl,dcl);
			cl=result->GetExpectedCLs( /* &dcl */);
			std::cout<<TString::Format(" | %5.2f +- %4.2f",cl,dcl);
			cl=result->GetDataCLb( /* &dcl */);
			std::cout<<TString::Format(" | %5.2f +- %4.2f",cl,dcl);
			cl=result->GetExpectedCLb( /* &dcl */);
			std::cout<<TString::Format(" | %5.2f +- %4.2f",cl,dcl);
			cl=result->GetDataCLsb(/* &dcl */);
			std::cout<<TString::Format(" | %5.2f +- %4.2f",cl,dcl);
			cl=result->GetExpectedCLsb( /* &dcl */);
			std::cout<<TString::Format(" | %5.2f +- %4.2f",cl,dcl)<<"\n";
		}
	}
}

Int_t TSysLimitScan::GetCL(Double_t scale,Int_t method,
		Int_t nTotal,Int_t nSysPrescale) {
	fSysLimit.CalculateCL(scale,nTotal,nSysPrescale);
	TSysLimitResult const*result;
	if(method==-1) result=fSysLimit.GetDefaultResult();
	else result=fSysLimit.GetResult(method);
	fResults.AddLast(new TSysLimitResult(*result));
	return fResults.GetEntries()-1;
}

void TSysLimitScan::DoScan(Double_t cl,Double_t startScale,
		Int_t method,Double_t signalScalePrecision,
		EConficenceLevelType cltype,
		Int_t nTotal,Int_t nSysPrescale,
		Bool_t generateFakeData) {
	fResults.Clear();
	fData=-1;
	fExpected=-1;
	Double_t x_min,x_max;
	Double_t x,xmin_d,xmax_d,xmin_e,xmax_e;
	Int_t i,imin_d,imax_d,imin_e,imax_e;
	Double_t clmin_d,clmax_d,clmin_e,clmax_e;
	imin_d=-1;
	imax_d=-1;
	imin_e=-1;
	imax_e=-1;
	clmin_d=-0.1;
	clmax_d= 1.1;
	clmin_e=-0.1;
	clmax_e= 1.1;
	xmin_d=-1.;
	xmax_d=-1.;
	xmin_e=-1.;
	xmax_e=-1.;
	x=startScale;
	x_min=startScale;
	x_max=startScale;
	if(generateFakeData) {
		fSysLimit.GenerateFakeData();
	}
	fSysLimit.SetFakeData(generateFakeData);
	for(Int_t iter=0;iter<fScanMax;iter++) {
		i=GetCL(x,method,nTotal,nSysPrescale);
		TSysLimitResult const *r=GetLimit(i);
		Double_t cl_data,cl_expected /* ,dcl_data,dcl_expected */;
		if(cltype==kConficenceLevelTypeCLS) {
			cl_data=r->GetDataCLs( /* &dcl_data */);
			cl_expected=r->GetExpectedCLs( /*&dcl_expected */);
		} else {
			cl_data=r->GetDataCLsb( /*&dcl_data */);
			cl_expected=r->GetExpectedCLsb(/*&dcl_expected*/);
		}


#ifdef DEBUG
		std::cout<<x<<" D: "<<cl_data<<" E: "<<cl_expected<<"\n";
#endif
		// update lower bound for data
		if((cl_data<cl)&&((cl_data>clmin_d)||(x<xmax_d))) {
			imin_d=i;
			clmin_d=cl_data;
			xmax_d=x;
		}
		// update upper bound for data
		if((cl_data>cl)&&((cl_data<clmax_d)||(x>xmin_d))) {
			imax_d=i;
			clmax_d=cl_data;
			xmin_d=x;
		}
		// update lower bound for expected
		if((cl_expected<cl)&&((cl_expected>clmin_e)||(x<xmax_e))) {
			imin_e=i;
			clmin_e=cl_expected;
			xmax_e=x;
		}
		// update upper bound for expected
		if((cl_expected>cl)&&((cl_expected<clmax_e)||(x>xmin_e))) {
			imax_e=i;
			clmax_e=cl_expected;
			xmin_e=x;
		}
#ifdef DEBUG
		std::cout<<"clD ["<<clmin_d<<","<<clmax_d<<"] clE["<<clmin_e<<","<<clmax_e<<"]\n";
		std::cout<<"xD ["<<xmin_d<<","<<xmax_d<<"] xE["<<xmin_e<<","<<xmax_e<<"]\n";
#endif
		// check whether we have a match within errors
		if(TMath::Abs(cl-cl_data)</* dcl_data */ 0.1*cl) {
#ifdef DEBUG
			std::cout<<"data match within errors\n";
#endif
			fData=i;
		}
		if(TMath::Abs(cl-cl_expected)< /* dcl_expected */ 0.1*cl) {
#ifdef DEBUG
			std::cout<<"expected match within errors\n";
#endif
			fExpected=i;
		}

		// define next search point
		if(((imin_d<0)&&(fData<0))||((imin_e<0)&&(fExpected<0))) {
			// try to get lower bounds
#ifdef DEBUG
			std::cout<<"improve lower bound\n";
#endif
			x_max *=4.0;
			x = x_max;
		} else if(((imax_d<0)&&(fData<0))||((imax_e<0)&&(fExpected<0))) {
			// try to get upper bounds
#ifdef DEBUG
			std::cout<<"improve upper bound\n";
#endif
			x_min /= 4.0;
			x = x_min;
		} else {
			Double_t xnext_data=-1,xnext_expected=-1;
			if((x<xmax_d)&&(x>xmin_d)) {
				if(x*signalScalePrecision>xmax_d-xmin_d) {
#ifdef DEBUG
					std::cout<<"data precision reached\n";
#endif
					fData=i;
				}
			}
			Double_t f=(clmax_d-cl)/(clmax_d-clmin_d);
			if((f<0.05)||(f>0.95)) f=0.5;
			xnext_data=xmax_d*f+xmin_d*(1.-f);
			if((x>xmin_e)&&(x<xmax_e)) {
				if(x*signalScalePrecision>xmax_e-xmin_e) {
#ifdef DEBUG
					std::cout<<"expected precision reached\n";
#endif
					fExpected=i;
				}
			}
			f=(clmax_e-cl)/(clmax_e-clmin_e);
			if((f<0.05)||(f>0.95)) f=0.5;
			xnext_expected=xmax_e*f+xmin_e*(1.-f);
#ifdef DEBUG
			std::cout<<"next: "<<xnext_data<<" "<<xnext_expected<<"\n";
#endif
			if((fData<0)&&(fExpected<0)) {
				if(xmax_d-xmin_d>xmax_e-xmin_e) x=xnext_data;
				else x=xnext_expected;
			} else if(fData<0) {
				x=xnext_data;
			} else {
				x=xnext_expected;
			}
		}
#ifdef LOGFILE
		fprintf(logFile,"%7.5f   %5.3f %5.3f   %5.3f %5.3f   %5.3f %5.3f   % 7.1e % 7.1e   % 7.1e % 7.1e\n", x, cl_data, cl_expected, clmin_d, clmax_d, clmin_e, clmax_e, xmin_d, xmax_d, xmin_e, xmax_e);     
		fflush(logFile);
#endif
		// both limits found -> stop iterating
		if((fData>=0)&&(fExpected>=0)) break;
	}
}

