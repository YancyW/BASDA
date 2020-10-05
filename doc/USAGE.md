# Usage

 ./BASDA [path.dat]
 
 - if ./BASDA, it runs with default input config file ./control/path.dat
 - if ./BASDA your_path.dat_file,  it runs with your config file

## input 
 There are five baisc input files
 - path.dat
 - flow.dat
 - Var/Var.dat
 - Cut/Cut.dat
 - BKG__sort.dat
 
 Others are advanced input parameters
 - format setting
   - advanced/plot.dat
 - analysis setting
   - advanced/scenario.dat
   - advanced/MVA.dat
   - advanced/Sensitivity.dat
   - advanced/Signal_Properties_Scan.dat
 - debug
   - advanced/debug.dat
   - advanced/Event.dat

## operation 
   - Pre_Cut 
      -  used when want to add a MVA variables
      -  used when want to combine different polarized file 
      -  used when want to discard some events
   - MVA_training
      - only works after Pre_Cut
   - MVA_attaching
      - only works when have the MVA dataset in MVA folder, (MVA_training will generate this dataset.)
      - a new variable will be attached into rootfile in MVA folder.
   - Direct_Cut 
      -  used when want to add cuts, and already do the pre cuts
   - Direct_Cut_NoMVA
      -  used when don't want to add any MVA variables
      -  used when didn't do pre cuts
      -  input files are more than one for each channels,  first use Analyse_Pre_Cut_Content to combine them into one file, then run with Analyse_Direct_Cut
      -  input file is onle one for each channels,  directly run Analyse_Direct_Cut with original input files
   - Make_Table 
      -  used when have cut data for each channels in data folder 
      -  automatically load this function after any Direct_Cut 
   - Sensitivity 
      -  used when have rootfile "total_bkg" in results folder/CUT/ 
   - Summarize_Plot 
      -  used when have rootfile "total_bkg" in results folder/CUT/ 
      -  need to edit control/advanced/summary.dat to supply correct signal_properties 
   - Complete_Pol 
      -  combine Pre_Cut, MVA_training, MVA_attaching, Direct_Cut 
   - Complete_Run
      - do Complete_Pol for four polarization combinations
   - Complete_Direct_Cut
      - do Direct_Cut for four polarization combinations

## example

## TSysLimit
	- declare a new pointer to the TSysLimitChannel(), init a Channel;
	```
	TSysLimitChannel *channel = new TSysLimitChannel();
	```
	- Set Data
	```
	channel->SetData(bkg_histo);//bkg_histo is the histogram of the background
	```
	  in this function, the histogram is decomposed into central value and error, and they are stored in fData and FDataError,
      
	- init declare a TSysLimit type "limit(0)"
	```
	TSysLimit limit(0);
	```
	- add the channel to limit


