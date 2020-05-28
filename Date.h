#ifndef DATE_H_
#define DATE_H_
#include <iostream>
#include <ctime>

class Date {
private:
	int year;
	char month[3];
	char day[3];

public:
	Date();
	Date(const int, const char*, const char*);
	Date& operator=(const char*); // operator= chrez niz

	const int getYear() const;    //
	const char* getMonth() const; // funkcii za dostup 
	const char* getDay() const;   //

	bool operator==(const Date&);//
	bool operator<(const Date&); // 
	bool operator>(const Date&); // logicheski operacii 
	bool operator<=(const Date&);//
	bool operator>=(const Date&);//
	bool isValid(); // proverka za validna data


	friend std::istream& operator>>(std::istream&, Date&);       // operatori za vhod 
	friend std::ostream& operator<<(std::ostream&, const Date&); // i izhod
};


#endif // DATE_H_
