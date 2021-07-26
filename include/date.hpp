#ifndef DATE_H
#define DATE_H

#include <iosfwd>
#include <ctime>
#include <map>

class Date {
public:
	enum class WeekDay {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday}; 

	explicit Date(); 					
	explicit Date(int d, int m, int y); 	
	explicit Date(const char *p);  	
	explicit Date(std::time_t timer);
	int 	get_month_day()const;  
	int 	get_month()const; 		
	int 	get_year()const; 		
	int 	get_year_day()const; 	
	WeekDay get_week_day()const; 	

	Date& 	set_month_day( int ); 	
	Date& 	set_month	 ( int ); 	
	Date& 	set_year	 ( int ); 	
    Date& 	set			 ( int , int , int ); 
	Date  	operator-	 ( int )const; 
	Date& 	operator+=	 ( int ); 
	Date& 	operator-=	 ( int ); 
	Date& 	operator++	 (); 
	Date  	operator++	 (int); 
	Date& 	operator--	 (); 
	Date  	operator--	 (int); 

	static Date random_date(); 
	static constexpr bool isleap(int year ){
		return year % 4 == 0 && ( year % 100 != 0 || year % 400 == 0);
	}

	friend bool operator>( const Date&, const Date&); 
	friend bool operator==(const Date&, const Date&); 

	friend std::ostream& operator<<(std::ostream& os, const Date& date);
	friend std::istream& operator>>(std::istream& is, Date& date);
	
private:
	int day_{};
	int mon_{};
	int year_{};

	void is_valid();

	static constexpr int year_base        { 1900 };  
	static constexpr int random_min_year  { 1940 };  
	static constexpr int random_max_year  { 2020 };  

	mutable std::map<int,int> day_count{{1,31},{2,28},{3,31},{4,30},{5,31},{6,30},{7,31},{8,31},{9,30},{10,31},{11,30},{12,31}};
	
};


bool operator<( const Date&, const Date&); 
bool operator<=(const Date&, const Date&); 
bool operator>=(const Date& , const Date&);
bool operator!=(const Date&, const Date&); 

int operator-(const Date &d1, const Date &d2);
Date operator+(const Date &date, int n); 
Date operator+(int n, const Date &); 
Date::WeekDay& operator++(Date::WeekDay &r); 
Date::WeekDay operator++(Date::WeekDay &r, int); 
Date::WeekDay& operator--(Date::WeekDay &r); 
Date::WeekDay operator--(Date::WeekDay &r, int); 

std::ostream &operator<<(std::ostream &os, const Date &date); 
std::istream &operator>>(std::istream &is, Date &date); 
std::ostream& operator<<(std::ostream& os , const Date::WeekDay& wd);

#endif