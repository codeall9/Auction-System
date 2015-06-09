#ifndef my_Simple_Auction_System_H
#include "Simple Auction System.h"
#endif
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Keyboard.h"
using namespace std;

AuctionAccount::AuctionAccount(string newAccountName, string newPassWord, string newUserName,
	string newIDnumber, string newEmail, string newPhoneNumber, string newAddress)
	:Account(newAccountName, newPassWord), LoggedIn(false)
{
	strncpy(UserName, newUserName.c_str(), 24);
	strncpy(IDnumber, newIDnumber.c_str(), 11);
	strncpy(Email, newEmail.c_str(), 24);
	strncpy(PhoneNumber, newPhoneNumber.c_str(), 11);
	strncpy(Address, newAddress.c_str(), 38);
}

AuctionAccount::AuctionAccount(const AuctionAccount &copy):Account(copy)
{
	strncpy(UserName, copy.UserName, 24);
	strncpy(IDnumber, copy.IDnumber, 11);
	strncpy(Email, copy.Email, 24);
	strncpy(PhoneNumber, copy.PhoneNumber, 11);
	strncpy(Address, copy.Address, 38);
	LoggedIn = copy.LoggedIn;
}

AuctionAccount::~AuctionAccount()
{}

void AuctionAccount::SignOut()
{
	this->LoggedIn = false;
}

void AuctionAccount::setAccountName(string newAccountName)
{
	if (this->LoggedIn) {
		strncpy(this->AccountName, newAccountName.c_str(), 24);
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

void AuctionAccount::setPassWord(string newPassword)
{
	if (this->LoggedIn) {
		strncpy(this->PassWord, newPassword.c_str(), 24);
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

void AuctionAccount::setUserName(string newUserName)
{
	if (this->LoggedIn) {
		strncpy(UserName, newUserName.c_str(), 24);
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

void AuctionAccount::setIDnumber(string newIDnumber)//check
{
	if (this->LoggedIn) {
		strncpy(IDnumber, newIDnumber.c_str(), 11);
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

void AuctionAccount::setEmail(string newEmail)
{
	if (this->LoggedIn) {
		strncpy(Email, newEmail.c_str(), 24);
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

void AuctionAccount::setPhoneNumber(string newPhoneNumber)//check
{
	if (this->LoggedIn) {
		strncpy(PhoneNumber, newPhoneNumber.c_str(), 11);
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

void AuctionAccount::setAddress(string newAddress)
{
	if (this->LoggedIn) {
		strncpy(Address, newAddress.c_str(), 38);
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

bool AuctionAccount::getLoginStatus() const
{
	return this->LoggedIn;
}

string AuctionAccount::getAccountName() const
{
	if (this->LoggedIn) {
		return this->AccountName;
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

string AuctionAccount::getPassWord() const
{
	if (this->LoggedIn) {
		return this->PassWord;
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

string AuctionAccount::getUserName() const
{
	return this->UserName;
}

string AuctionAccount::getIDnumber() const
{
	if (this->LoggedIn) {
		return this->IDnumber;
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

string AuctionAccount::getEmail() const
{
	return this->Email;
}

string AuctionAccount::getPhoneNumber() const
{
	if (this->LoggedIn) {
		return this->PhoneNumber;
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}

string AuctionAccount::getAddress() const
{
	if (this->LoggedIn) {
		return this->Address;
	}
	else {
		logic_error Offline("User doesn't login");
		throw Offline;
	}
}
////////////////////////////////////////////////////////////////////////////////////
AuctionData::AuctionData(string newUserFilePath, string newCommoditiesFilePath)
:AccountFilePath(newUserFilePath), CommoditiesFilePath(newCommoditiesFilePath)
{
	this->LoadData(AccountFilePath, AuctionAccounts);
	this->LoadData(CommoditiesFilePath, Commodities);
}

AuctionData::AuctionData(const AuctionData &copy)
:AuctionAccounts(copy.AuctionAccounts), Commodities(copy.Commodities){}

AuctionData::~AuctionData()
{
	this->SaveData(AccountFilePath, AuctionAccounts);
	this->SaveData(CommoditiesFilePath, Commodities);
	this->FreeData(AuctionAccounts);
	this->FreeData(Commodities);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
AuctionSYS::AuctionSYS(string UserFilePath, string CommoditiesFilePath)
:AuctionData(UserFilePath, CommoditiesFilePath){}

AuctionSYS::AuctionSYS(const AuctionSYS &copy)
: AuctionData(copy){}

AuctionSYS::~AuctionSYS()
{}

void AuctionSYS::SignUp()//use try{...} catch {input overflow}
{
	char tmpAccountName[24], tmpPassword[24], tmpUserName[24], tmpIDnumber[11], tmpEmail[24], tmpPhoneNumber[11], tmpAddress[38];
	bool Flag;
	int count;
	do{
		Flag = false;
		cin.sync();
		cout << "\nAccountName :";
		cin >> tmpAccountName;
		for (Acc_iter Iter = this->AuctionAccounts.begin(), End = this->AuctionAccounts.end(); Iter < End; ++Iter) {
			if (strncmp((*Iter)->AccountName, tmpAccountName, 24) == 0) {
				cout << "Sorry, \"" << tmpAccountName << "\" has been used...\nPlease change another name...";
				Flag = true;
				break;
			}
		}
	} while (Flag);

	do {
		count = 0;
		cout << "\nPassword (len > 2) :";
		cin.sync();
		while ((*(tmpPassword + count++) = cin.get()) != '\n' && count < 24) {
		}
		*(tmpPassword + count - 1) = '\0';
		if (count < 4) {
			cout << "Your input is wrong~";
			Flag = true;
		}
		else {
			Flag = false;
		}
	} while (Flag);

	cout << "\nUserName :";
	cin.sync();
	cin.getline(tmpUserName, 24, '\n');

	do {
		cout << "\nIDnumber :";
		cin.sync();
		cin.getline(tmpIDnumber, 11, '\n');
		if (!authenticateIDnumber(tmpIDnumber)) {
			cout << "Wrong ID number";
			Flag = true;
		}
		else {
			Flag = false;
		}

	} while (Flag);

	cout << "\nEmail :";
	cin.sync();
	cin.getline(tmpEmail, 24, '\n');

	do {
		count = 0;
		cout << "\nPhoneNumber :";
		cin.sync();
		while ((*(tmpPhoneNumber + count++) = cin.get()) != '\n') {
		}
		*(tmpPhoneNumber + count - 1) = '\0';
		if (count != 11) {
			cout << "Your PhoneNumber is wrong~";
			Flag = true;
		}
		else {
			Flag = false;
		}
	} while (Flag);

	cout << "\nAddress :";
	cin.sync();
	cin.getline(tmpAddress, 38, '\n');

	AuctionAccount *newAccount = new AuctionAccount(tmpAccountName, tmpPassword, tmpUserName, tmpIDnumber, tmpEmail, tmpPhoneNumber, tmpAddress);
	this->AuctionAccounts.push_back(newAccount);
	cout << "Sign up success~";
	return;
}

AuctionAccount* AuctionSYS::SignIn()
{
	char tmpAccountName[24], tmpPassword[24];
	cin.sync();
	cout << "\nPlease input your account name :";
	cin >> tmpAccountName;

	cout << "\nPlease input your password :";
	cin.sync();
	cin.getline(tmpPassword, 24, '\n');// need ******
	//authenticateUser
	Acc_iter Iter = this->AuctionAccounts.begin(), End = this->AuctionAccounts.end();
	for (; Iter < End; ++Iter) {
		if (strncmp((*Iter)->AccountName, tmpAccountName, 24) == 0) {
			if (strncmp((*Iter)->PassWord, tmpPassword, 24) == 0) {
				if ((*Iter)->LoggedIn) {
					logic_error AlreadySignIn("\nUser has alread sign in...");
					throw AlreadySignIn;
				}
				cout << "\nLogin success~~\n\nWelcome, " << (*Iter)->UserName;
				(*Iter)->LoggedIn = true;
				return *Iter;
			}
			else {
				return 0;
			}
		}
	}
	return 0;
}

bool AuctionSYS::authenticateUser(const string& inputAccoutName, const string& inputPassWord)//if not friend, need to use get func || if set func was protected, should friend
{
	for (Acc_iter Iter = this->AuctionAccounts.begin(), End = this->AuctionAccounts.end(); Iter < End; ++Iter) {
		if (strncmp((*Iter)->AccountName, inputAccoutName.c_str(), 24) == 0) {
			if (strncmp((*Iter)->PassWord, inputPassWord.c_str(), 24) == 0) {
				return true;
			}
			//else throw password wrong
		}
	}
	return false;//throw account name wrong
}

bool AuctionSYS::PostItem(const AuctionAccount *Sys_User)//class account is friend//throw if can't postitem
{
	char newProductName[24];
	unsigned int newPrice, newQuantity;

	if (Sys_User == NULL || !Sys_User->getLoginStatus()) {
		logic_error noLogin("\nPlease Login first...");
		throw noLogin;
	}
	else if (!authenticateUser(Sys_User->AccountName, Sys_User->PassWord)) {
		logic_error notMyUser("\nUser of this system does not exist...");
		throw notMyUser;
	}

	cout << "\nPlease input your product name you want to sell :";
	cin.sync();
	cin.getline(newProductName, 24, '\n');

	cout << "Please input the price of the product :";
	cin.sync();
	cin >> newPrice;

	cout << "Please input the quantity of the product :";
	cin.sync();
	cin >> newQuantity;

	Commodity *newItem = new Commodity(newProductName, Sys_User->UserName, "", newPrice, newQuantity);
	this->Commodities.push_back(newItem);
	cout << "Your commodity  has already uploaded\n";

	return true;
}

bool AuctionSYS::BuyItem(const AuctionAccount* Sys_User, int CommodityID, int Num)//class account is friend
{
	Com_iter Head = Commodities.begin(), theCommodity;
	int Range = Commodities.end() - Head;

	if (CommodityID > Range || CommodityID <= 0) {
		out_of_range wrongNum("\nCommodity doesn't exist...");
		throw wrongNum;
	}
	else if (Sys_User == NULL || !Sys_User->getLoginStatus()) {
		logic_error noLogin("\nPlease Login first~");
		throw noLogin;
	}
	else if (!authenticateUser(Sys_User->AccountName, Sys_User->PassWord)) {
		logic_error notMyUser("\nUser of this system does not exist");
		throw notMyUser;
	}

	theCommodity = Head + CommodityID - 1;

	if ((*theCommodity)->getQuantity() < Num) {
		out_of_range wrongNum("\nQuantity is not enough or the commodity has already been sold...");
		throw wrongNum;
	}
	else {
		(*theCommodity)->setLastBuyerName(Sys_User->UserName);
		(*theCommodity)->PlusQuantity(-Num);
	}
	return true;
}

void AuctionSYS::CommodityList()
{
	Com_iter Item_iter = this->Commodities.begin(), End = this->Commodities.end();
	cout << "\nProductID   " << left << setw(20) << "ProductName" << " Price     Quantity  Seller     LastBuyer\n\n";
	for (int i = 1; Item_iter < End; ++Item_iter, ++i) {
		cout << right << setw(5) << i << setw(7) << " " << left << setw(21) << (*Item_iter)->getProductName() << setw(14)
			<< (*Item_iter)->getPrize() << setw(6) << (*Item_iter)->getQuantity() << setw(11) << (*Item_iter)->getOwnerName()
			<< setw(11) << (*Item_iter)->getLastBuyerName() << endl;
	}
}

void AuctionSYS::UserDetail(const AuctionAccount* User)
{
	Com_iter Item_iter = this->Commodities.begin(), Com_End = this->Commodities.end();
	cout << "\nUserName: " << User->UserName << "\nIDnumber: " << User->IDnumber << "\nEmail: "
		<< User->Email << "\nPhoneNumber: " << User->PhoneNumber << "\nAddress: " << User->Address
		<< endl;

}

void AuctionSYS::DeleteItem(const AuctionAccount *User)
{

	vector<Com_iter> UserItems_iter;
	int count;
	char inChar;
	do {
		count = 0;
		cout << "\nAuction Item:\nNo.  ProductName\tPrice\t Quantity\tLastBuyer\n";
		int i = 0;
		for (Com_iter Item_iter = this->Commodities.begin(), Com_End = this->Commodities.end(); Item_iter + i < Com_End; ++i) {
			if (strncmp(User->UserName, Item_iter[i]->getOwnerName().c_str(), 24) == 0) {
				UserItems_iter.push_back(Item_iter + i);
				cout << ++count << ")   " << Item_iter[i]->getProductName() << "\t\t" << Item_iter[i]->getPrize()
					<< "\t    " << Item_iter[i]->getQuantity() << "\t\t" << Item_iter[i]->getLastBuyerName() << endl;
			}
		}
		cout << "\n\nInput the number you want to delete (0 to back):";
		inChar = get_Input('0', count + '0');
		if (inChar == '0') {
			break;
		}
		else {
			this->Commodities.erase(UserItems_iter[inChar - '1']);
			cout << "\nCancel success~~~\n";
			UserItems_iter.clear();
		}
	} while (true);

}

unsigned int AuctionSYS::StatsOnlineUsers()
{
	unsigned int count = 0;
	for (Acc_iter Iter = this->AuctionAccounts.begin(), End = this->AuctionAccounts.end(); Iter < End; ++Iter) {
		if ((*Iter)->LoggedIn) {
			++count;
		}
	}
	return count;
}

unsigned int AuctionSYS::StatsUser()
{
	return this->AuctionAccounts.size();
}

bool authenticateIDnumber(char* newID)//for taiwan... but not sure//doen't check len
{
	int LocalID, Total = 0;
	int IDcode[26] = { 10, 11, 12, 13, 14, 15, 16, 17, 34, 18, 19, 20, 21,
		22, 35, 23, 24, 25, 26, 27, 28, 29, 32, 30, 31, 33 };

	if (*newID >= 'A' && *newID <= 'Z'){
		LocalID = *newID - 'A';
	}
	else /*if (*newID >= 'a' && *newID <= 'z')*/{
		//LocalID = *newID - 'a';
		return false;
	}

	Total = IDcode[LocalID] / 10 + IDcode[LocalID] % 10 * 9;
	for (int i = 1; i <= 8; i++){
		Total += (*(newID + i) - '0') * (9 - i);
	}

	return ((10 - (Total % 10)) == (*(newID + 9) - '0')) ? true : false;
}
