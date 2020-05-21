#ifndef _STRING_H_
#define _STRING_H_
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<cstring>


class String {
private:
	char* arr;
	int capacity;
	int size;

	void copyStrings(const char*, const int, const int);
	void deleteString();
public:
	String();
	String(const char*, const int, const int);
	String(const String&);
	String& operator=(const String&);
	String& operator=(const char*);
	~String();
	friend std::istream& operator>>(std::istream&, String&);
	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::ifstream& operator>>(std::ifstream&, String&);
	friend std::ofstream& operator<<(std::ofstream&, const String&);
	char& operator[](const int);
	bool operator==(const String&) const;
	bool operator==(const char*) const;
	bool operator!=(const String&) const;
	bool operator!=(const char*) const;
	String& operator+=(const String&);
	String& to_string(const int);
	int getCapacity() const;
	int getSize() const;
	void clear();


};


#endif // !_STRING_H_

