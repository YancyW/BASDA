#include <string>
#include <vector>
#include <inttypes.h>
#include "yaml-cpp/yaml.h"
#include <cmath>


#include "TCanvas.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitter.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TH3.h"
#include "THStack.h"
#include "TImage.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TMath.h"
#include "TMatrix.h"
#include "TMatrixT.h"
#include "TMinuit.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TTree.h"
#include <iomanip>
#include <map>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "boost/filesystem.hpp"


#include "Fram/Fsection.h"
#include "Fram/Fram.h"
#include "Lib/MessageFormat.h"
#include "Function/Fvector.h"
#include "Class/DrawClass.h"

#include "BASDA.h"


//using namespace boost::filesystem;
//using namespace std;
//using namespace YAML;


int main(int argc, char*argv[]) {


	CDraw para(argc,argv);

	StartProcess();

	LoadLibrary(para);

	Fram(para);

	EndProcess();
}
