#include "String.h"

void String::copyStrings(const char* arr_, const int capacity_, const int size_) {
	arr = new(std::nothrow) char[strlen(arr_) + 1];
	if (arr == nullptr) {
		throw ("No memory for string!(String::copyStrings())");
		return;
	}
	strcpy(arr, arr_);
	capacity = capacity_;
	size = size_;
}

void String::deleteString() {
	if (arr != nullptr) delete[] arr;
}

String::String() {
	arr = new(std::nothrow) char[1];
	if (arr == nullptr) {
		throw ("No memory for string!(default constructor)");
	}
	capacity = 1;
	size = 0;
}

String::String(const char* arr_, const int capacity_, const int size_) {
	copyStrings(arr_, capacity_, size_);
}

String::String(const String& other) {
	copyStrings(other.arr, other.capacity, other.size);
}

String& String::operator=(const String& other) {
	if (this != &other) {
		deleteString();
		copyStrings(other.arr, other.capacity, other.size);
	}
	return *this;
}

String& String::operator=(const char* str) {
	deleteString();
	int l = strlen(str);
	arr = new(std::nothrow) char[l + 1];
	if (arr == nullptr) {
		throw ("No memory for string!(operator=(const char*))");
	}
	for (int i = 0; i < l; i++) {
		arr[i] = str[i];
	}
	arr[l] = '\0';
	capacity = l + 1;
	size = l;
	return *this;
}

String::~String() {
	deleteString();
}

std::istream& operator>>(std::istream& in, String& str) { // vuvejdane simvol po simvol
	char letter;
	int br = 2;
	in.get(letter);
	while (letter != '\n') {
		char* tempArr = new(std::nothrow) char[br];
		if (tempArr == nullptr) {
			throw ("No memory for string!(operator>>)");
			return in;
		}
		if (br == 2) {
			tempArr[0] = letter;
			tempArr[1] = '\0';
		}
		else {
			strcpy(tempArr, str.arr);
			tempArr[br - 2] = letter;
			tempArr[br - 1] = '\0';
		}
		str.deleteString();
		str.arr = new(std::nothrow) char[br];
		if (str.arr == nullptr) {
			delete[] tempArr;
			throw ("No memory for string!(operator>>)");
			return in;
		}
		strcpy(str.arr, tempArr);
		br++;
		delete[] tempArr;
		
		in.get(letter);
	}
	str.capacity = br - 1;
	str.size = br - 2;
	return in;
}

std::ostream& operator<<(std::ostream& out, const String& str){
	int i = 0;
	while (str.arr[i]) {
		out << str.arr[i];
		i++;
	}
	return out;
}

std::ifstream& operator>>(std::ifstream& iFile, String& str) {
	char letter;
	int br = 2;
	iFile.get(letter);
	while (letter != '\n') {
		char* tempArr = new(std::nothrow) char[br];
		if (tempArr == nullptr) {
			throw ("No memory for string!(operator>>)");
			return iFile;
		}
		if (br == 2) {
			tempArr[0] = letter;
			tempArr[1] = '\0';
		}
		else {
			strcpy(tempArr, str.arr);
			tempArr[br - 2] = letter;
			tempArr[br - 1] = '\0';
		}
		str.deleteString();
		str.arr = new(std::nothrow) char[br];
		if (str.arr == nullptr) {
			delete[] tempArr;
			throw ("No memory for string!(operator>>)");
			return iFile;
		}
		strcpy(str.arr, tempArr);
		br++;
		delete[] tempArr;

		iFile.get(letter);
	}
	str.capacity = br - 1;
	str.size = br - 2;
	return iFile;
}

std::ofstream& operator<<(std::ofstream& oFile, const String& str) {
	int i = 0;
	while (str.arr[i]) {
		oFile << str.arr[i];
		i++;
	}
	return oFile;
}


char& String::operator[](const int i){ // dostup do element ot stringa
	if (i <= size && i >= 0) {
		return arr[i];
	}
}

int String::getCapacity() const{
	return capacity;
}

int String::getSize() const{
	return size;
}

void String::clear() {
	delete[] arr;
	arr = new(std::nothrow) char[1];
	if (arr == nullptr) {
		throw ("No memory for string!(String::clear())");
		return;
	}
	capacity = 1;
	size = 0;
}

bool String::operator==(const String& other) const{
	if (size != other.getSize()) return false;
	if (strcmp(arr, other.arr) == 0) return true;
	else return false;
}

bool String::operator==(const char* str) const {
	if (size != strlen(str)) return false;
	if (strcmp(arr, str) == 0) return true;
	else return false;
}

bool String::operator!=(const String& other) const {
	return !(*this == other);
}

bool String::operator!=(const char* str) const {
	return !(*this == str);
}

String& String::operator+=(const String& other) {
	if (size == 0) { // ako pruviyat string e prazen
		deleteString();
		int len = strlen(other.arr);
		arr = new(std::nothrow) char[len + 1];
		if (arr == nullptr) {
			throw ("No memory for string!(operator+=)");
		}
		for (int i = 0; i < len; i++) {
			arr[i] = other.arr[i];
		}
		arr[len] = '\0';
		size = len;
		capacity = len + 1;
	}
	else {
		int len1 = strlen(arr);
		int len2 = strlen(other.arr);
		char* tempArr = new(std::nothrow) char[len1 + 1];
		if (tempArr == nullptr) {
			throw ("No memory for string!(operator+=)");
		}
		strcpy(tempArr, arr);
		delete[] arr;
		arr = new(std::nothrow) char[len1 + len2 + 1];
		if (arr == nullptr) {
			delete[] tempArr;
			throw ("No memory for string!(operator+=)");
		}
		for (int i = 0; i < len1; i++) arr[i] = tempArr[i];
		int br = 0;
		for (int i = len1; i < len1 + len2; i++) {
			arr[i] = other.arr[br];
			br++;
		}
		arr[len1 + len2] = '\0';
		size += other.size;
		capacity += other.capacity;
		delete[] tempArr;
	}
	return *this;
}

String& String::to_string(const int num) {
	int br = 0, tempNum1 = num, tempNum2 = num;
	while (tempNum1 > 0) {
		tempNum1 /= 10;
		br++;
	}
	char* numStr;
	if (br == 0) {
		numStr = new(std::nothrow) char[br + 2];
		if (numStr == nullptr) {
			throw ("No memory for string!(String::to_string())");
		}
	}
	else numStr = new(std::nothrow) char[br + 1];
	if (numStr == nullptr) {
		throw ("No memory for string!(String::to_string())");
	}
	for (int i = 0; i < br; i++) {
		numStr[br - i - 1] = tempNum2 % 10 + '0';
		tempNum2 /= 10;
	}
	if (br == 0) {
		numStr[0] = '0';
		numStr[1] = '\0';
	}
	else numStr[br] = '\0';
	*this = numStr;
	delete[] numStr;
	return *this;
}