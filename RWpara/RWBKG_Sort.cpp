#include "Class/BKG_Sort.h"
#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"

void CBKG_Sort:: Read_BKG_Sort(CPath &path){
	ShowMessage(3, "read BKG_Sort");
	YAML::Node bkg_node = YAML::LoadFile(path.bkg_sort_file);

	std::vector<int> input_class_vec;
	std::vector<std::string> input_class_name;
	std::vector<std::string> _string_tmp;

	RW_element("sort_num" ,bkg_node,this->_sort_num);
	for(int i=0;i<_sort_num;i++){
		RW_vector_element("sub_sort_num"      ,i,bkg_node,input_class_vec);
		RW_vector_element("sub_sort_name"     ,i,bkg_node,input_class_name);
	}

	sort.resize(_sort_num);
	for(int i=0;i<_sort_num;i++){
		for(int j=0;j<input_class_vec[i];j++){
			RW_vector_element(input_class_name[i] ,j,bkg_node,_string_tmp);
		}
		sort[i].Set_Class(input_class_name[i]);
		for(int j=0;j<input_class_vec[i];j++){
			std::size_t code_pos = _string_tmp[j].find(";");
			if(code_pos!=std::string::npos){
				std::string first_name = _string_tmp[j].substr(0,code_pos);
				std::string code_name  = _string_tmp[j].substr(code_pos+1);
                sort[i].Set_Sub_Class(first_name);
				sort[i].Set_Default_Legend(input_class_name[i]+"_{"+first_name+"}"); 
				sort[i].Set_Default_Sub_Legend("{"+first_name+"}"); 
				sort[i].Set_Legend(code_name); 
			}
			else{
                sort[i].Set_Sub_Class(_string_tmp[j]);
				sort[i].Set_Default_Legend(input_class_name[i]+"_{"+_string_tmp[j]+"}"); 
				sort[i].Set_Default_Sub_Legend("{"+_string_tmp[j]+"}"); 
				sort[i].Set_Legend        (input_class_name[i]+"_{"+_string_tmp[j]+"}"); 
			}
		}
		sort[i].Set();
		_string_tmp.clear();
	}


	ShowMessage(3,"sort size",sort.size());
	for(unsigned int i=0;i<sort.size();i++){
		ShowMessage(3,"sort ",i,"th class name",sort[i].Class());
		for(int j=0;j<sort[i].Sub_Num();j++){
			ShowMessage(4,"sort ",i,"th sub class",sort[i].Sub_Class(j));
			ShowMessage(4,"sort ",i,"th default legend",sort[i].Default_Legend(j));
			ShowMessage(4,"sort ",i,"th personal legend",sort[i].Legend(j));
		}
	}
}

