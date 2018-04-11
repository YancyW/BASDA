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

## output

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


