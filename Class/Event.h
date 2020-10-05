#pragma once
#ifndef CEVENT_H
#define CEVENT_H
#include "yaml-cpp/yaml.h"

#include "RWpara/RWbasic.h"
#include "Class/Path.h"
#include "TSystem.h"

class CEvent{
	private:
		Long64_t _loop_begin, _loop_end, _tot_num;
		Long64_t _num_first_events, _num_special_events;
	public:
		long long int    event_num    ;
		long long int    total_num    ;



		Long64_t Begin_Event(){
			return(_loop_begin);
		}

		Long64_t End_Event(){
			return(_loop_end);
		}

		long long int Total_Event(){
			return(total_num);
		}

		void Get_Event(long long int num){
			event_num = num;
		};

		long long int Event(){
			return(event_num);
		};

		void Read_Event(CPath path);

		void Init(long long int _tot_num){
			event_num = -1;

			total_num = _tot_num;

			if(_num_first_events!=-1 && _num_special_events==-1){
				_loop_begin = 0;
				if(_num_first_events<_tot_num){
					_loop_end   = _num_first_events;
					total_num   = _loop_end;
				}
				else{
					ShowMessage(2,"_num_first_events > tot_num, show all events");
					_loop_end   = _tot_num;
				}
			}
			else if(_num_first_events==-1 && _num_special_events!=-1){
				if(_num_special_events<_tot_num){
					_loop_begin = _num_special_events;
					_loop_end   = _num_special_events+1;
					total_num   = 1;
				}
				else{
					ShowMessage(2,"_num_special_events > tot_num, only show the last events");
					_loop_begin = _tot_num-1;
					_loop_end   = _tot_num;
					total_num   = 1;
				}
			}
			else if(_num_first_events!=-1 && _num_special_events!=-1){
				if(_num_special_events<_tot_num && _num_first_events<_tot_num  && _num_special_events<_num_first_events){
					_loop_begin = _num_special_events;
					_loop_end   = _num_first_events;
					total_num   = _num_first_events - _num_special_events + 1;
				}
				if(_num_special_events<_tot_num && _num_first_events<_tot_num  && _num_special_events>_num_first_events){
					_loop_begin = _num_first_events;
					_loop_end   = _num_special_events;
					total_num   = _num_special_events - _num_first_events + 1;
				}
				else{
					ShowMessage(2,"in Event.dat,events should satisfy: _num_special_events < _num_first_events, and both < tot_num, please check,  now  only show the last events");
					_loop_begin = 0;
					_loop_end   = _tot_num;
				}
			}
			else{
				_loop_begin = 0;
				_loop_end   = _tot_num;
			}
		}
};


#endif
