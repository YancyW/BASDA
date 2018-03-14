#include "Lib/YAML_Assistant.h"
void YAML_Type(YAML::Node nodes){
	ShowMessage(3,"Find node type");
	switch(nodes.Type()){
		case YAML::NodeType::Null     : ShowMessage(4,"The node type is", "Null"     );break;
		case YAML::NodeType::Scalar   : ShowMessage(4,"The node type is", "Scalar"   );break;
		case YAML::NodeType::Sequence : ShowMessage(4,"The node type is", "Sequence" );break;
		case YAML::NodeType::Map      : ShowMessage(4,"The node type is", "Map"      );break;
		case YAML::NodeType::Undefined: ShowMessage(4,"The node type is", "Undefined");break;
	}
	ShowMessage(4,"The node size is",nodes.size());
}
