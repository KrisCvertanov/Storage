#include "Date.h"

Date::Date() { // defolten konstruktor
	year = 0;
	month[0] = '0';
	month[1] = '0';
	month[2] = '\0';
	day[0] = '0';
	day[1] = '0';
	day[2] = '\0';
}

Date::Date(const int year_, const char* month_, const char* day_) { // konstruktor s parametri
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

bool Date::operator==(const Date& other) const { // proverka dali 2 dati sa ednakvi
	if (year == other.year && month[0] == other.month[0] && month[1] == other.month[1] && day[0] == other.day[0] && day[1] == other.day[1]) {
		return true;
	}
	return false;
}

bool Date::isValid() const { // proverka dali data e validna
	if (day[0] < '0' || day[0] > '3') return false; // proverka dali denyat i mesecut sa validni
	if (day[1] < '0' || day[1] > '9') return false;
	if (month[0] < '0' || month[0] > '1') return false;
	if (month[1] < '0' || month[1] > '9') return false;
	if (month[0] == '1' && month[1] > '2') return false;
	if (day[0] == '3' && (day[1] < '0' || day[1] > '1' || (month[0] == '0' && month[1] == '2'))) return false;
	if (day[0] == '3' && day[1] == '1' && (month[1] == '4' || month[1] == '6' || month[1] == '9' || (month[0] == '1' && month[1] == '1'))) return false;
	if (month[0] == '0' && month[1] == '2' && day[0] == '2' && day[1] == '9') { // ako e visokosna (29.02)
		if (year % 400 == 0) return true;
		if (year % 100 == 0) return false;
		if (year % 4 == 0) return true;
		return false;
	}
	if (year <= 0) return false;
	return true;
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
	if (!(date.isValid())) {
		std::cerr << "That date does not exist!" << std::endl;
	}
	return in;

}

std::ostream& operator<<(std::ostream& out, const Date& date) {
	out << date.year << "-" << date.month << "-" << date.day;
	return out;
}

bool Date::operator<(const Date& other) const { // proverka dali data e po - stara ot druga
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

bool Date::operator>(const Date& other) const {
	return !(*this < other || *this == other);
}

bool Date::operator<=(const Date& other) const {
	return !(*this > other);
	
}

bool Date::operator>=(const Date& other) const {
	return !(*this < other);
}
