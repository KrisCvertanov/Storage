#ifndef PRODUCT_H_
#define PRODUCT_H_
#include "Date.h"
#include "String.h"

class Storage;
class Shelf;

class Product {
private:
	String name;
	Date dateOfExpiry;
	Date dateOfReceipt;
	String manufacturerName;
	String unit;
	int amount;
	String comment;

public:
	Product();
	Product(const String&, const Date&, const Date&, const String&, const String&, const int, const String&);
	Product(const char*, const char*, const char*, const char*, const char*, const int, const char*);
	const String& getName() const;            //
	const Date& getDateOfExpiry() const;	  //
	const Date& getDateOfReceipt() const;	  //
	const String& getManufacturerName() const;// funkcii za dostup
	const String& getUnit() const;			  //
	const int getAmount() const;			  //
	const String& getComment() const;		  //
	bool operator==(const Product&);
	friend std::ifstream& operator>>(std::ifstream&, Product&);      //
	friend std::ofstream& operator<<(std::ofstream&, const Product&);// operator za vhod i izhod
	friend std::istream& operator>>(std::istream&, Product&);		 //
	friend std::ostream& operator<<(std::ostream&, const Product&);	 //
	void save(std::ofstream&); // funkciya za zapazvane na informaciya v izhoden failov potok 
	void load(std::ifstream&); // funkciya za izvlichane na informaciya ot vhoden failov potok 

	friend class Shelf;  // klasovete raft i sklad sa priyateli za product
	friend class Storage;//

};
	
#endif // !PRODUCT_H_
