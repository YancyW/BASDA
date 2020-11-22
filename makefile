TARGET=BASDA

CXX=g++
FLAGS=-std=c++14 -g 
#-Wall

RootPath=${HOME}/Software/executable/root/
YAMLPath=${HOME}/Software/lib/yaml-cpp/
JPEGPath=${HOME}/Software/executable/anaconda3/pkgs/jpeg-8d-2/lib/
CPPITERTOOL=${HOME}/Software/lib/cppitertools-1.0

INCLUDE = -I. -I..  -I$(RootPath)/include  -I${YAMLPath}/include -I${CPPITERTOOL}/ -I${CPPITERTOOL}/internal -I${CPPITERTOOL}/test


LIBS =  -lboost_filesystem  -lboost_system -lTMVA -lTMVAGui ${YAMLPath}/libyaml-cpp.a 
ROOTLIBS = -L${RootPath}/lib -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lEG -lm -ldl -rdynamic -lTreePlayer

SRCS = \
$(TARGET).cpp \
Class/Path.cpp Class/Cut_Scan.cpp Class/BKG_Sort.cpp Class/Debug.cpp Class/DrawClass.cpp Class/Event.cpp Class/File.cpp Class/Flow.cpp Class/MVA.cpp Class/Path.cpp Class/Plot.cpp Class/Scenario.cpp Class/Sensitivity.cpp Class/Signal_Properties_Scan.cpp \
Test/Test_Function.cpp Test/Test_Tuple.cpp Test/Test_CPPIterTools.cpp\
Fram/Fram.cpp Fram/Fsection.cpp \
Function/Fbasic.cpp Function/Fvector.cpp Function/Ffile.cpp Function/FCalc.cpp Function/FString.cpp\
Latex/LTable.cpp Latex/LItem.cpp\
Lib/MessageFormat.cpp Lib/PlotSetting.cpp Lib/Record.cpp Lib/YAML_Assistant.cpp\
RWpara/RWFile.cpp RWpara/RWFlow.cpp RWpara/RWPath.cpp RWpara/RWDebug.cpp RWpara/RWDraw.cpp RWpara/RWbasic.cpp RWpara/RWEvent.cpp RWpara/RWVar.cpp\
RWpara/RWSensitivity.cpp RWpara/RWCut.cpp RWpara/RWPlot.cpp RWpara/RWSignal_Properties_Scan.cpp RWpara/RWBKG_Sort.cpp RWpara/RWScenario.cpp RWpara/RWMVA.cpp\
RWpara/RWPlot_Direct.cpp RWpara/RWCut_Scan.cpp\
Analyse/Analyse_Find_Cut.cpp  Analyse/Make_Table.cpp \
Analyse/Make_Complete_Table.cpp \
Analyse/Make_Efficiency_Plot.cpp Analyse/Make_Complete_Efficiency_Plot.cpp \
Analyse/Analyse_Pre_Cut.cpp \
Analyse/Analyse_Direct_Cut.cpp\
Analyse/Analyse_Cut_NoMVA.cpp \
Analyse/Analyse_Complete.cpp\
Analyse/Abasic.cpp Analyse/Analyse_MVA_Train.cpp Analyse/Analyse_MVA_Attach.cpp \
Analyse/Analyse_Sensitivity.cpp\
Analyse/Analyse_Signal_Scan.cpp\
Analyse/Analyse_Summarize_Plot.cpp\
Analyse/Analyse_Plot_Direct.cpp\
Analyse/Analyse_Summarize_Cut_Efficiency_Plot.cpp\
Analyse/Analyse_Summarize_Sensitivity.cpp\
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
