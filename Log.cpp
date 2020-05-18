#include "Log.h"

Log::Log() {}

Log::Log(const Date date_, const String message_) {
	dateOfLog = date_;
	message = message_;
}

Log::Log(const Date date_, const char* message_) {
	dateOfLog = date_;
	message = message_;
}

Log::Log(const char* date_, const char* message_) {
	dateOfLog = date_;
	message = message_;
}

const Date& Log::getDate() const {
	return dateOfLog;
}

const String& Log::getMessage() const {
	return message;
}

std::istream& operator>>(std::istream& in, Log& log) {
	in >> log.dateOfLog;
	in.ignore();
	in.ignore();
	in >> log.message;
	return in;
}

std::ostream& operator<<(std::ostream& out, Log& log) {
	out << log.dateOfLog << ": " << log.message << std::endl;
	return out;
}
