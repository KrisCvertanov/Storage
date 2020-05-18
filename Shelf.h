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

	void setProduct(const Product);
public:
	Shelf();
	Shelf(const Product, const Vector<Date>, const Vector<int>);

	void add(int, const Date&);
	void print();
	const Product& getProductOnShelf() const ;
	//const bool* getSpots();

	friend class Storage;
};

#endif // !SHELF_H_
