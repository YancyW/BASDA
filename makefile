TARGET=BASDA

CXX=g++
FLAGS=-std=c++14  -Wextra  -Wall ${shell root-config --cflags}

RootPath=/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-11/root/6.08.00
YAMLPath=/afs/desy.de/user/y/ywang/Software/Lib/yaml-cpp-master/

INCLUDE = -I. -I..  -I$(RootPath)/include  \
		  -I${YAMLPath}/include

LIBS =  -L${YAMLPath} -lyaml-cpp -lboost_filesystem  -lboost_system -lTMVA -lTMVAGui 
ROOTLIBS := $(shell root-config --libs) -lXMLIO

SRCS = \
$(TARGET).cpp \
Class/Path.cpp\
Fram/Fram.cpp Fram/Fsection.cpp \
Function/Fbasic.cpp Function/Fvector.cpp Function/Ffile.cpp Function/FCalc.cpp Function/FString.cpp \
Latex/LTable.cpp Latex/LItem.cpp\
Lib/MessageFormat.cpp Lib/PlotSetting.cpp Lib/Record.cpp Lib/YAML_Assistant.cpp\
RWpara/RWFile.cpp RWpara/RWFlow.cpp RWpara/RWPath.cpp RWpara/RWDebug.cpp RWpara/RWDraw.cpp RWpara/RWbasic.cpp RWpara/RWEvent.cpp RWpara/RWVar.cpp\
RWpara/RWSensitivity.cpp RWpara/RWCut.cpp RWpara/RWPlot.cpp RWpara/RWMass_Scan.cpp RWpara/RWBKG_Sort.cpp RWpara/RWScenario.cpp\
Analyse/Analyse_Find_Cut.cpp  Analyse/Make_Table.cpp \
Analyse/Make_Complete_Table.cpp \
Analyse/Analyse_Pre_Cut.cpp \
Analyse/Analyse_Direct_Cut.cpp\
Analyse/Analyse_Complete.cpp\
Analyse/Abasic.cpp Analyse/Analyse_BDT_Train.cpp Analyse/Analyse_BDT_Attach.cpp \
Analyse/Analyse_Sensitivity.cpp\
Analyse/Analyse_Mass_Scan.cpp\
Analyse/Analyse_Summarize_Plot.cpp\
AnalyseClass/File.cpp AnalyseClass/File_List.cpp AnalyseClass/Sort_List.cpp \
AnalyseClass/AnalyseClass.cpp\
AnalyseClass/Variable.cpp\
AnalyseClass/Plot.cpp\
TSysLimit/TSysLimit.cpp TSysLimit/TSysLimitChannel.cpp TSysLimit/TSysLimitResult.cpp TSysLimit/TSysLimitResultLogL.cpp TSysLimit/TSysLimitResultPBock.cpp TSysLimit/TSysLimitScan.cpp


OBJS=$(patsubst %.cpp, %.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CXX) $(FLAGS) $(INCLUDE) -o $@ $^ $(FASTLIBS) $(ROOTLIBS)  $(LIBS)

%.o: %.cpp
	$(CXX) $(FLAGS) $(INCLUDE) -c $<  -o  $@

clean:
	-rm $(TARGET) $(OBJS)
