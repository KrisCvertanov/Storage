#ifndef _STRING_H_
#define _STRING_H_
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<cstring>
#include<exception>


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
	String& operator=(const char*); // operator= za niz
	~String();
	friend std::istream& operator>>(std::istream&, String&);        //
	friend std::ostream& operator<<(std::ostream&, const String&);  // operatori za vhod i izhod
	friend std::ifstream& operator>>(std::ifstream&, String&);      //
	friend std::ofstream& operator<<(std::ofstream&, const String&);//
	char& operator[](const int);
	bool operator==(const String&) const;   //
	bool operator==(const char*) const;     // logicheski operacii
	bool operator!=(const String&) const;   //
	bool operator!=(const char*) const;     //
	String& operator+=(const String&); // operator za konkatenaciya
	String& to_string(const int); // konvertira cyalo chislo v niz
	int getCapacity() const;  // 
	int getSize() const;      // funkcii za dostup
	void clear(); // izchistva stringa


};


#endif // !_STRING_H_

