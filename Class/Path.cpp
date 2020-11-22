#include "Class/Path.h"

void CPath::Create_Folder(){
	::Create_Folder(this->output_file);
	::Create_Folder(this->event_file);
	::Create_Folder(this->single_plot);
	::Create_Folder(this->combine_plot);
	::Create_Folder(this->horizontal_summary_plot);
}



void CPath::Print(){
	ShowMessage(2,"The CPath is ");
	ShowMessage(3,"process                   is ", process                     );
	ShowMessage(3,"output_folder             is ", output_folder               );
	ShowMessage(3,"input_folder              is ", input_folder                );

	ShowMessage(3,"record_file               is ", record_file                 );

	ShowMessage(3,"output_file               is ", output_file                 );
	ShowMessage(3,"event_file                is ", event_file                  );
	ShowMessage(3,"single_plot               is ", single_plot                 );
	ShowMessage(3,"combine_plot              is ", combine_plot                );
	ShowMessage(3,"horizontal_summary_plot   is ", horizontal_summary_plot     );

	ShowMessage(3,"input_file                is ", input_file                  );
	ShowMessage(3,"debug_file                is ", debug_file                  );
	ShowMessage(3,"analyse_file              is ", analyse_file                );
	ShowMessage(3,"flow_file                 is ", flow_file                   );
	ShowMessage(3,"cut_file                  is ", cut_file                    );
	ShowMessage(3,"plot_file                 is ", plot_file                   );
	ShowMessage(3,"MVA_file                  is ", MVA_file                    );

	ShowMessage(3,"var_file                  is ", var_file                    );
	ShowMessage(3,"sensitivity_file          is ", sensitivity_file            );
	ShowMessage(3,"signal_property_scan_file is ", signal_property_scan_file   );
	ShowMessage(3,"bkg_sort_file             is ", bkg_sort_file               );
	ShowMessage(3,"scenario_file             is ", scenario_file               );
	ShowMessage(3,"cut_scan_file             is ", cut_scan_file               );
}

std::ostream & operator<< (std::ostream & ostr, CPath str){
	str.Print();
	return ostr;
}

