#include "Storage.h"

Storage::Storage() {}

Storage::Storage(const Vector<Section> sections_, const Vector<Log> logs_) {
	sections = sections_;
	logs = logs_;
}

void Storage::print() {
	std::cout << "Info about products in storage: " << std::endl;
	int n = sections.size();
	for (int i = 0; i < n; i++) sections[i].print();
}

void Storage::add(Vector<Section> tempSections) { // pri dobavqne na product, dobavqm i spravka v logs!!!!
	Product tempProduct;
	std::cout << "input the product's characteristics: " << std::endl;
	std::cin >> tempProduct;
	if (tempProduct.getComment().getSize() == 0) return;
	Date dateOfAdding;
	std::cout << "Choose an option for the date that you are adding the product: " << std::endl;
	std::cout << "1: Enter a date that you want." << std::endl;
	std::cout << "2: Add by current date." << std::endl;
	int option;
	std::cout << "Option(1 / 2): ";
	std::cin >> option;

	if (option == 1) std::cin >> dateOfAdding;
	else if (option == 2) dateOfAdding = createCurrDate();
	else {
		std::cout << "Incorrect option!" << std::endl;
		return;
	}

	int n = tempSections.size();
	Vector<int> positions;
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (tempProduct.getName() == tempSections[i].getName() && tempSections[i].getShelves().size() < 50) {
			positions.add(i);
			flag = true;
		}
	}
	if (!flag) { // ako ne e nameren producta 
		int numOfNewSections = tempProduct.getAmount() / 2500 + 1;
		addAndFillNewSections(numOfNewSections, tempProduct, tempSections);
		String logStr, fp;
		fp = "operation: add | new sections filled: ";
		char num = numOfNewSections + '0';



		// dobavyam v logs!!
	}
	else { // ako e sreshtnat
		int n = positions.size();
		int amountOfProduct = tempProduct.getAmount();
		for (int i = 0; i < n; i++) { // nai - vunshen cikul e po - sekciite s tova ime(kato na producta)
			int	numOfShelves = tempSections[positions[i]].getShelves().size();
			for (int j = 0; j < numOfShelves; j++) { // cikul za dadenata sekciq(minava prez raftovete)
				if (tempProduct == tempSections[positions[i]].getShelves()[j].getProductOnShelf()) { // ako producta, koito dobavyame, e kato tozi na rafta
					int addedQuantity = 50 - tempSections[positions[i]].shelves[j].productOnShelf.amount;
					if (addedQuantity > 0) {
						tempSections[positions[i]].shelves[j].productOnShelf.amount += addedQuantity;
						tempSections[positions[i]].shelves[j].datesOfReceipt.add(tempProduct.getDateOfReceipt());
						tempSections[positions[i]].shelves[j].productsForEveryDate.add(addedQuantity);
						amountOfProduct -= addedQuantity;
						// dobavyam v logs!!
					}
				}
			}
		}
		if (amountOfProduct > 0) { // ako sa svurshili sekciite v sklada
			int numOfNewSections = amountOfProduct / 2500 + 1;
			addAndFillNewSections(numOfNewSections, tempProduct, tempSections);
			// dobavyam v logs!!
		}
	}	
}

void Storage::remove(Vector<Section> tempSections) { // pri izvajdane na product, dobavqm i spravka v logs
	String nameOfProduct;
	int amountOfProduct;
	std::cout << "product: ";
	std::cin >> nameOfProduct;
	std::cout << "\namount: ";
	std::cin >> amountOfProduct;
	if (amountOfProduct == 0) return;
	int amountOfAvailableProducts = 0, n = tempSections.size();
	for (int i = 0; i < n; i++) {
		if (tempSections[i].getName() == nameOfProduct) {
			int numOfShelves = tempSections[i].getShelves().size();
			for (int j = 0; j < numOfShelves; j++) {
				amountOfAvailableProducts += tempSections[i].getShelves()[j].getProductOnShelf().getAmount();
			} // sumirame cyaloto nalichno kolichesvo product
		}
	}
	if (amountOfAvailableProducts == 0) { // ako go nyama producta
		std::cout << "There's no such product in the storage!" << std::endl;
		return;
	}
	if (amountOfAvailableProducts < amountOfProduct) { // ako shte mahame poveche, otkolkoto ima
		std::cout << "The inputed amount is more then the available." << std::endl;
		std::cout << "Available amount of the product: " << amountOfAvailableProducts << std::endl;
		std::cout << "Batches: ";
		for (int i = 0; i < n; i++) {
			if (tempSections[i].getName() == nameOfProduct) {
				int numOfShelves = tempSections[i].getShelves().size();
				for (int j = 0; j < numOfShelves; j++) {
					std::cout << tempSections[i].getShelves()[j].getProductOnShelf().getDateOfExpiry() << ", ";
				}
			}
		}
		int option;
		std::cout << "\n1. I'll still remove the remaining products." << std::endl;
		std::cout << "2. Exit the command." << std::endl;
		std::cout << "Option(1 / 2): ";
		std::cin >> option;
		do {
			if (option == 1) {
				for (int i = 0; i < n; i++) {
					if (tempSections[i].getName() == nameOfProduct) {
						int numOfShelves = tempSections[i].getShelves().size();
						for (int j = 0; j < numOfShelves; j++) {
							tempSections[i].shelves.removeAtIndex(j);
						}
					}
				}
				// dobavyam v logs!!(vsichki producti sa mahnati ot sklada)
				return;
			}
			else if (option == 2) return;

			else std::cout << "Incorrect option!" << std::endl;

			std::cout << "Option(1 / 2): ";
			std::cin >> option;
		} while (option < 0 && option > 2);

	}
	else { // nalichnite producti sa poveche, vadim po procedurata
		Vector<Date> expiryDates;

		for (int i = 0; i < n; i++) { // po vsichki sekcii
			if (tempSections[i].getName() == nameOfProduct) {
				int numOfShelves = tempSections[i].getShelves().size();
				for (int j = 0; j < numOfShelves; j++) { // za vsyaka sekciya raftovete
					expiryDates.add(tempSections[i].getShelves()[j].productOnShelf.getDateOfExpiry());
				} // dobavyame srokovete na godnost na producta na vseki raft
			}
		}
		int sizeOfExpiryDates = expiryDates.size();
		for (int i = 0; i < sizeOfExpiryDates; i++) { // metod na mehurcheto(sortirame vektora s dati)
			for (int j = i + 1; j < sizeOfExpiryDates; j++) {
				if (expiryDates[i] > expiryDates[j]) {
					Date tempDate = expiryDates[i];
					expiryDates[i] = expiryDates[j];
					expiryDates[j] = tempDate;
				}
			}
		}
		//veche sme sortirali datite vuv vuzhodyasht red
		int tempAmountOfRemovedProduct = amountOfProduct, br=0;
		while (tempAmountOfRemovedProduct > 0) { // dokato ne mahnem kolichestvoto vuveden product
			for (int i = 0; i < n; i++) { // po vsichki sekcii
				if (tempAmountOfRemovedProduct <= 0) break;
				if (tempSections[i].getName() == nameOfProduct) { // ako sekciyata e za tozi product
					int numOfShelves = tempSections[i].getShelves().size();
					for (int j = 0; j < numOfShelves; j++) { // po vsichki raftove v sekciya
						if (expiryDates[br] == tempSections[i].getShelves()[j].getProductOnShelf().getDateOfExpiry()) {
							// znaem che ot tozi raft shte vadim producti
							if (tempAmountOfRemovedProduct <= tempSections[i].shelves[j].productOnShelf.amount) {
								// vadenoto e po - malko ot nalichnoto za rafta
								tempSections[i].shelves[j].productOnShelf.amount -= tempAmountOfRemovedProduct;
								std::cout << "Section: " << tempSections[i].getName();
								std::cout << " | shelf: " << j << std::endl;
								std::cout << "Batch: " << tempSections[i].getShelves()[j].getProductOnShelf().getDateOfExpiry() << " ";
								std::cout << "Removed product: " << tempAmountOfRemovedProduct << " of " << tempSections[i].getShelves()[j].getProductOnShelf().getAmount() << std::endl << std::endl;
								if (tempSections[i].shelves[j].productOnShelf.amount == 0) {
									tempSections[i].shelves.removeAtIndex(j);
								}
								tempAmountOfRemovedProduct = 0;
								//dobavyam v logs!!
								break; // mahaneto e prikliuchilo, spirame algorituma
							}
							else {
								//vadenoto e poveche ot nalichnoto za rafta
								tempAmountOfRemovedProduct -= tempSections[i].shelves[j].productOnShelf.amount;
								std::cout << "Section: " << tempSections[i].getName();
								std::cout << " | shelf: " << j << std::endl;
								std::cout << "Batch: " << tempSections[i].getShelves()[j].getProductOnShelf().getDateOfExpiry() << " ";
								std::cout << "Removed product: " << tempSections[i].getShelves()[j].getProductOnShelf().getAmount() << " of " << tempSections[i].getShelves()[j].getProductOnShelf().getAmount() << std::endl << std::endl;
								tempSections[i].shelves.removeAtIndex(j);
								// dobavyam v logs!!
							}
							br++; // preminavame kum sledvashtata partida
						}
					}
				}
			}
		}

	}
}

void Storage::log(const char* fromDate, const char* toDate) { 

}

void Storage::clean(Vector<Section> tempSections) { // pri razchistvane, dobavqm i spravka v logs
	std::cout << "Choose an option for the date that will be compared with the expiry date: " << std::endl;
	std::cout << "1: Enter a date that you want." << std::endl;
	std::cout << "2: Clear by current date." << std::endl;
	int option;
	std::cout << "Option(1 / 2): ";
	std::cin >> option;
	if (option == 1) {
		Date inputDate;
		std::cout << "Enter date: ";
		std::cin >> inputDate;
		if (inputDate.getDay()[0] == '0' && inputDate.getDay()[1] == '0') return;
		int n = tempSections.size();
		for (int i = 0; i < n; i++) { // cikul po vsichki sekcii
			int numOfShelves = tempSections[i].getShelves().size();
			for (int j = 0; j < numOfShelves; j++) { // obhojdane na rafotvete v sekciya
				if (inputDate > tempSections[i].getShelves()[j].getProductOnShelf().getDateOfExpiry()) { // ako producta e s iztekul srok
					tempSections[i].shelves.removeAtIndex(j);
					// dobavyam v logs!!
				}
			}
		}
	}
	else if (option == 2) {
		Date currDate;
		currDate = createCurrDate(); // suzdavame tekushtata data

		int n = tempSections.size();
		for (int i = 0; i < n; i++) { // cikul po vsichki sekcii
			int numOfShelves = tempSections[i].getShelves().size();
			for (int j = 0; j < numOfShelves; j++) { // obhojdane na rafotvete v sekciya
				if (currDate > tempSections[i].getShelves()[j].getProductOnShelf().getDateOfExpiry()) { // ako producta e s iztekul srok
					tempSections[i].shelves.removeAtIndex(j);
					// dobavyam v logs!!
				}
			}
		}
	}
	else {
		std::cout << "Incorrect option!" << std::endl;
		return;
	}
	std::cout << "Storage cleared successfully!" << std::endl;
}

void Storage::open(const char* dir, Vector<Section>& tempSections) {	// shte pazq i logovete vuv fail logs.txt

}

void Storage::close(Vector<Section>& tempSections) const { 
	if (tempSections.size() == 0) {
		std::cout << "File is already closed. Cannot use this command!" << std::endl;
		return;
	}
	tempSections.clear();
	std::cout << "File closed!" << std::endl;
	std::cout << std::endl;
}

void Storage::save(const char* dir, Vector<Section>& tempSections) const { // shte pazq i logovete vuv fail logs.txt

}

void Storage::saveas(const char* newDir, Vector<Section>& tempSections) const{ // shte pazq i logovete vuv fail logs.txt

}

void Storage::help() const {
	std::cout << "The following commands are supported: " << std::endl;
	std::cout << "open <file>           opens <file>" << std::endl;
	std::cout << "close                 closes currently opened file" << std::endl;
	std::cout << "save <file>           saves updates in currently opened file" << std::endl;
	std::cout << "saveas                saves updates in <file>" << std::endl;
	std::cout << "exit                  exits the programm" << std::endl;
	std::cout << "print                 prints info about the available products in storage" << std::endl;
	std::cout << "add                   adds a new product to storage" << std::endl;
	std::cout << "remove                removes a product from storage" << std::endl;
	std::cout << "log <from> <to>       outputs a reference to all updates in the period <from> - <to> (dates)" << std::endl;
	std::cout << "clean                 cleans up the storage from all expired products" << std::endl;
	std::cout << std::endl;
}

void Storage::fillShelves(int amount_, const Product& tempProduct, Vector<Shelf>& tempShelves) {
	for (int j = 0; j < amount_; j++) {
		Shelf tempShelf;
		Product copyOfTempProduct(tempProduct.getName(), tempProduct.getDateOfExpiry(), tempProduct.getDateOfReceipt(), tempProduct.getManufacturerName(), tempProduct.getUnit(), 50, tempProduct.getComment());
		tempShelf.productOnShelf = copyOfTempProduct;
		tempShelf.datesOfReceipt.add(tempProduct.getDateOfReceipt());
		tempShelf.productsForEveryDate.add(50);

		tempShelves.add(tempShelf);
	}
}

void Storage::addAndFillNewSections(int numOfNewSections, const Product& tempProduct, Vector<Section>& tempSections) {
	numOfNewSections = tempProduct.getAmount() / 2500 + 1;
	for (int i = 0; i < numOfNewSections - 1; i++) { // pulnim celi sekcii
		Vector<Shelf> tempShelves;
		fillShelves(50, tempProduct, tempShelves);

		String nameOfSection = tempProduct.getName();
		Section newSection(nameOfSection, tempShelves);
		tempSections.add(newSection);
		// dobavyam v logs!!
	}
	int amountForNewSection = tempProduct.getAmount() % 2500;
	Vector<Shelf> tempShelves;
	fillShelves(amountForNewSection / 50, tempProduct, tempShelves);

	Shelf tempShelf;
	Product copyOfTempProduct(tempProduct.getName(), tempProduct.getDateOfExpiry(), tempProduct.getDateOfReceipt(), tempProduct.getManufacturerName(), tempProduct.getUnit(), amountForNewSection % 50, tempProduct.getComment());
	tempShelf.productOnShelf = copyOfTempProduct;
	tempShelf.datesOfReceipt.add(tempProduct.getDateOfReceipt());
	tempShelf.productsForEveryDate.add(amountForNewSection % 50);

	tempShelves.add(tempShelf);

	String nameOfSection = tempProduct.getName();
	Section newSection(nameOfSection, tempShelves);
	tempSections.add(newSection);
}

const Date& Storage::createCurrDate() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int year = 1900 + timePtr->tm_year;
	int	intMonth = 1 + timePtr->tm_mon;
	int	intDay = timePtr->tm_mday;
	char month[3];
	char day[3];
	if (intMonth < 10) {
		month[0] = '0';
	}
	else {
		month[0] = '1';
	}
	month[1] = intMonth % 10 + '0';
	month[2] = '\0';
	if (intDay < 10) {
		day[0] = '0';
	}
	else {
		day[0] = intDay / 10 + '0';
	}
	day[1] = intDay % 10 + '0';
	day[2] = '\0';
	Date currDate(year, month, day);
	return currDate;
}