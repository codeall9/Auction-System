#ifndef my_Simple_Auction_System_H
#include "Simple Auction System.h"
#endif
#include "Keyboard.h"
#include <iomanip>
#include <cstdlib>
#include <stdexcept>

using namespace std;

void ViewItem(AuctionSYS &mySYS, const AuctionAccount* User);
void EditAccount(AuctionSYS &mySYS, AuctionAccount* User);

typedef vector<AuctionAccount*>::iterator User_iter;
vector<AuctionAccount *> OnlineUsers;//

int main()
{
	enum Action{ Login = 1, Register, PostItem, ViewCommodities, ManageAccount, SignOut, End, SwitchAccount };
	AuctionSYS mySYS("members.dat","commodities.dat");
	AuctionAccount *User = 0;
	Menu GuestMenu, UserMenu, UserSignOutMenu;
	Action GuestAction[4] = { Login, Register, ViewCommodities, End};
	Action UserAction[6] = {SwitchAccount, ManageAccount, PostItem, ViewCommodities, SignOut, End};
	Action UserSignOutAction[4] = { SwitchAccount, Register, ViewCommodities, End };
	//default
	GuestMenu << "\nPlease select the action you want to perform:"
			<< "\n(1)Login\n(2)Register\n(3)View the website commodities\n(4)End\n";
	UserMenu << "\nPlease select the action you want to perform:"
		<< "\n(1)Switch Account\n(2)Manage Account\n(3)Post Auction Items\n(4)View the website commodities\n(5)Sign Out\n(6)End\n";

	Menu *sysMenu = &GuestMenu;
	Action *sysAction = GuestAction;
	char inChar, ChRange = '4';
	bool Block = false;
	User_iter Users_Iter, End_iter;
	cout << "Welcome ";
	do {
		cout << sysMenu->display;
		cout << "\nChoose :";
		inChar = get_Input('1', ChRange);
		try {
			switch (sysAction[inChar - '1'])
			{
			case SwitchAccount:	{
				Users_Iter = OnlineUsers.begin(), End_iter = OnlineUsers.end();
				/////////////////////////////////////////////////////////////
				char inChar;
				cout << "Online Users :\n";
				int i = 0;
				for (; (Users_Iter + i) < End_iter; ++i) {
					cout << (i + 1) << ") " << Users_Iter[i]->getAccountName() << endl;
				}
				cout << i + 1 << ") Login for new user\nChoose (0 to back): ";
				cin.sync();
				inChar = get_Input('0', i + '1');
				//////////////////////////////////////////////////////////////
				if (inChar == '0') {
					break;
				}
				else if(inChar < i + '1') {
					char inPassword[24];
					cout << "\nPlease input your password :";
					cin.sync();
					cin.getline(inPassword, 24, '\n');
					if (mySYS.authenticateUser(Users_Iter[inChar - '1']->getAccountName(), inPassword)) {
						AuctionAccount *tmpUser;
						tmpUser = Users_Iter[inChar - '1'];
						Users_Iter[inChar - '1'] = *(End_iter - 1);
						*(End_iter - 1) = tmpUser;
						User = tmpUser;
						cout << "\nSwitch success, Welcome back, " << User->getUserName();
						sysMenu = &UserMenu;
						sysAction = UserAction;
						ChRange = '6';
						break;
					}
					else {
						runtime_error AuthenticateFail("\nWrong password...");
						throw AuthenticateFail;
					}

				}

			}
			case Login:
				User = mySYS.SignIn();
				if (User == NULL) {
					runtime_error NullUser("\nUser doesn't exist or the password does't correct...");
					throw NullUser;
				}
				else {
					OnlineUsers.push_back(User);
					sysMenu = &UserMenu;
					sysAction = UserAction;
					ChRange = '6';
				}
				break;
			case Register:
				mySYS.SignUp();
				break;
			case PostItem:
				mySYS.PostItem(User);
				break;
			case ViewCommodities:
				ViewItem(mySYS, User);
				break;
			case ManageAccount:
				EditAccount(mySYS, User);
				break;
			default: case End:
				Block = true;
				Users_Iter = OnlineUsers.begin(), End_iter = OnlineUsers.end();
				for (int i = 0;(Users_Iter + i) < End_iter; ++i) {
					Users_Iter[i]->SignOut();
				}
				break;
			case SignOut:
				User->SignOut();
				OnlineUsers.pop_back();
				sysAction = (OnlineUsers.empty()) ? GuestAction : UserSignOutAction;
				sysMenu = &GuestMenu;
				ChRange = '4';
			};
		}
		catch (runtime_error &RuntimeError){
			cout << "\n/////////////////////////////////////////////////////"
				<< RuntimeError.what()
				<< "\n////////////////////////////////////////////////////\n";
		}
		catch (logic_error &LogicError) {
			cout << "\n/////////////////////////////////////////////////////"
				<< LogicError.what()
				<< "\n////////////////////////////////////////////////////\n";
		}
		catch (exception &SomeError) {
			cout << "\n//////////////////////////////////////////////////////////"
				<< "\nSome error occur : " << SomeError.what() << "\nSorry, System is going terminate..."
				<< "\n/////////////////////////////////////////////////////////";
			Users_Iter = OnlineUsers.begin(), End_iter = OnlineUsers.end();
			for (int i = 0; (Users_Iter + i) < End_iter; ++i) {
				Users_Iter[i]->SignOut();
			}
			User = 0;
			//Block = true;
			exit(1);
		}
	} while (!Block);

	return 0;
}

void ViewItem(AuctionSYS &mySYS, const AuctionAccount* User)
{
	int num = 0, input = 0;
	while (true) {
		try {
			mySYS.CommodityList();
			cout << "\nPlease choose the product ID you want to buy (input 0 back to menu):";
			cin.sync();
			cin >> input;//not safe
			if (input != 0) {
				cout << "\nHow many you want to buy? :";
				cin.sync();
				cin >> num;
				mySYS.BuyItem(User, input, num);
			}
			else {
				break;
			}
		}
		catch (out_of_range &RangeError) {
			cout << "\n/////////////////////////////////////////////////////"
				<< RangeError.what()
				<< "\n////////////////////////////////////////////////////";
		}
		catch (...) {
			throw;
		}
	}
}

void EditAccount(AuctionSYS &mySYS, AuctionAccount* User)
{
	bool Flag = true;
	char inChar;

	do {
		mySYS.UserDetail(User);
		cout << "\nPlease select the action you want to perform:"
			<< "\n(1)Cancel/Check my auction item\n(2)Edit UserName\n(3)Edit Password\n(4)Edit IDnumber\n(5)Edit Email\n(6)Edit PhoneNumber\n(7)Edit Adress"
			<< "\nChoose (0 to back):";

		inChar = get_Input('0', '7');
		cin.sync();
		char tmpInput[38];
		try {
			switch (inChar - '0')
			{
			case 1:
				mySYS.DeleteItem(User);
				break;
			case 2:
				cout << "\nInput :";
				cin.getline(tmpInput, 24, '\n');
				User->setUserName(tmpInput);
				cout << "\nUser name has already changed~~~";
				break;
			case 3:
				cout << "\nPlease input your old password:";
				cin.getline(tmpInput, 24, '\n');
				if (mySYS.authenticateUser(User->getAccountName(), tmpInput)) {
					cout << "\nInput your new password:";
					cin.getline(tmpInput, 24, '\n');//len should > 3
					User->setPassWord(tmpInput);
					cout << "\nPassword has already changed~~~";
				}
				else {
					logic_error Error("\nPassword doesn't correct...");
					throw Error;
				}
				break;
			case 4:
				cout << "\nInput :";
				cin.getline(tmpInput, 11, '\n');
				if (!authenticateIDnumber(tmpInput)) {
					logic_error Error("\nWrong ID number...");
					throw Error;
				}
				else {
					User->setUserName(tmpInput);
					cout << "\nIDnumber has already changed~~~\n";
				}
				break;
			case 5:
				cout << "\nInput :";
				cin.getline(tmpInput, 24, '\n');
				User->setEmail(tmpInput);
				cout << "\nEmail has already changed~~~";
				break;
			case 6:
			{
				cout << "\nInput :";
				cin.getline(tmpInput, 11, '\n');
				int count = 0;
				while ((*(tmpInput + count++) = cin.get()) != '\n') {
				}
				*(tmpInput + count - 1) = '\0';
				if (count != 11) {
					logic_error Error("\nYour PhoneNumber is wrong...");
					throw Error;
				}
				else {
					User->setPhoneNumber(tmpInput);
					cout << "\nPhoneNumber has already changed~~~";
				}
				break;
			}
			case 7:
				cout << "\nInput :";
				cin.getline(tmpInput, 38, '\n');
				User->setAddress(tmpInput);
				cout << "\nAddress has already changed~~~";
				break;
			default:case 0:
				Flag = false;
			};
		}
		catch (logic_error &LogicError) {
			cout << "\n/////////////////////////////////////////////////////"
				<< LogicError.what()
				<< "\n////////////////////////////////////////////////////\n";
		}
		catch (...){
			throw;
		}
	} while (Flag);
}
