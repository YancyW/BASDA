#pragma once
#ifndef GLOBAL_PARA_TIME_H
#define GLOBAL_PARA_TIME_H
#include <string> 
#include <time.h>

class CTime{
	private:
		time_t _begin_time;

		time_t _current_time;
	public:
		void Begin_Time(){
			time(&_begin_time);
			ShowMessage(2,"The begin time is ", ctime(&_begin_time));
		}

		void Current_Time(){
			time(&_current_time);
			ShowMessage(2,"The current time is ", ctime(&_current_time));
		}

		void Time_Interval(){
			double seconds;
			seconds = difftime(_current_time,_begin_time);
			ShowMessage(2," cost time",seconds ,"seconds");
		}
};

#endif
