TARGET=BASDA

CXX=g++
FLAGS=-std=c++14 -g 
#-Wall

RootPath=/home/yancy/Software/executable/root/build
YAMLPath=/home/yancy/Software/lib/yaml-cpp/

INCLUDE = -I. -I..  -I$(RootPath)/include  \
		  -I${YAMLPath}/include

LIBS =  -lboost_filesystem  -lboost_system -lTMVA -lTMVAGui ${YAMLPath}/libyaml-cpp.a 
ROOTLIBS = -L/home/yancy/Software/executable/root/build/lib -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lEG -lm -ldl -rdynamic -lTreePlayer

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
Analyse/Analyse_Cut_NoMVA.cpp \
Analyse/Analyse_Complete.cpp\
Analyse/Abasic.cpp Analyse/Analyse_MVA_Train.cpp Analyse/Analyse_MVA_Attach.cpp \
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
