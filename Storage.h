#ifndef STORAGE_H_
#define STORAGE_H_
#define _CRT_SECURE_NO_WARNINGS
#include "Section.h"
#include "Log.h";

class Storage {
private:
	Vector<Section> sections;
	Vector<Log> logs;	// promenite po sklada(logs) se sledyat ot startiraneto na programata do prikliuchvaneto i

	void fillShelves(int, const Product&, Vector<Shelf>&);
	void addAndFillNewSections(int, const Product&, Vector<Section>&, const Date&);
	const Date& createCurrDate();
public:
	Storage();
	Storage(const Vector<Section>, const Vector<Log>);

	void print();
	void add(Vector<Section>&);
	void remove(Vector<Section>&);
	void log(const char* , const char*);
	void clean(Vector<Section>&);
	void open(const char*, Vector<Section>&);
	void close(Vector<Section>&) const;
	void save(const char*, Vector<Section>&) const;
	void saveas(const char*, Vector<Section>&) const;
	void help() const;
	

};

#endif // !STORAGE_H_

