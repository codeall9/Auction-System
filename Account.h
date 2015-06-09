
#pragma once
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include <cstring>
#include <string>
using std::string;
using std::strncpy;

class Account
{
public:
	Account(string = "", string = "");
	Account(const Account &Copy);
	virtual ~Account();
	virtual string getAccountName() const;
	virtual string getPassWord() const;
	// should protected set func?
	virtual void setAccountName(string);
	virtual void setPassWord(string);
protected:
	char AccountName[24];
	char PassWord[24];
};

inline Account::Account(string newName, string newPassWord)
{
	strncpy(AccountName, newName.c_str(), 24);
	strncpy(PassWord, newPassWord.c_str(), 24);
}

inline Account::Account(const Account &copy)
{
	strncpy(AccountName, copy.AccountName, 24);
	strncpy(PassWord, copy.PassWord, 24);
}

inline Account::~Account(){}//

inline string Account::getAccountName() const
{
	return this->AccountName;
}

inline string Account::getPassWord() const
{
	return this->PassWord;
}

inline void Account::setAccountName(string newName)
{
	strncpy(this->AccountName, newName.c_str(), 24);
}

inline void Account::setPassWord(string newPassWord)
{
	strncpy(this->PassWord, newPassWord.c_str(), 24);
}

#endif
