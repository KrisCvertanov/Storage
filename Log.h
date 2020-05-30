#ifndef LOG_H_
#define LOG_H_
#include "Date.h"
#include "String.h"

class Storage;

class Log {
private:
	Date dateOfLog;       // data na spravka
	String message;		  // suobshtenie na spravka

public:
	Log();
	Log(const Date&, const String&);
	Log(const Date&, const char*);
	Log(const char*, const char*); 

	const Date& getDate() const;      // funkcii za dostup
	const String& getMessage() const; // 

	friend std::istream& operator>>(std::istream&, Log&); // operatori za vhod
	friend std::ostream& operator<<(std::ostream&, Log&); // i izhod
	friend class Storage;
};

#endif // !LOG_H_

