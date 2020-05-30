#ifndef SECTION_H_
#define SECTION_H_
#include "vector.hpp"
#include "Shelf.h"

class Storage;

class Section {
private:
	String name;
	Vector<Shelf> shelves;

	void setName(const String&); // mutator za imeto
public:
	Section();
	Section(const String&, const Vector<Shelf>&);
	Section(const char*, const Vector<Shelf>&);

	void print() const;			  // izvejda informaciya za sekciyata
	const String& getName() const;          // 
	const Vector<Shelf>& getShelves() const;// funkcii za dostup
	void save(std::ofstream&); // funkciya za zapazvane na informaciya v izhoden failov potok
	void load(std::ifstream&); // funkciya za izvlichane na informaciya ot vhoden failov potok

	friend class Storage; // klas sklad e priyatel za sekciya

};

#endif // !SECTION_H_

