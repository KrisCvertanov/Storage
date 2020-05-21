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
	Date& operator=(const char*);

	const int getYear() const;
	const char* getMonth() const;
	const char* getDay() const;
	bool operator==(const Date&);
	bool operator<(const Date&);
	bool operator>(const Date&);
	bool operator<=(const Date&);
	bool operator>=(const Date&);


	friend std::istream& operator>>(std::istream&, Date&);
	friend std::ostream& operator<<(std::ostream&, const Date&);
	/*friend std::ifstream& operator>>(std::ifstream&, Date&);
	friend std::ofstream& operator<<(std::ofstream&, Date&);*/

};


#endif // DATE_H_
