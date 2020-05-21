#include "Shelf.h"

Shelf::Shelf() {}

Shelf::Shelf(const Product product_, const Vector<Date> datesOfReceipt_, const Vector<int> productsForEveryDate_) {
	productOnShelf = product_;
	datesOfReceipt = datesOfReceipt_;
	productsForEveryDate = productsForEveryDate_;
}

const Product& Shelf::getProductOnShelf() const{
	return productOnShelf;
}

void Shelf::add(int amount_, const Date& date_) {
	if (productOnShelf.amount + amount_ > 50) {
		std::cout << "Too much products to add on shelf!" << std::endl;
		return;
	}
	productOnShelf.amount += amount_;
	int n = datesOfReceipt.size();
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (datesOfReceipt[i] == date_) {
			flag = true;
			productsForEveryDate[i] += amount_;
			break;
		}
	}
	if (!flag) {
		datesOfReceipt.add(date_);
		productsForEveryDate.add(amount_);
	}
	
}

void Shelf::print() {
	std::cout << "product: " << productOnShelf.getName() << std::endl;
	std::cout << "date of expiry: " << productOnShelf.getDateOfExpiry() << std::endl;
	std::cout << "dates of receipt: ";
	int n = datesOfReceipt.size();
	int br = 0;
	for (int i = 0; i < n; i++) {
		std::cout << datesOfReceipt[i];
		if (br < n - 1) std::cout << " | ";
		br++;
	}
	std::cout << std::endl;
	std::cout << "manufacturer: " << productOnShelf.getManufacturerName() << std::endl;
	std::cout << "unit: " << productOnShelf.getUnit() << std::endl;
	std::cout << "amount: " << productOnShelf.getAmount() << std::endl;
	std::cout << "comment: " << productOnShelf.getComment() << std::endl;

}

void Shelf::setProduct(const Product otherProduct) {
	productOnShelf = otherProduct;
}

void Shelf::save(std::ofstream& oFile) {
	productOnShelf.save(oFile);
	int sizeOfDatesOfReceipt = datesOfReceipt.size();
	oFile << sizeOfDatesOfReceipt << std::endl;
	for (int i = 0; i < sizeOfDatesOfReceipt; i++) {
		oFile << datesOfReceipt[i] << " " << productsForEveryDate[i] << std::endl;
	}
}

void Shelf::load(std::ifstream& iFile) {
	productOnShelf.load(iFile);
	int sizeOfDatesOfReceipt;
	iFile >> sizeOfDatesOfReceipt;
	for (int i = 0; i < sizeOfDatesOfReceipt; i++) {
		Date tempDate;
		iFile >> tempDate;
		datesOfReceipt.add(tempDate);
		iFile.ignore();
		int tempNum;
		iFile >> tempNum;
		productsForEveryDate.add(tempNum);
		iFile.ignore();
	}
}