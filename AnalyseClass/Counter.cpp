#include "AnalyseClass/Counter.h"

void ACounter::Init(CDraw &para, int input_entries){
	AllEntries   = input_entries;
	jetSwitch    = para.jet.SWITCH; 
	jetsSwitch   = para.jet.jets.SWITCH; 
	bjetSwitch   = para.jet.bjet.SWITCH; 
	lepSwitch    = para.lep.SWITCH; 
	elecSwitch   = para.lep.elec.SWITCH; 
	muonSwitch   = para.lep.muon.SWITCH; 
	metSwitch    = para.met.SWITCH; 
	combSwitch   = para.comb.SWITCH;
	recoilSwitch = para.recoil.SWITCH;
	recombSwitch = para.recoil.comb_SWITCH;
	mdSwitch     = para.MassDrop.SWITCH;
	nsubSwitch   = para.NSubjettiness.SWITCH;
	boostSwitch  = para.BoostTag.SWITCH;
	jetsubSwitch = para.jetsub.SWITCH;
	jepSwitch    = para.jep.SWITCH;
}


void ACounter::setWeight(float value){
	_weight = value;
}

void ACounter::setCounter(ASpecies& spe){
	for(ASpeciesType::iterator it = spe._species.begin(); it!=spe._species.end(); ++it ){
		////ShowMessage(2,"weight ",_weight);
		////ShowMessage(2,"num name",it->first);
		////ShowMessage(2,"num value",it->second);
		setCounterSingle(it->first,it->second.size()*_weight);	
		////ShowMessage(2,"next loop",0);
	}
}

void ACounter::setCounterSingle(std::string event_name,float num){
	_counter[event_name]=_counter[event_name]+num;
}


void ACounter::showCounter(){
	ShowMessage(2," OutPut --- Species for All Particle" );
	for(ACounterType::iterator it = _counter.begin(); it!= _counter.end(); ++it ){
		ShowMessage(2,"number  of "+it->first+" is" , it->second);
	}
}


void ACounter::getCounter(std::string event_name){
	if(event_name=="basic"){
		pass_basic++;
	}
	else if(event_name=="basic_jet"){
		pass_basic_jet++;
	}
	else if(event_name=="basic_tagged_jet"){
		pass_basic_bjet++;
	}
	else if(event_name=="basic_lep"){
		pass_basic_lep++;
	}
	else if(event_name=="basic_elec"){
		pass_basic_elec++;
	}
	else if(event_name=="basic_muon"){
		pass_basic_muon++;
	}
	else if(event_name=="basic_met"){
		pass_basic_met++;
	}
	else if(event_name=="operation_combine1"){
		pass_remass1++;
	}
	else if(event_name=="operation_combine2"){
		pass_remass2++;
	}
	else if(event_name=="operation_recoil"){
		pass_recoilmass++;
	}
	else if(event_name=="operation_recoil_comb"){
		pass_comb_recoil++;
	}
	else if(event_name=="JSS_Massdrop"){
		pass_massdrop++;
	}
	else if(event_name=="JSS_Nsubjettiness"){
		pass_nsubjettiness++;
	}
	else if(event_name=="JSS_BoostTag"){
		pass_boosttag++;
	}
	else if(event_name=="JSS"){
		pass_jetsub++;
	}
	else if(event_name=="JES_JEP"){
		pass_jep++;
	}
	else if(event_name=="All"){
		pass++;
	}
}



void ACounter::sendCounter(std::string event_name){
	if(event_name=="basic_jet"&& jetSwitch && jetsSwitch){
		ShowMessage(2,"number    passed cut basic  jet is        " , pass_basic_jet);
		ShowMessage(2,"efficient passed cut basic  jet is        " ,float(pass_basic_jet     )/float(AllEntries));
	}
	if(event_name=="basic_tagged_jet"&& jetSwitch && jetsSwitch &&  bjetSwitch){
		ShowMessage(2,"efficient passed cut tagged jet is        ", float(pass_basic_bjet    )/float(AllEntries));
	}
	if(event_name=="basic_lep"&& lepSwitch && elecSwitch && muonSwitch ){
		ShowMessage(2,"efficient passed cut baisc lep  is        ", float(pass_basic_lep     )/float(AllEntries));
	}
	if(event_name=="basic_elec"&& lepSwitch && elecSwitch && !muonSwitch ){
		ShowMessage(2,"efficient passed cut baisc elec is        ", float(pass_basic_elec    )/float(AllEntries));
	}
	if(event_name=="basic_muon"&& lepSwitch && !elecSwitch && muonSwitch ){
		ShowMessage(2,"efficient passed cut basic muon is        ", float(pass_basic_muon    )/float(AllEntries));
	}
	if(event_name=="basic_met"&& metSwitch){
		ShowMessage(2,"efficient passed cut basic  met is        ", float(pass_basic_met     )/float(AllEntries));
	}
	if(event_name=="basic" ){
		ShowMessage(2,"efficient passed cut basic is             ", float(pass_basic         )/float(AllEntries));
	}
	if(event_name=="operation_combine1"&& combSwitch){
		ShowMessage(2,"efficient passed cut remass1    is        ", float(pass_remass1       )/float(AllEntries));
	}
	if(event_name=="operation_combine2"&& combSwitch){
		ShowMessage(2,"efficient passed cut remass1    is        ", float(pass_remass2       )/float(AllEntries));
	}
	if(event_name=="operation_recoil"&& recoilSwitch){
		ShowMessage(2,"efficient passed cut recoilmass is        ", float(pass_recoilmass    )/float(AllEntries));
	}
	if(event_name=="operation_recoil_comb"&& recombSwitch){
		ShowMessage(2,"efficient passed cut comb recoil is       ", float(pass_comb_recoil   )/float(AllEntries));
	}
	if(event_name=="JSS_Massdrop"&& mdSwitch){
		ShowMessage(2,"efficient passed cut MassDrop   is        ", float(pass_massdrop      )/float(AllEntries));
	}
	if(event_name=="JSS_Nsubjettiness"&& nsubSwitch){
		ShowMessage(2,"efficient passed cut NSubjettiness is     ", float(pass_nsubjettiness )/float(AllEntries));
	}
	if(event_name=="JSS_BoostTag"&& boostSwitch){
		ShowMessage(2,"efficient passed cut BoostTag   is        ", float(pass_boosttag      )/float(AllEntries));
	}
	if(event_name=="JSS"&& jetsubSwitch){
		ShowMessage(2,"efficient passed cut JetSubStructure is   " , float(pass_jetsub       )/float(AllEntries));
	}
	if(event_name=="JES_JEP"&& jepSwitch){
		ShowMessage(2,"efficient passed cut JEP        is        ", float(pass_jep           )/float(AllEntries));
	}
	if(event_name=="All"){
		ShowMessage(2,"efficient passed cut all        is        " , float(pass              )/float(AllEntries));
	}
}
void ACounter::sendCounter(){
	ShowMessage(2," OutPut --- Efficience for Cut" );
	ShowMessage(2,"all entries are                      " , AllEntries);
	sendCounter("basic_jet");
	sendCounter("basic_tagged_jet");
	sendCounter("basic_lep");
	sendCounter("basic_elec");
	sendCounter("basic_muon");
	sendCounter("basic_met");
	sendCounter("basic");
	sendCounter("operation_combine1");
	sendCounter("operation_combine2");
	sendCounter("operation_recoil");
	sendCounter("operation_recoil_comb");
	sendCounter("JSS_Massdrop");
	sendCounter("JSS_Nsubjettiness");
	sendCounter("JSS_BoostTag");
	sendCounter("JSS");
	sendCounter("JSS_JEP");
	sendCounter("All");
	ShowMessage();
	ShowMessage(2,"");
}

void ACounter::Clear(){
	pass_basic        =0;
	pass_basic_jet    =0, pass_basic_bjet=0,pass_basic_cjet=0,pass_basic_qjet=0;
	pass_basic_lep    =0, pass_basic_elec=0,pass_basic_muon=0,pass_basic_met =0;
	pass_basic_photon =0;
	pass_combine      =0;
	pass_remass1      =0, pass_remass2   =0,pass_recoilmass=0;
	pass_comb_recoil  =0;
	pass_jetsub       =0;
	pass_boosttag     =0, pass_massdrop=0, pass_nsubjettiness=0;
	pass_jeteventshape=0, pass_jep          =0;
	pass              =0;

	jetSwitch         = false;
	jetsSwitch        = false;
	bjetSwitch        = false;
	lepSwitch         = false;
	elecSwitch        = false;
	muonSwitch        = false;
	metSwitch         = false;
	combSwitch        = false;
	recoilSwitch      = false;
	recombSwitch      = false;
	mdSwitch          = false;
	nsubSwitch        = false;
	boostSwitch       = false;
	jetsubSwitch      = false;
	jepSwitch         = false;
	jesSwitch         = false;

	_counter          .clear();
	_weight           = 1;
}
