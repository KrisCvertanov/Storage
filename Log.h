#ifndef LOG_H_
#define LOG_H_
#include "Date.h"
#include "String.h"

class Storage;

class Log {
private:
	Date dateOfLog;
	String message;

public:
	Log();
	Log(const Date, const String);
	Log(const Date, const char*);
	Log(const char*, const char*);

	const Date& getDate() const;
	const String& getMessage() const;

	friend std::istream& operator>>(std::istream&, Log&);
	friend std::ostream& operator<<(std::ostream&, Log&);
	friend class Storage;
};

#endif // !LOG_H_

