#ifndef STORAGE_H_
#define STORAGE_H_
#define _CRT_SECURE_NO_WARNINGS
#include "Section.h"
#include "Log.h";

class Storage {
private:
	Vector<Section> sections;
	Vector<Log> logs;	// promenite po sklada(logs) se sledyat ot startiraneto na programata do prikliuchvaneto i

	void fillShelves(int, const Product&, Vector<Shelf>&); // zapulva raftove s daden product
	void addAndFillNewSections(int, const Product&, Vector<Section>&, const Date&); // dobavya i zapulva sekcii s daden product
	const Date& createCurrDate() const; // suzdava data, koyato e tekushtata za kompiutura
public:
	Storage();
	Storage(const Vector<Section>&, const Vector<Log>&);

	void print() const;									// izvejda invormaciya za nalichnite producti v sklada
	void add(Vector<Section>&);							// dobavya nov product v dialogov rejim
	void remove(Vector<Section>&);						// premahva product v dialogov rejim
	void log(const char* , const char*) const;			// izvejda spravka za promenite po nalichnostta na sklada v dadeniya period
	void clean(Vector<Section>&);						// razchistva sklada ot producti s iztekul srok
	void open(const char*, Vector<Section>&);			// otvarya i prochita informaciya ot fail
	void close(Vector<Section>&) const;					// zatvarya fail i izchistva prochetenoto(promenyanoto)
	void save(const char*, Vector<Section>&) const;		// zapazva novite danni za sklada v tekushto otvoreniya fail
	void saveas(const char*, Vector<Section>&) const;	// zapazva novite danni za sklada v nov, posochen ot nas fail
	void help() const;									// izvejda informaciya za poddurjanite comandi
	

};

#endif // !STORAGE_H_

