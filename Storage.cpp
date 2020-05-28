#include "Storage.h"

Storage::Storage() {}

Storage::Storage(const Vector<Section> sections_, const Vector<Log> logs_) {
	sections = sections_;
	logs = logs_;
}

void Storage::print() {
	if (sections.size() == 0) {
		std::wcout << "Storage is empty!" << std::endl;
		std::cout << std::endl;
		return;
	}
	std::cout << "Info about products in storage: " << std::endl;
	int n = sections.size();
	std::cout << "Amount of sections: " << n << std::endl;
	for (int i = 0; i < n; i++) sections[i].print();
}

void Storage::add(Vector<Section>& tempSections) { // pri dobavqne na product, dobavqm i spravka v logs!!!!
	Product tempProduct; // dobavyaniya product
	std::cout << "input the product's characteristics: " << std::endl;
	std::cin >> tempProduct;
	if (tempProduct.getComment().getSize() == 0) return;
	Date dateOfAdding; // data na dobavyane na producta kum sklada
	dateOfAdding = tempProduct.getDateOfReceipt();
	int n = tempSections.size();
	Vector<int> positions;
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (tempProduct.getName() == tempSections[i].getName() && tempSections[i].getShelves().size() < 50) {
			positions.add(i); // zapazva indeksa na sekciyata s ime kato na producta
			flag = true;
		}
	}
	if (!flag) { // ako ne e nameren producta 
		int numOfNewSections = tempProduct.getAmount() / 2500 + 1;
		addAndFillNewSections(numOfNewSections, tempProduct, tempSections, dateOfAdding); 
	}
	else { // ako e sreshtnat
		int n = positions.size(), j = 0;
		while(tempProduct.getAmount() > 0 && tempSections[positions[0]].getShelves().size() < 50){
			if (tempProduct == tempSections[positions[0]].getShelves()[j].getProductOnShelf()) { // ako producta, koito dobavyame, e == na tozi na rafta
				int addedQuantity;
				if (tempProduct.amount >= 50 - tempSections[positions[0]].shelves[j].productOnShelf.amount) {
					//dobavyanoto e >= ot svobodnoto myasto za rafta
					addedQuantity = 50 - tempSections[positions[0]].shelves[j].productOnShelf.amount;
				}
				else addedQuantity = tempProduct.amount; // dobavyanoto < ot svobodnoto myasto za rafta
				if (addedQuantity > 0) {
					tempSections[positions[0]].shelves[j].productOnShelf.amount += addedQuantity;
					bool isNotMet = true;
					int sizeOfDatesOfRecipe = tempSections[positions[0]].shelves[j].datesOfReceipt.size();
					for (int i = 0; i < sizeOfDatesOfRecipe; i++) {
						if (tempSections[positions[0]].shelves[j].datesOfReceipt[i] == tempProduct.getDateOfReceipt()) {
							tempSections[positions[0]].shelves[j].productsForEveryDate[i] += addedQuantity;
							isNotMet = false;
							break;
							//dobavyame kum vektora, koito sledi kolichestvoto product, vnesen na opredelena data
						}
					}
					if (isNotMet) { // datata na vnos e nova za vektora ot dati
						tempSections[positions[0]].shelves[j].datesOfReceipt.add(tempProduct.getDateOfReceipt());
						tempSections[positions[0]].shelves[j].productsForEveryDate.add(addedQuantity);
					}
					tempProduct.amount -= addedQuantity; // namalyame kolichestvoto na dobavyaniya product
					String message, op, numOfSection, numOfShelf, sh, nameOfPr, productStr, amount_, addedQStr;
					// postroyavame suobshtenieto za spravkata za dobavyane
					op = "operation: add | Section: ";
					numOfSection.to_string(positions[0]);
					sh = " | Shelf: ";
					numOfShelf.to_string(j);
					productStr = " | product: ";
					nameOfPr = tempProduct.getName();
					amount_ = " | amount: ";
					addedQStr.to_string(addedQuantity);
					message += op;
					message += numOfSection;
					message += sh;
					message += numOfShelf;
					message += productStr;
					message += nameOfPr;
					message += amount_;
					message += addedQStr;
					Log tempLog(dateOfAdding, message);
					logs.add(tempLog); // dobavyame kum vektora ot spravki
				}
			}
			if (j == tempSections[positions[0]].getShelves().size() - 1 && tempProduct.getAmount() > 0) {
				// ako sa svurshili raftovete za proverka, no sa < 50 i producta ne e svurshil(dobavyaniya)
				int amountOfNewShelves = tempProduct.getAmount() / 50 + 1; // kolichestvoto novi raftove, koito shte se dobavyat
				if (amountOfNewShelves <= 50 - tempSections[positions[0]].getShelves().size()) {
					// ako dobaveniya product se pobira v ostanaloto myasto v sekciyata
					
					for (int i = 0; i < amountOfNewShelves - 1; i++) {
						Shelf tempShelf;
						Product copyOfTempProduct(tempProduct.getName(), tempProduct.getDateOfExpiry(), tempProduct.getDateOfReceipt(), tempProduct.getManufacturerName(), tempProduct.getUnit(), 50, tempProduct.getComment());
						tempShelf.productOnShelf = copyOfTempProduct;
						tempShelf.datesOfReceipt.add(tempProduct.getDateOfReceipt());
						tempShelf.productsForEveryDate.add(50);
						tempSections[positions[0]].shelves.add(tempShelf);
						String message, op, numOfSection, numOfShelf, sh, nameOfPr, productStr, amount_, addedQStr;
						// postroyavame suobshtenieto za spravkata za dobavyane
						op = "operation: add | Section: ";
						numOfSection.to_string(positions[0]);
						sh = " | Shelf: ";
						numOfShelf.to_string(tempSections[positions[0]].getShelves().size());
						productStr = " | product: ";
						nameOfPr = tempProduct.getName();
						amount_ = " | amount: ";
						addedQStr.to_string(50);
						message += op;
						message += numOfSection;
						message += sh;
						message += numOfShelf;
						message += productStr;
						message += nameOfPr;
						message += amount_;
						message += addedQStr;
						Log tempLog(dateOfAdding, message);
						logs.add(tempLog);

					}
					tempProduct.amount %= 50;
					Shelf tempShelf;
					Product copyOfTempProduct(tempProduct.getName(), tempProduct.getDateOfExpiry(), tempProduct.getDateOfReceipt(), tempProduct.getManufacturerName(), tempProduct.getUnit(), tempProduct.getAmount(), tempProduct.getComment());
					tempShelf.productOnShelf = copyOfTempProduct;
					tempShelf.datesOfReceipt.add(tempProduct.getDateOfReceipt());
					tempShelf.productsForEveryDate.add(tempProduct.getAmount());
					tempSections[positions[0]].shelves.add(tempShelf); 
					String message, op, numOfSection, numOfShelf, sh, nameOfPr, productStr, amount_, addedQStr;
					// postroyavame suobshtenieto za spravkata za dobavyane
					op = "operation: add | Section: ";
					numOfSection.to_string(positions[0]);
					sh = " | Shelf: ";
					numOfShelf.to_string(tempSections[positions[0]].getShelves().size());
					productStr = " | product: ";
					nameOfPr = tempProduct.getName();
					amount_ = " | amount: ";
					addedQStr.to_string(tempProduct.getAmount());
					message += op;
					message += numOfSection;
					message += sh;
					message += numOfShelf;
					message += productStr;
					message += nameOfPr;
					message += amount_;
					message += addedQStr;
					Log tempLog(dateOfAdding, message);
					logs.add(tempLog);

					tempProduct.amount = 0;
				}
				else {
					//ako ne se pobira v tazi sekciya
					int shelvesToBeAdded = 50 - tempSections[positions[0]].getShelves().size();
					for (int i = 0; i < shelvesToBeAdded; i++) {
						Shelf tempShelf;
						Product copyOfTempProduct(tempProduct.getName(), tempProduct.getDateOfExpiry(), tempProduct.getDateOfReceipt(), tempProduct.getManufacturerName(), tempProduct.getUnit(), 50, tempProduct.getComment());
						tempShelf.productOnShelf = copyOfTempProduct;
						tempShelf.datesOfReceipt.add(tempProduct.getDateOfReceipt());
						tempShelf.productsForEveryDate.add(50);
						tempSections[positions[0]].shelves.add(tempShelf);
						String message, op, numOfSection, numOfShelf, sh, nameOfPr, productStr, amount_, addedQStr;
						// postroyavame suobshtenieto za spravkata za dobavyane
						op = "operation: add | Section: ";
						numOfSection.to_string(positions[0]);
						sh = " | Shelf: ";
						numOfShelf.to_string(tempSections[positions[0]].getShelves().size());
						productStr = " | product: ";
						nameOfPr = tempProduct.getName();
						amount_ = " | amount: ";
						addedQStr.to_string(50);
						message += op;
						message += numOfSection;
						message += sh;
						message += numOfShelf;
						message += productStr;
						message += nameOfPr;
						message += amount_;
						message += addedQStr;
						Log tempLog(dateOfAdding, message);
						logs.add(tempLog);
					}
					tempProduct.amount -= shelvesToBeAdded * 50;
				}

				break;
			}
			j++;
		}
		if (tempProduct.getAmount() > 0) { // ako sa svurshili sekciite v sklada, no vse oshte ima product za dobavyane
			int numOfNewSections = tempProduct.getAmount() / 2500 + 1;
			addAndFillNewSections(numOfNewSections, tempProduct, tempSections, dateOfAdding);
		}
	}
	std::cout << "Product added successfully!" << std::endl;
	std::cout << std::endl;
	//std::cin.ignore();
}

void Storage::remove(Vector<Section>& tempSections) { 
	String nameOfProduct;
	int amountOfProduct;
	std::cout << "product: ";
	std::cin >> nameOfProduct;
	std::cout << "\namount: ";
	std::cin >> amountOfProduct;
	if (amountOfProduct == 0) return;
	Date dateOfRemoving; // datata, na koyto se izvurshva premahvaneto
	std::cout << "Choose an option for the date that you are removing the products: " << std::endl;
	std::cout << "1: Enter a date that you want." << std::endl;
	std::cout << "2: Remove by current date." << std::endl;
	int option;      // izbira se dali datata za spravka da e tekushtata za kompiutura ili da e vuvedena ot nas
	std::cout << "Option(1 / 2): ";
	std::cin >> option;
	if (option == 1) {
		std::cout << "Enter date: ";
		std::cin >> dateOfRemoving;
	}
	else if (option == 2) dateOfRemoving = createCurrDate();
	else {
		std::cerr << "Incorrect option!" << std::endl;
		std::cout << std::endl;
		return;
	}

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
		std::cerr << "There's no such product in the storage!" << std::endl;
		std::cout << std::endl;
		//std::cin.ignore();
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
					// izvejdat se srokovete na godnost na nalichnite producti(koito sa sushtite kato premahvaniya)
				}
			}
		}
		int option; // izbira se opcicya dali da ima promyana po sklada ili ne
		std::cout << "\n1. I'll still remove the remaining products." << std::endl;
		std::cout << "2. Exit the command." << std::endl;
		std::cout << "Option(1 / 2): ";
		std::cin >> option;
		
		if (option == 1) {
			for (int i = 0; i < n; i++) {
				if (tempSections[i].getName() == nameOfProduct) {
					tempSections.removeAtIndex(i); // iztrivame sekciyata, ako e s producta, koito izvajdame
				}
			}
			String message, op, nameOfPr, removed;
			// postroyavame suobshtenieto za spravkata za izvajdane
			op = "operation: remove |  product: ";
			nameOfPr = nameOfProduct;
			removed = " | all removed from storage.";
			message += op;
			message += nameOfPr;
			message += removed;
			Log tempLog(dateOfRemoving, message);
			logs.add(tempLog);
			// dobavil sum v logs!!
			return;
		}
		else if (option == 2) return;
		else {
			std::cerr << "Incorrect option!" << std::endl;
			std::cout << std::endl;
			//std::cin.ignore();
			return;
		}
	}
	else { // nalichnite producti sa poveche, vadim po procedurata
		Vector<Date> expiryDates;

		for (int i = 0; i < n; i++) { // po vsichki sekcii
			if (tempSections[i].getName() == nameOfProduct) {
				int numOfShelves = tempSections[i].getShelves().size();
				for (int j = 0; j < numOfShelves; j++) { // za vsyaka sekciya raftovete
					expiryDates.add(tempSections[i].getShelves()[j].productOnShelf.getDateOfExpiry());
				} // dobavyame sroka na godnost na producta na vseki raft
			}
		}
		int sizeOfExpiryDates = expiryDates.size();
		for (int i = 0; i < sizeOfExpiryDates; i++) { // sortirame vremenniya vektor sus srokove na godnost
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
								// vudenoto e po - malko ot nalichnoto za rafta
								std::cout << "Section: " << tempSections[i].getName();
								std::cout << " | shelf: " << j << std::endl;
								std::cout << "Batch: " << tempSections[i].getShelves()[j].getProductOnShelf().getDateOfExpiry() << " ";
								std::cout << "Removed product: " << tempAmountOfRemovedProduct << " of " << tempSections[i].getShelves()[j].getProductOnShelf().getAmount() << std::endl << std::endl;
								tempSections[i].shelves[j].productOnShelf.amount -= tempAmountOfRemovedProduct;
								// premahvame ot ot producta na rafta dadenoto kolichestvo
								if (tempSections[i].shelves[j].productOnShelf.amount == 0) {
									tempSections[i].shelves.removeAtIndex(j);
								}
								//std::cin.ignore();
								String message, op, numOfSection, sh, numOfShelf, productStr, nameOfPr, amountStr, amount_;
								// postroyavame suobshtenieto za spravkata za dobavyane
								op = "operation: remove | Section: ";
								numOfSection.to_string(i);
								sh = " | Shelf: ";
								numOfShelf.to_string(j);
								productStr = " | product: ";
								nameOfPr = nameOfProduct;
								amountStr = " | amount: ";
								amount_.to_string(tempAmountOfRemovedProduct); // ne moje!!
								message += op;
								message += numOfSection;
								message += sh;
								message += numOfShelf;
								message += productStr;
								message += nameOfPr;
								message += amountStr;
								message += amount_;
								Log tempLog(dateOfRemoving, message);
								logs.add(tempLog);

								while (tempAmountOfRemovedProduct > 0) {
									// opravyame vektorite s dati za vnos i kolichestvo za vsyaka data
									int count = 0;
									if (tempSections[i].shelves[j].productsForEveryDate[count] > tempAmountOfRemovedProduct) {
										tempSections[i].shelves[j].productsForEveryDate[count] -= tempAmountOfRemovedProduct;
										tempAmountOfRemovedProduct = 0;
									}
									else if (tempSections[i].shelves[j].productsForEveryDate[count] == tempAmountOfRemovedProduct) {
										tempSections[i].shelves[j].productsForEveryDate.removeAtIndex(count);
										tempSections[i].shelves[j].datesOfReceipt.removeAtIndex(count);
										tempAmountOfRemovedProduct = 0;
									}
									else {
										tempAmountOfRemovedProduct -= tempSections[i].shelves[j].productsForEveryDate[count];
										tempSections[i].shelves[j].productsForEveryDate.removeAtIndex(count);
										tempSections[i].shelves[j].datesOfReceipt.removeAtIndex(count);
									}
									count++;
								}

								tempAmountOfRemovedProduct = 0;
								break; // mahaneto e prikliuchilo, spirame algorituma
							}
							else {
								//vudenoto e poveche ot nalichnoto za rafta
								std::cout << "Section: " << tempSections[i].getName();
								std::cout << " | shelf: " << j << std::endl;
								std::cout << "Batch: " << tempSections[i].getShelves()[j].getProductOnShelf().getDateOfExpiry() << " ";
								std::cout << "Removed product: " << tempSections[i].getShelves()[j].getProductOnShelf().getAmount() << " of " << tempSections[i].getShelves()[j].getProductOnShelf().getAmount() << std::endl << std::endl;
								tempAmountOfRemovedProduct -= tempSections[i].shelves[j].productOnShelf.amount;
								//std::cin.ignore();
								String message, op, numOfSection, sh, numOfShelf, productStr, nameOfPr, amountStr, amount_;
								// postroyavame suobshtenieto za spravkata za dobavyane
								op = "operation: remove | Section: ";
								numOfSection.to_string(i); 
								sh = " | Shelf: ";
								numOfShelf.to_string(j); 
								productStr = " | product: ";
								nameOfPr = nameOfProduct;
								amountStr = " | amount: all ";
								amount_.to_string(tempSections[i].getShelves()[j].getProductOnShelf().getAmount()); 
								message += op;
								message += numOfSection;
								message += sh;
								message += numOfShelf;
								message += productStr;
								message += nameOfPr;
								message += amountStr;
								message += amount_;
								Log tempLog(dateOfRemoving, message);
								logs.add(tempLog);

								tempSections[i].shelves.removeAtIndex(j);
							}
							br++; // preminavame kum sledvashtata partida
						}
					}
				}
			}
		} // skoba za while(amountOfProduct > 0)
		
		for (int i = 0; i < n; i++) { // premahvame sekciite s prazni raftove
			if (tempSections[i].getShelves().size() == 0) tempSections.removeAtIndex(i);
		}

	}
}

void Storage::log(const char* fromDate_, const char* toDate_) { 
	std::cout << "References to all changes in storage from " << fromDate_ << " to " << toDate_  << ": "<< std::endl << std::endl;
	int n = logs.size();
	Date fromDate, toDate;
	fromDate = fromDate_;
	toDate = toDate_;
	if (!(fromDate.isValid()) || !(toDate.isValid())) return;
	bool empty = true;
	for (int i = 0; i < n; i++) {
		if (fromDate <= logs[i].getDate() && toDate >= logs[i].getDate()) { // ako datata na spravkata e vuv vuvedeniya period
			std::cout << logs[i];
			empty = false;
		}
	}
	if (empty) std::cout << "Unfortunately, there's no changes in that range." << std::endl;
	std::cout << std::endl;
}

void Storage::clean(Vector<Section>& tempSections) { 
	std::cout << "Choose an option for the date that will be compared with the expiry date: " << std::endl;
	std::cout << "1: Enter a date that you want." << std::endl;
	std::cout << "2: Clear by current date." << std::endl;
	int option; // izbira se opciya za data za spravkata na razchistvane 
	bool cleanedSomething = false;
	std::cout << "Option(1 / 2): ";
	std::cin >> option;
	if (option == 1) {
		Date inputDate;
		std::cout << "Enter date: ";
		std::cin >> inputDate;
		if(!(inputDate.isValid())) return; 
		int n = tempSections.size();
		for (int i = 0; i < n; i++) { // cikul po vsichki sekcii
			int numOfShelves = tempSections[i].getShelves().size();
			for (int j = 0; j < numOfShelves; j++) { // obhojdane na rafotvete v sekciya
				if (inputDate > tempSections[i].getShelves()[j].getProductOnShelf().getDateOfExpiry()) { // ako producta e s iztekul srok
					tempSections[i].shelves.removeAtIndex(j);
					j--;
					numOfShelves--;
					cleanedSomething = true;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (tempSections[i].getShelves().size() == 0) tempSections.removeAtIndex(i);
		}
		String message;
		// postroyavame suobshtenieto za spravkata za dobavyane
		message = "operation: clean | Storage cleaned by specified date.";
		Log tempLog(inputDate, message);
		logs.add(tempLog);
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
					j--;
					numOfShelves--;
					cleanedSomething = true;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (tempSections[i].getShelves().size() == 0) tempSections.removeAtIndex(i);
		}
		String message;
		// postroyavame suobshtenieto za spravkata za dobavyane
		message = "operation: clean | Storage cleaned by specified date.";
		Log tempLog(currDate, message);
		logs.add(tempLog);
	}
	else {
		std::cerr << "Incorrect option!" << std::endl;
		std::cout << std::endl;
		return;
	}
	if (!cleanedSomething) {
		std::cout << "All products are in date. There was nothing to be cleaned." << std::endl;
		std::cout << std::endl;
		return;
	}
	std::cout << "Storage cleared successfully!" << std::endl;
	std::cout << std::endl;
}

void Storage::open(const char* dir, Vector<Section>& tempSections) {	// shte pazq i logovete vuv fail logs.txt
	std::ifstream iFile(dir, std::ios::in); // otvarya faila za productite
	if (!iFile) {                   // ako failut ne sushtestvuva, suzdavame nov s tova ime
		std::ofstream oFile(dir);
		int zero = 0;
		oFile << zero;
		oFile.close();
		iFile.open(dir, std::ios::in);
		std::cout << "There was no existing file with that name, but there was created a new empty one!" << std::endl;
		std::cout << std::endl;
	}
	iFile.seekg(0, std::ios::end);
	if (iFile.tellg() == 0) { // ako faila e prazen
		iFile.close();
		std::ofstream oFile(dir, std::ios::out);
		if (!oFile) {
			std::cerr << "Failed to open!" << std::endl;
			std::cout << std::endl;
			return;
		}
		int zero = 0;
		oFile << zero; // zapisva '0' 
		oFile.close();
		iFile.open(dir, std::ios::in);
		if (!iFile) {
			std::cerr << "Failed to open!" << std::endl;
			std::cout << std::endl;
		}

	}
	iFile.seekg(0, std::ios::beg);
	tempSections.clear(); // triya tempSections kato shte cheta nov fail
	int numOfSections;
	iFile >> numOfSections;
	for (int i = 0; i < numOfSections; i++) { // chetem ot faila dannite za sklada
		Section tempSect;
		tempSect.load(iFile);
		//iFile.ignore();
		tempSections.add(tempSect);
	}

	sections = tempSections;
	std::wcout << "File opened successfully!" << std::endl;
	std::cout << std::endl;
}

void Storage::close(Vector<Section>& tempSections) const { 
	if (tempSections.size() == 0) { // ako nyama nishto za iztrivane
		std::cerr << "File is already closed or the opened file is empty!" << std::endl;
		return;
	}
	tempSections.clear();
	std::cout << "File closed!" << std::endl;
	std::cout << std::endl;
}

void Storage::save(const char* dir, Vector<Section>& tempSections) const { 
	int n = tempSections.size();
	
	std::ofstream oFile(dir, std::ios::trunc);
	if (!oFile) {
		std::cerr << "Failed to open!" << std::endl;
		std::cout << std::endl;
		return;
	}
	for (int i = 0; i < n; i++) {
		if (tempSections[i].getShelves().size() == 0) tempSections.removeAtIndex(i);
	}
	oFile << n << std::endl;
	for (int i = 0; i < n; i++) { // zapazva dannite za sklada v tekushto otvoreniya fail
		tempSections[i].save(oFile); 
		oFile << std::endl;
	}
	oFile.close();
	std::cout << "Changes saved successfully!" << std::endl;
	std::cout << std::endl;
}

void Storage::saveas(const char* newDir, Vector<Section>& tempSections) const{ // shte pazq i logovete vuv fail logs.txt
	int n = tempSections.size();

	std::ofstream oFile(newDir, std::ios::trunc);
	if (!oFile) {
		std::cerr << "Failed to open!" << std::endl;
		std::cout << std::endl;
		return;
	}
	for (int i = 0; i < n; i++) {
		if (tempSections[i].getShelves().size() == 0) tempSections.removeAtIndex(i);
	}
	oFile << n << std::endl;
	for (int i = 0; i < n; i++) { // zapazva dannite za sklada v noviya fail
		tempSections[i].save(oFile);
		oFile << std::endl;
	}
	oFile.close();
	std::cout << "Changes saved successfully in " << newDir << "!" << std::endl;
	std::cout << std::endl;
}

void Storage::help() const {
	std::cout << "The following commands are supported: " << std::endl;
	std::cout << "open <file>           opens <file>" << std::endl;
	std::cout << "close                 closes currently opened file" << std::endl;
	std::cout << "save <file>           saves updates in currently opened file" << std::endl;
	std::cout << "saveas                saves updates in <file>" << std::endl;
	std::cout << "exit                  exits the program" << std::endl;
	std::cout << "print                 prints info about the available products in storage" << std::endl;
	std::cout << "add                   adds a new product to storage" << std::endl;
	std::cout << "remove                removes a product from storage" << std::endl;
	std::cout << "log <from> <to>       outputs a reference to all updates in the period <from> - <to> (dates)" << std::endl;
	std::cout << "clean                 cleans up the storage from all expired products" << std::endl;
	std::cout << std::endl;
}

void Storage::fillShelves(int amount_, const Product& tempProduct, Vector<Shelf>& tempShelves) {
	// suzdava i zapulva amount_ na broi raftove, kato gi dobavya v tempShelves
	for (int j = 0; j < amount_; j++) {
		Shelf tempShelf;
		Product copyOfTempProduct(tempProduct.getName(), tempProduct.getDateOfExpiry(), tempProduct.getDateOfReceipt(), tempProduct.getManufacturerName(), tempProduct.getUnit(), 50, tempProduct.getComment());
		tempShelf.productOnShelf = copyOfTempProduct;
		tempShelf.datesOfReceipt.add(tempProduct.getDateOfReceipt());
		tempShelf.productsForEveryDate.add(50);

		tempShelves.add(tempShelf);
	}
}

void Storage::addAndFillNewSections(int numOfNewSections, const Product& tempProduct, Vector<Section>& tempSections, const Date& date) {
	// dobavya i zapulva novi sekcii s dadeniya product, kato gi dobavya v tempSections
	numOfNewSections = tempProduct.getAmount() / 2500 + 1;
	for (int i = 0; i < numOfNewSections - 1; i++) { // pulnim celi sekcii (bez poslednata)
		Vector<Shelf> tempShelves;
		fillShelves(50, tempProduct, tempShelves);

		String nameOfSection = tempProduct.getName();
		Section newSection(nameOfSection, tempShelves);
		tempSections.add(newSection);
		String message, op, numOfSection, filled;
		// postroyavame suobshtenieto za spravkata za dobavyane
		op = "operation: adding | Section: ";
		numOfSection.to_string(tempSections.size()); 
		filled = " | filled with ";
		message += op;
		message += numOfSection;
		message += filled;
		message += tempProduct.getName();
		Log tempLog(date, message);
		logs.add(tempLog);
	}
	int amountForNewSection = tempProduct.getAmount() % 2500;
	int brOfShelves = amountForNewSection / 50;
	Vector<Shelf> tempShelves;
	fillShelves(amountForNewSection / 50, tempProduct, tempShelves);
	if (brOfShelves > 0) {
		String message, op, numOfSection, brOfShelvesStr, sh;
		// postroyavame suobshtenieto za spravkata za dobavyane
		op = "operation: adding | Section: ";
		numOfSection.to_string(tempSections.size()); 
		sh = " | number of shelves filled: ";
		brOfShelvesStr.to_string(brOfShelves); 
		message += op;
		message += numOfSection;
		message += sh;
		message += brOfShelvesStr;
		Log tempLog(date, message);
		logs.add(tempLog);
	}
	Shelf tempShelf;
	Product copyOfTempProduct(tempProduct.getName(), tempProduct.getDateOfExpiry(), tempProduct.getDateOfReceipt(), tempProduct.getManufacturerName(), tempProduct.getUnit(), amountForNewSection % 50, tempProduct.getComment());
	tempShelf.productOnShelf = copyOfTempProduct;
	tempShelf.datesOfReceipt.add(tempProduct.getDateOfReceipt());
	tempShelf.productsForEveryDate.add(amountForNewSection % 50);

	tempShelves.add(tempShelf);

	String nameOfSection = tempProduct.getName();
	Section newSection(nameOfSection, tempShelves);
	tempSections.add(newSection);
	String message, op, numOfSection, numOfShelf, sh, amount_, amountStr, nameOfPr, productStr;
	// postroyavame suobshtenieto za spravkata za dobavyane
	op = "operation: adding | Section: ";
	numOfSection.to_string(tempSections.size()); 
	sh = " | Shelf: ";
	numOfShelf.to_string(tempSections[tempSections.size() - 1].getShelves().size());
	productStr = " | product: ";
	nameOfPr = tempProduct.getName();
	amountStr = " | amount: ";
	amount_.to_string(amountForNewSection % 50);
	message += op;
	message += numOfSection;
	message += sh;
	message += numOfShelf;
	message += productStr;
	message += nameOfPr;
	message += amountStr;
	message += amount_;
	Log tempLog(date, message);
	logs.add(tempLog);
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