# Beautiful_And_Simple_Drawing_Atificer (BASDA)

## Introduction:
This package is developed for releasing you from programming and unphysical labor for number statistics. It can add cut and draw figures and give final efficicency cut table and sensitivity plots.
All operation can be done by only change the input config file.

## Pre-Installation
 - c++ >= 11 (default c++14)
 - root6 
 - boost_filesystem 
 - yaml-cpp [download](https://github.com/jbeder/yaml-cpp)

 - For ILC users, you can initialize an ilcsoft environment with gcc≧4.8, root 6, (e.g. ILCSoft-v17-11) and install yaml-cpp by yourself.

## Installation
 - change yaml directory in the makefile
 - make -j8
 - set config files.
 - run code with two methods:
   - ./BASDA 
   - ./BASDA ./control/path.dat

 

## input root file structure
  - root tree 
	  - observable 1
	  - observable 2
      - ...

## Manual
 - The introduction pdf/pptx is in [Introduction](./doc/BASDA_Introduction.pdf).
 - The complete manual is in [USAGE](./doc/USAGE.md).
 - The licence is in [Licence](./doc/LICENCE).
 - Four branches 
	- master: The public code.
    - release: The most stable develop version, prepare to merge into master, but not well tested.
    - develop: With new features, without known bugs.
    - feature: Testing new features.

## change.log
- 2017/7/1 :  v0.01 
    - have basic function for input, output, make_table ...
- 2017/10/1:  v0.02 
    - can do any cuts for given observables with any orders; 
    - draw four kinds of plots (origin, before, after, final) automatically; 
    - complete analyse tools, such as MVA (can be any given observables.), normal cut, final sensitivity calculation ....
- 2017/10/25: v0.03
    - plot for any higgs mass (used for my project, the code also can be used for any other combination!).
    - store histogram to the root file, so ploting will be a little easier, donot need to recalculation when changing the legend of plot format.
- 2018/03/25: v0.04
    - generallize this code with more setting options.
    - save all intermedia data/plots/root files.
    - write introduction for BASDA (pdf/pptx).
- 2018/04/04: v0.05
    - support double and integer input.
- 2018/04/08: v0.06
    - further generallize more setting options.
    - put many setting (e.g. MVA, plot ...) into config file.
    - split more branch for development.
