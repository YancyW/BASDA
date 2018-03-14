# Usage

 ./Analyse_Root path.dat

## input 

## output

## setting

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


