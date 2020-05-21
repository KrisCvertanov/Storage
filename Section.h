#ifndef SECTION_H_
#define SECTION_H_
#include "vector.hpp"
#include "Shelf.h"

class Storage;

class Section {
private:
	String name;
	Vector<Shelf> shelves;

	void setName(const String);
public:
	Section();
	Section(const String, const Vector<Shelf>);
	Section(const char*, const Vector<Shelf>);

	void add(const Product&);
	void print();
	const String& getName() const;
	const Vector<Shelf>& getShelves() const;
	void save(std::ofstream&);
	void load(std::ifstream&);

	friend class Storage;

};

#endif // !SECTION_H_

