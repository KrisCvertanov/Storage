#include "Section.h"


Section::Section() {}

Section::Section(const String name_, const Vector<Shelf> shelves_) {
	name = name_;
	shelves = shelves_;
}

Section::Section(const char* name_, const Vector<Shelf> shelves_) {
	name = name_;
	shelves = shelves_;
}

void Section::add(const Product& newProduct) {

}

const String& Section::getName() const{
	return name;
}

const Vector<Shelf>& Section::getShelves() const {
	return shelves;
}

void Section::setName(const String name_) {
	name = name_;
}

void Section::print() {
	std::cout << "Section name: " << name << std::endl;
	int n = shelves.size();
	for (int i = 0; i < n; i++) {
		std::cout << "Number of shelf: " << i << std::endl;
		shelves[i].print();
	}
	std::cout << std::endl;
}

void Section::save(std::ofstream& oFile) {
	oFile << name << std::endl;
	int n = shelves.size();
	oFile << n << " ";
	for (int j = 0; j < n; j++) {
		shelves[j].save(oFile); 
	}
}

void Section::load(std::ifstream& iFile) {
	iFile.ignore();
	iFile >> name;
	int n;
	iFile >> n;
	iFile.ignore();
	for (int j = 0; j < n; j++) {
		Shelf tempShelf;
		tempShelf.load(iFile);
		shelves.add(tempShelf); 
	}
}