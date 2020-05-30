#ifndef SHELF_H_
#define SHELF_H_
#include "Product.h"
#include "vector.hpp"

class Storage;

class Shelf {
private:
	Product productOnShelf;
	Vector<Date> datesOfReceipt;
	Vector<int> productsForEveryDate;

	void setProduct(const Product&); // mutator za producta na rafta
public:
	Shelf();
	Shelf(const Product&, const Vector<Date>&, const Vector<int>&);

	void add(int, const Date&); // dobavya producti kum rafta
	void print() const ;				// izvejda informaciya za producta na rafta
	const Product& getProductOnShelf() const ;	// funkciya za dostup
	void save(std::ofstream&); // funkciya za zapazvane na informaciya v izhoden failov potok
	void load(std::ifstream&); // funkciya za izvlichane na informaciya ot vhoden failov potok

	friend class Storage; // klas sklad e priyatel za raft
};

#endif // !SHELF_H_
