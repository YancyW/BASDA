#include "Class/DrawClass.h"
void CDraw::Read(){
	this->path.Read_Path(this->steering_file);
	default_path = path;
	Jpath = true;

	this->file.Read_File(path);
	default_file = file;
	Jfile = true;

	this->debug.Read_Debug(path);
	Jdebug = true;

	this->flow.Read_Flow(path);
	default_flow = flow;
	Jflow = true;

	this->event.Read_Event(path);
	default_event = event;
	Jevent = true;

	this->var.Read_Var(path);
	default_var = var;
	Jvar = true;

	this->sensitivity.Read_Sensitivity(path);
	default_sensitivity = sensitivity;
	Jsen = true;

    this->signal_scan.Read_Signal_Properties_Scan(path);
	default_signal_scan = signal_scan;
    JSP_scan = true;

    //this->bkg_sort.Read_BKG_Sort(path);
    this->bkg_sort.Read_BKG_Sort_Test(path);
	default_bkg_sort = bkg_sort;
    Jbkg_sort= true;

    this->scenario.Read_Scenario(path,flow);
	default_scenario = scenario;
    Jscenario= true;

    this->plot.Read_Plot(path);
	default_plot = plot;
    Jplot= true;

    this->plot_direct.Read_Plot_Direct(path);
	default_plot_direct = plot_direct;
    Jplot_direct= true;

    this->MVA.Read_MVA(path,flow);
	default_MVA = MVA;
    JMVA= true;

    this->cut_scan.Read_Cut_Scan(path.cut_scan_file);
	default_cut_scan= cut_scan;
    Jcut_scan= true;
}
