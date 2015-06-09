#ifndef my_Simple_Auction_System_H
#define my_Simple_Auction_System_H

#include <iostream>
#include "Account.h"
#include "Commodity.h"
#include <vector>
#include <fstream>
#include <cstdlib>
using std::vector;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::cerr;
using std::exit;

struct Menu
{
	Menu& operator<<(string Input)
	{
		display.append(Input);
		return *this;
	}
	Menu& operator<<(const Menu& InputMenu)
	{
		display.append(InputMenu.display);
		return *this;
	}
	string display = "";
};

class AuctionSYS;

class AuctionAccount :public Account
{
	friend class AuctionSYS;
public:
	AuctionAccount(string = "", string = "", string = "", string = "", string = "", string = "", string = "");
	AuctionAccount(const AuctionAccount &copy);
	virtual ~AuctionAccount();
	void SignOut();
	//getfunction
	virtual string getAccountName() const;//overloading
	virtual string getPassWord() const;//overloading
	virtual string getUserName() const;
	virtual string getIDnumber() const;
	virtual string getEmail() const;
	virtual string getPhoneNumber() const;
	virtual string getAddress() const;
	bool getLoginStatus() const;
	//setfunction (maybe protected)
	virtual void setAccountName(string);//overloading
	virtual void setPassWord(string);//overloading
	virtual void setUserName(string);
	virtual void setIDnumber(string);
	virtual void setEmail(string);
	virtual void setPhoneNumber(string);
	virtual void setAddress(string);

protected:
	char UserName[24];
	char IDnumber[11];
	char Email[24];
	char PhoneNumber[11];
	char Address[38];
	bool LoggedIn;//write more 1 bytes to file
};
////////////////////////////////////////////////////////////////////////////////
class AuctionData
{
public:
	AuctionData(string newUserFilePath = "", string newCommoditiesFilePath = "");
	AuctionData(const AuctionData &copy);
	virtual ~AuctionData();
protected:
	typedef vector<AuctionAccount*>::iterator Acc_iter;
	typedef vector<Commodity*>::iterator Com_iter;
	template<class SaveType> void SaveData(string FilePath, vector<SaveType*> &Data);
	template<class LoadType> void LoadData(string FilePath, vector<LoadType*> &Data);
	//template<class PushType> void PushData(PushType* Data, vector<PushType*> &Member);no need if no sort Data 
	template<class DataType> void FreeData(vector<DataType*> &Data);
	string AccountFilePath;
	string CommoditiesFilePath;
	//vector<AuctionAccount*> AuctionAccounts[26];
	//vector<Commodity*> Commodities[26];
	vector<AuctionAccount*> AuctionAccounts;
	vector<Commodity*> Commodities;
};
////////////////////////////////////////////////////////////////////////////////////
class AuctionSYS:public AuctionData
{
public:
	AuctionSYS(string UserFilePath, string CommoditiesFilePath);
	AuctionSYS(const AuctionSYS &copy);
	~AuctionSYS();

	virtual bool authenticateUser(const string&, const string&);
	virtual AuctionAccount* SignIn();//Login	
	virtual void SignUp();//Register
	virtual bool PostItem(const AuctionAccount* Sys_User);//return int?? or throw?
	virtual bool BuyItem(const AuctionAccount* Sys_User, int CommodityID, int Num);
	virtual void CommodityList();//need more format
	virtual void UserDetail(const AuctionAccount *User);
	virtual void DeleteItem(const AuctionAccount *User);
	unsigned int StatsOnlineUsers();// return the number of online users
	unsigned int StatsUser();//return the number of users
protected:
	//AuctionAdmin SuperAdmin
};

bool authenticateIDnumber(char *);
///////////////////////////////////////////////////////////////////////////////////
template<class SaveType>
inline void AuctionData::SaveData(string FilePath, vector<SaveType*> &Data)
{
	ofstream outFile(FilePath.c_str(), ios::binary | ios::trunc);
	if (!outFile.is_open()) {
		cerr << "\nFile could not be opened\n";
		exit(1);
	}
	outFile.seekp(0, ios::beg);
	typename vector<SaveType*>::iterator D_iter = Data.begin(), End = Data.end();

	for (int i = 0; (D_iter + i) < End; ++i) {///////
		outFile.write(reinterpret_cast< char *>(Data[i]), sizeof(SaveType));
	}

	outFile.close();
}

template<class LoadType>
inline void AuctionData::LoadData(string FilePath, vector<LoadType*> &Data)
{
	ifstream inFile(FilePath.c_str(), ios::binary);
	if (!inFile.is_open()) {
		cerr << "\nFile could not be opened\n";
		exit(1);
	}
	inFile.seekg(0, ios::beg);
	
	LoadType *DataInfo, tmpData;
	while (inFile.read(reinterpret_cast<char *>(&tmpData), sizeof(LoadType))) {
		DataInfo = new LoadType(tmpData);
		Data.push_back(DataInfo);
	}
	inFile.close();
}

template<class DataType> inline void AuctionData::FreeData(vector<DataType*> &Data)
{
	typename vector<DataType*>::iterator D_iter = Data.begin(), End = Data.end();
	for (; D_iter < End; ++D_iter) {
		delete *D_iter;
	}
}

#endif
