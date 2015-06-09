
#ifndef _COMMODITY_H
#define _COMMODITY_H

#include <cstring>
#include <string>
using std::string;
using std::strncpy;

class Commodity
{
public:
	Commodity(string = "", string = "", string = "", unsigned int = 0, unsigned int = 0);
	Commodity(const Commodity &Copy);
	virtual ~Commodity();
	//get function
	string getProductName() const;
	string getOwnerName() const;
	string getLastBuyerName() const;
	unsigned int getPrize() const;
	unsigned int getQuantity() const;
	//set function
	void setProductName(string);
	void setOwnerName(string);
	void setLastBuyerName(string);
	void setPrize(unsigned int);
	void setQuantity(unsigned int);
	//
	Commodity & operator--();
	Commodity operator--(int);
	Commodity & operator++();
	Commodity operator++(int);
	//
	void PlusQuantity(int);
protected:
	char ProductName[24];
	char OwnerName[24];
	char LastBuyerName[24];
	unsigned int Price;
	unsigned int Quantity;
};

inline Commodity::Commodity(string productName, string ownerName, string lastbuyerName, unsigned int prize, unsigned int num)
:Price(prize), Quantity(num)
{
	strncpy(ProductName, productName.c_str(), 24);
	strncpy(OwnerName, ownerName.c_str(), 24);
	strncpy(LastBuyerName, lastbuyerName.c_str(), 24);
}

inline Commodity::Commodity(const Commodity &Copy)
:Price(Copy.Price), Quantity(Copy.Quantity)
{
	strncpy(ProductName, Copy.ProductName, 24);
	strncpy(OwnerName, Copy.OwnerName, 24);
	strncpy(LastBuyerName, Copy.LastBuyerName, 24);
}

inline Commodity::~Commodity(){}

inline void Commodity::setProductName(string newName)
{
	strncpy(ProductName, newName.c_str(), 24);
}

inline void Commodity::setOwnerName(string newName)
{
	strncpy(OwnerName, newName.c_str(), 24);
}

inline void Commodity::setLastBuyerName(string newName)
{
	strncpy(LastBuyerName, newName.c_str(), 24);
}

inline void Commodity::setPrize(unsigned int newPrize)
{
	this->Price = newPrize;
}

inline void Commodity::setQuantity(unsigned int newNum)
{
	this->Quantity = newNum;
}

inline string Commodity::getProductName() const
{
	return this->ProductName;
}

inline string Commodity::getOwnerName() const
{
	return this->OwnerName;
}

inline string Commodity::getLastBuyerName() const
{
	return this->LastBuyerName;
}

inline unsigned int Commodity::getPrize() const
{
	return this->Price;
}

inline unsigned int Commodity::getQuantity() const
{
	return this->Quantity;
}

inline Commodity & Commodity::operator--()
{
	if (this->Quantity > 0) {
		--this->Quantity;
	}
	return *this;
}

inline Commodity & Commodity::operator++()
{
	if (this->Quantity < 4294967295) {
		++this->Quantity;
	}
	return *this;
}

inline Commodity Commodity::operator--(int)
{
	Commodity tmp(*this);
	if (this->Quantity > 0) {
		--this->Quantity;
	}
	return tmp;
}

inline Commodity Commodity::operator++(int)
{
	Commodity tmp(*this);
	if (this->Quantity < 4294967295) {
		++this->Quantity;
	}
	return tmp;
}

inline void Commodity::PlusQuantity(int Val)
{
	if ((this->Quantity < 4294967295) && (this->Quantity > 0)) {
		this->Quantity += Val;
	}
}
#endif
