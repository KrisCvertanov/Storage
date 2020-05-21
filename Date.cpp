#include "Date.h"

Date::Date() {
	year = 0;
	month[0] = '0';
	month[1] = '0';
	month[2] = '\0';
	day[0] = '0';
	day[1] = '0';
	day[2] = '\0';
}

Date::Date(const int year_, const char* month_, const char* day_) {
	year = year_;
	month[0] = month_[0];
	month[1] = month_[1];
	month[2] = '\0';
	day[0] = day_[0];
	day[1] = day_[1];
	day[2] = '\0';
}

Date& Date::operator=(const char* date_) {
	year = atoi(date_);
	int i = 0;
	do { i++; }while (date_[i] != '-' && date_[i] != '\0');
	i++;
	month[0] = date_[i];
	i++;
	month[1] = date_[i];
	i += 2;
	day[0] = date_[i];
	i++;
	day[1] = date_[i];

	return *this;
}

const int Date::getYear() const {
	return year;
}

const char* Date::getMonth() const {
	return month;
}

const char* Date::getDay() const {
	return day;
}

bool Date::operator==(const Date& other) {
	if (year == other.year && month[0] == other.month[0] && month[1] == other.month[1] && day[0] == other.day[0] && day[1] == other.day[1]) {
		return true;
	}
	return false;
}

std::istream& operator>>(std::istream& in, Date& date) {
	char dash;
	in >> date.year;
	in >> dash;
	if (dash != '-') {
		std::cout << "Invalid format of date!" << std::endl;
		return in;
	}
	in.get(date.month, 3);
	in >> dash;
	if (dash != '-') {
		std::cout << "Invalid format of date!" << std::endl;
		return in;
	}
	in.get(date.day, 3);
	return in;

}

std::ostream& operator<<(std::ostream& out, const Date& date) {
	out << date.year << "-" << date.month << "-" << date.day;
	return out;
}

/*std::ifstream& operator>>(std::ifstream& iFile, Date& date) {

}

std::ofstream& operator<<(std::ofstream& oFile, Date& date) {
	oFile << date.year << "-" << date.month << "-" << date.day << std::endl;
	return oFile;
}*/

bool Date::operator<(const Date& other) {
	if (year < other.year) return true;
	else if (year == other.year) {
		if (month[0] < other.month[0]) return true;
		else if (month[0] == other.month[0]) {
			if (month[1] < other.month[1]) return true;
			else if (month[1] == other.month[1]) {
				if (day[0] < other.day[0]) return true;
				else if (day[0] == other.day[0]) {
					if (day[1] < other.day[1]) return true;
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

bool Date::operator>(const Date& other) {
	return !(*this < other || *this == other);
}

bool Date::operator<=(const Date& other) {
	return !(*this > other);
	
}

bool Date::operator>=(const Date& other) {
	return !(*this < other);
}
