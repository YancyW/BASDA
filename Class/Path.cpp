#include "Class/Path.h"

void CPath::Create_Folder(){
	::Create_Folder(this->output_file);
	::Create_Folder(this->event_file);
	::Create_Folder(this->single_plot);
	::Create_Folder(this->combine_plot);
	::Create_Folder(this->horizontal_summary_plot);
}
