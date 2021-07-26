#include "date.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <map>

Date::Date() : day_(1) , mon_(1) , year_(year_base) {} 
Date::Date(int d, int m, int y): day_{d} , mon_{m} , year_{y}{ }  
Date::Date(const char *p){
	char* date = strdup(p);
    char* token = strtok(date, ".");
    std::vector<int> tmp;
    
    while (token) {
        tmp.push_back(atoi(token));
        token = std::strtok(nullptr, ".");
    }
	day_  = tmp[0];
	mon_  = tmp[1];
	year_ = tmp[2];
}  
Date::Date(std::time_t timer){
	struct tm * ptm;
    time( &timer );
    ptm = gmtime ( &timer );

    day_  = ptm->tm_mday ;
	mon_  = ptm->tm_mon + 1;
	year_ = ptm->tm_year+1900;
}
int Date::get_month_day()const{ return day_; } 
int Date::get_month()const{ return mon_; } 
int Date::get_year()const{ return year_; } 
int Date::get_year_day()const{
	
	if(isleap(year_))
		day_count[2] = 29;
    int count{};

    for(int i = 1 ; i < mon_ ; i++)
        count += day_count[i];
    count += day_;

	return count;    
} 
Date::WeekDay Date::get_week_day()const{
    std::tm time_in = { 0, 0, 0, day_, mon_-1, year_- 1900 };
    std::time_t time_temp = std::mktime(&time_in);
    const std::tm * time_out = std::localtime(&time_temp);

    switch(time_out->tm_wday){
        case 1:
            return Date::WeekDay::Monday;
            break;
        case 2:
            return Date::WeekDay::Tuesday;
            break;
        case 3:
            return Date::WeekDay::Wednesday;
            break;
        case 4:
            return Date::WeekDay::Thursday;
            break;
        case 5:
            return Date::WeekDay::Friday;
            break;
        case 6:
            return Date::WeekDay::Saturday;
            break;
        case 0:
            return Date::WeekDay::Sunday;
            break;
    }
} 
Date& Date::set_month_day(int day){ 
	day_ = day; 
	return *this;
} 
Date& Date::set_month(int month){ 
	mon_ = month;
	return *this;	
} 
Date& Date::set_year(int year){ 
	year_ = year; 
	return *this;
} 
Date& Date::set(int day, int mon, int year){
	day_  = day;
	mon_  = mon;
	year_ = year;
	return *this;
} 
bool operator<( const Date& dateFirst, const Date& dateSec){
	return ( dateFirst <= dateSec && !(dateFirst == dateSec));
} 
bool operator<=(const Date& dateFirst, const Date& dateSec){
	return !( dateFirst > dateSec);
} 
bool operator>( const Date& dateFirst, const Date& dateSec){
	return dateFirst.year_ > dateSec.year_ ? true : 
		   dateFirst.mon_  > dateSec.mon_  ? true : 
		   dateFirst.day_  > dateSec.day_  ? true : false ;
} 
bool operator>=(const Date& dateFirst, const Date& dateSec){
	return ( (dateFirst > dateSec) || (dateFirst == dateSec));
} 
bool operator==(const Date& dateFirst, const Date& dateSec){
	return dateFirst.day_  == dateSec.day_ && 
		   dateFirst.mon_  == dateSec.mon_ &&
		   dateFirst.year_ == dateSec.year_;
}
bool operator!=(const Date& dateFirst, const Date& dateSec){
	return !( dateFirst == dateSec);
} 
std::ostream& operator<<(std::ostream &os, const Date &date){
	os << date.day_ << "." << date.mon_ << "." << date.year_ ;
	return os << "\n";
} 
std::istream& operator>>(std::istream &is, Date &date){
	is >> date.day_;
	is >> date.mon_;
	is >> date.year_;
	return is;
} 
std::ostream& operator<<(std::ostream& os , const Date::WeekDay& wd){
	switch(wd){
        case Date::WeekDay::Monday:
            return os << "Monday\n";
            break;
        case Date::WeekDay::Tuesday:
            return os << "Tuesday\n";
            break;
        case Date::WeekDay::Wednesday:
            return os << "Wednesday\n";
            break;
        case Date::WeekDay::Thursday:
            return os << "Thursday\n";
            break;
        case Date::WeekDay::Friday:
            return os << "Friday\n";
            break;
        case  Date::WeekDay::Saturday:
            return os << "Saturday\n";
            break;
        case Date::WeekDay::Sunday:
            return os << "Sunday\n";
            break;
    }
}
void Date::is_valid() {
	if( day_ > day_count[mon_]){		
		int count{};
		while(  day_ > day_count[mon_] ){
			day_ -= day_count[mon_];
			count++;
		}

		if( count >= 12 ){
			int tmp = count / 12;
			year_ += tmp;
			count -= tmp * 12;
		}
		mon_ += count;
	}
	if(day_ < 1 ){
		int count{};
		while( day_ < 1){
			day_ += day_count[mon_ - 1];
			count++;
		}

		if(count >= 12){
			int tmp = count / 12;
			year_   -= tmp;
			count   -= tmp-12;  
		}
		mon_ -= count;
	}
}
Date  Date::operator-(int day)const{
	Date temp{*this};
	for(int i = 0 ; i < day ; i++)
		--temp;
	return temp;
} 
Date& Date::operator+=(int day){
	day_ += day;
	is_valid();
	return *this;
} 
Date& Date::operator-=(int day){
	day_ -= day;
	is_valid();
	return *this;
} 
Date& Date::operator++(){
	++day_;
	is_valid();
	return *this;
} 
Date  Date::operator++(int){
	Date temp{*this};
	++*this;
	return temp;
} 
Date& Date::operator--(){
	--day_;
	is_valid();
	return *this;
} 
Date  Date::operator--(int){
	Date temp{*this};
	--*this;
	return temp;
} 
Date Date::random_date(){
    srand (time(NULL));
    int year = (random_min_year + ((rand() % (random_max_year - random_min_year)) + 1));
    int mon = rand() % 12 + 1;
    int day = rand() % 28 + 1;
	return Date{day , mon , year};
} 
int operator-(const Date &d1, const Date &d2){
	int tmp{};
    struct std::tm last_date = {0,0,0,d1.get_month_day(),d1.get_month()-1,d1.get_year()}; 
    struct std::tm first_date = {0,0,0,d2.get_month_day(),d2.get_month()-1,d2.get_year()}; 
    std::time_t first = std::mktime(&first_date);
    std::time_t last = std::mktime(&last_date);
    if ( first != (std::time_t)(-1) && last != (std::time_t)(-1) )
        tmp = std::difftime(last, first) / (60 * 60 * 24);
	return tmp;
        
}
Date operator+(const Date &date, int n){
	Date tmp = date;
	tmp += n;
	return tmp;
}
Date operator+(int n, const Date& date){
	Date tmp = date;
	tmp += n;
	return tmp;
}
Date::WeekDay& operator--(Date::WeekDay &r){
	if( r == Date::WeekDay::Sunday)
		r = Date::WeekDay::Saturday;
	else 
		r = static_cast<Date::WeekDay>(static_cast<int>(r)-1);
	return r;
}
Date::WeekDay  operator--(Date::WeekDay &r, int){
	Date::WeekDay tmp = r;
	--r;
	return tmp;
}
Date::WeekDay& operator++(Date::WeekDay &r){
	if( r == Date::WeekDay::Saturday)
		r = Date::WeekDay::Sunday;
	else
		r = static_cast<Date::WeekDay>(static_cast<int>(r)+1);
	return r;
}
Date::WeekDay  operator++(Date::WeekDay &r, int){
	Date::WeekDay tmp = r;
	++r;
	return tmp;
}
