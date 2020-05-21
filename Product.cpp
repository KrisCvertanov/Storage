#include "Product.h"

Product::Product() {
	amount = 0;
}

Product::Product(const String name_, const Date dateOfExpiry_, const Date dateOfReceipt_, const String manufacturerName_, const String unit_, const int amount_, const String comment_) {
	name = name_;
	dateOfExpiry = dateOfExpiry_;
	dateOfReceipt = dateOfReceipt_;
	manufacturerName = manufacturerName_;
	unit = unit_;
	amount = amount_;
	comment = comment_;
}

Product::Product(const char* name_, const char* dateOfExpiry_, const char* dateOfReceipt_, const char* manufacturerName_, const char* unit_, const int amount_, const char* comment_) {
	name = name_;
	dateOfExpiry = dateOfExpiry_;
	dateOfReceipt = dateOfReceipt_;
	manufacturerName = manufacturerName_;
	unit = unit_;
	amount = amount_;
	comment = comment_;
}

const String& Product::getName() const {
	return name;
}

const Date& Product::getDateOfExpiry() const {
	return dateOfExpiry;
}

const Date& Product::getDateOfReceipt() const {
	return dateOfReceipt;
}

const String& Product::getManufacturerName() const {
	return manufacturerName;
}

const String& Product::getUnit() const {
	return unit;
}

const int Product::getAmount() const {
	return amount;
}

const String& Product::getComment() const {
	return comment;
}

bool Product::operator==(const Product& other) {
	if (name == other.name && dateOfExpiry == other.dateOfExpiry && manufacturerName == other.manufacturerName && unit == other.unit) {
		return true;
	}
	return false;
}

std::ifstream& operator>>(std::ifstream& iFile, Product& product) {
	iFile >> product.name;
	iFile >> product.dateOfExpiry;
	iFile.ignore();
	iFile >> product.manufacturerName;
	iFile >> product.unit;
	iFile >> product.amount; 
	iFile.ignore();
	iFile >> product.comment;
	for (int i = 0; i < 18; i++) iFile.ignore(); // tova e za datite na vnos
	return iFile;
}

std::ofstream& operator<<(std::ofstream& oFile, const Product& product) {
	oFile << product.name << std::endl;
	oFile << product.dateOfExpiry << std::endl;
	oFile << product.manufacturerName << std::endl;
	oFile << product.unit << std::endl;
	oFile << product.amount << std::endl;
	oFile << product.comment << std::endl;
	oFile << "Dates of receipt: "; 
	return oFile;
}

std::istream& operator>>(std::istream& in, Product& product) {
	std::cout << "name: ";
	in >> product.name;
	int n = product.name.getSize();
	for (int i = 0; i < n; i++) {
		if (product.name[i] < 'a' && product.name[i] > 'z' && product.name[i] < 'A' && product.name[i] > 'Z' && product.name[i] < '0' && product.name[i] > '9') {
			std::cout << "Invalid name!" << std::endl;
			return in;
		}
	}
	std::cout << "date of expiry: ";
	in >> product.dateOfExpiry;
	if (product.dateOfExpiry.getDay()[0] == '0' && product.dateOfExpiry.getDay()[1] == '0') return in;
	std::cout << "date of receipt: ";
	in >> product.dateOfReceipt;
	if (product.dateOfReceipt.getDay()[0] == '0' && product.dateOfReceipt.getDay()[1] == '0') return in;
	in.ignore();
	std::cout << "name of manufacturer: ";
	in >> product.manufacturerName;
	std::cout << "unit(kg/l): ";
	in >> product.unit;
	if (product.unit != "kg" && product.unit != "l") {
		std::cout << "Invalid unit!" << std::endl;
		return in;
	}
	std::cout << "amount: ";
	char validAmount[10];
	in.getline(validAmount, 10);
	n = strlen(validAmount);
	bool flag = true;
	for (int i = 0; i < n; i++) {
		if (validAmount[0] == '0') {
			flag = false;
			break;
		}
		if (validAmount[i] < '0' && validAmount[i]>'9') {
			flag = false;
			break;
		}
	}
	if (!flag) {
		std::cout << "Invalid amount!" << std::endl;
		return in;
	}
	product.amount = atoi(validAmount);
	//in.ignore();
	std::cout << "short comment: ";
	in >> product.comment;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Product& product) {
	std::cout << std::endl;
	std::cout << "name: ";
	out << product.name << std::endl;
	std::cout << "date of expiry: ";
	out << product.dateOfExpiry << std::endl;
	std::cout << "name of manufacturer: ";
	out << product.manufacturerName << std::endl;
	std::cout << "unit(kg/l): ";
	out << product.unit << std::endl;
	std::cout << "amount: ";
	out << product.amount << std::endl;
	std::cout << "short comment: ";
	out << product.comment << std::endl;
	std::cout << std::endl;
	return out;
}

void Product::save(std::ofstream& oFile) {
	oFile << *this;
}

void Product::load(std::ifstream& iFile) {
	iFile >> *this;
}
