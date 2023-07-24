#include<iostream>
#include<string>
#include<cstring>
#include<ctime>
#include<fstream>
using namespace std;

class Accounts;
class Checking_Account;
class Saving_Account;
class CreditCard;
class Master_Card;
class Visa_Card;
class Local_Card;
class FAST_Banking_System;
class Date;


class Date
{
private:
	int Day;
	int Month;
	int Year;

public:
	static Date Birth_Date;  //composition

		//overloaded constructor
	Date(int d = 0, int m = 0, int y = 0)
	{
		Day = d;
		Month = m;
		Year = y;
	}

	void PrindDate()
	{
		cout << "(" << Day << "/" << Month << "/" << Year << ")";

	}

	static Date SetDateOfBrth(int day, int month, int year)
	{
		Birth_Date.Day = day;
		Birth_Date.Month = month;
		Birth_Date.Year = year;
		return Birth_Date;
	}

	void SetDay(int dd)
	{
		Day = dd;
	}

	void SetMonth(int mm)
	{
		Month = mm;
	}

	void SetYear(int yy)
	{
		Year = yy;
	}

	int GetDay()
	{
		return Day;
	}

	int GetMonth()
	{
		return Month;
	}

	int GetYear()
	{
		return Year;
	}

};
// initializing current date to 0
Date Date::Birth_Date(0, 0, 0);



class Accounts
{
private:
	string password; // to access only in this class

protected:  // to access in all child classes
	Date DOB;
	string First_Name;
	string Middle_Name;
	string Last_Name;
	long long int CNIC_Number;
	long long int Telephone_Number;
	long long int Account_Number;
	double Balance;
	double Service_charges;
	double Goverment_Taxes;
	string Transaction_History;
	string AccountType;

public:
	Accounts()
	{
		password = '0';
		First_Name = '0';
		Middle_Name = '0';
		Last_Name = '0';
		CNIC_Number = 0;
		Telephone_Number = 0;
		Account_Number = 0;
		Balance = 0;
		Service_charges = 0;
		Goverment_Taxes = 0;
		Transaction_History = '0';
		AccountType = '0';
	}
	void SetaccType(string typ)
	{
		AccountType = typ;
	}

	string GetAccountType()
	{
		return AccountType;
	}

	string GetFirstName()
	{
		return First_Name;
	}
	void SetFirstName(string Fname)
	{
		First_Name = Fname;
	}
	string GetMiddleName()
	{
		return Middle_Name;
	}
	void SetMiddleName(string Mname)
	{
		Middle_Name = Mname;
	}
	string GetLastName()
	{
		return Last_Name;
	}
	void SetLastName(string Lname)
	{
		Last_Name = Lname;
	}
	long long int GetCNIC()
	{
		return CNIC_Number;
	}
	void SetCNIC(long long int cnic)
	{
		CNIC_Number = cnic;
	}
	long long int GetTelephoneNumber()
	{
		return Telephone_Number;
	}
	void SetTelephoneNumber(long long int TNumber)
	{
		Telephone_Number = TNumber;
	}
	long long int GetAccountNumber()
	{
		return Account_Number;
	}
	void SetAccountNumber(long long int AccNumber)
	{
		Account_Number = AccNumber;
	}
	double GetBalance()
	{
		return Balance;
	}

	void SetBalance(double bal)
	{
		Balance = bal;
	}

	void SetPassword(string pass)
	{
		password = pass;
	}

	string GetPassword()
	{
		return password;
	}

	void SetDate(int day, int month, int year)
	{
		DOB.SetDateOfBrth(day, month, year);
	}

	void setTransactionHistory(string hist)
	{
		Transaction_History = hist;
	}
	string GetTransactionHistory()
	{
		return Transaction_History;
	}

	void PrintTransactionHistory()
	{
		cout << Transaction_History << endl;
	}

	//pure virtual function
	virtual double Calculate_Interest(int amount) = 0;

	void calculateServiceTax(int& amount)
	{
		// service charge of 0.2%
		amount = amount - (amount * 0.002);
	}

	void calculateGovtTax(int& amount)
	{
		// gi=overment tax of 2.5%
		amount = amount - (amount * 0.025);
	}




};

class Checking_Account : public Accounts
{
private:
	double interest;
public:
	double Calculate_Interest(int amount)
	{
		// interest rate of checking Account is zero
		return 0;
	}
};

class Saving_Account : public Accounts
{
private:
	double interest;

public:
	double Calculate_Interest(int amount)
	{
		// interest rate of saving account is 5%
		return (amount * 0.05);

	}
};

class CreditCard
{
protected:

	long long int card_number;
	string cardtype;

public:
	CreditCard()
	{
		card_number = 0;
		cardtype = '0';
	}

	void setCardType(string typ)
	{
		cardtype = typ;
	}

	string GetCardType()
	{
		return cardtype;
	}

	void SetCardNumber(long long int num)
	{
		card_number = num;
	}

	long long int GetCardNumber()
	{
		return card_number;
	}

	//pure virtual function
	virtual void CalculateCard_Interest(int& amount) = 0;

};

class Master_Card :public CreditCard
{
	double interest_rate;
public:
	Master_Card(string typ)
	{
		cardtype = typ;
		interest_rate = 0;
	}
	void CalculateCard_Interest(int& amount)
	{
		amount = amount - (amount * 0.18);
	}
};

class Visa_Card :public CreditCard
{
	double interest_rate;
public:

	Visa_Card(string typ)
	{
		cardtype = typ;
		interest_rate = 0;
	}

	void CalculateCard_Interest(int& amount)
	{
		amount = amount - (amount * 0.10);
	}
};

class Local_Card :public CreditCard
{
	double interest_rate;
public:
	Local_Card(string typ)
	{
		cardtype = typ;
		interest_rate = 0;
	}

	void CalculateCard_Interest(int& amount)
	{
		amount = amount - (amount * 0.25);
	}
};

class FAST_Banking_System
{
private:
	Accounts* Acc;
	CreditCard* card;

	// setting current user
	void setUserDetails(long long int acc, string password)
	{
		ifstream allinfo("All users info.txt"); // file containing all users data
		ifstream accountdata("accountType.txt"); // file containing accounts details

		long long int accnum, cnic, phone;
		int d, m, y;
		string pass, fname, mname, lname;
		string accType;
		string cardType;
		long long int accNumber;
		long long int cardNumber;

		if (allinfo.is_open())
		{
			while (!allinfo.eof())
			{

				allinfo >> accnum;
				allinfo >> pass;
				allinfo >> fname >> mname >> lname;
				allinfo >> cnic >> phone;
				allinfo >> d >> m >> y;

				bool check = false;
				int c = 0;
				for (int i = 0; i < password.length(); i++)
				{
					if (pass[i] == password[i])
					{
						c++;
					}
				}
				if (c == password.length())
				{
					check = true;
				}

				if (acc == accnum && check == true) {

					Acc->SetAccountNumber(accnum);
					Acc->SetPassword(pass);
					Acc->SetFirstName(fname);
					Acc->SetMiddleName(mname);
					Acc->SetLastName(lname);
					Acc->SetCNIC(cnic);
					Acc->SetTelephoneNumber(phone);
					Acc->SetDate(d, m, y);

					return;
				}


			}
		}
		allinfo.close();

		if (accountdata.is_open())
		{
			while (!accountdata.eof())
			{
				accountdata >> accNumber;
				accountdata >> accType;
				accountdata >> cardType;
				accountdata >> cardNumber;

				bool check2 = false;
				int d = 0;
				for (int i = 0; i < password.length(); i++)
				{
					if (pass[i] == password[i])
					{
						d++;
					}
				}
				if (d == password.length())
				{
					check2 = true;
				}

				if (acc == accnum && check2 == true) {

					card->SetCardNumber(cardNumber);
					card->setCardType(cardType);
					Acc->SetaccType(accType);

					return;
				}


			}
		}
		accountdata.close();


	}

public:

	FAST_Banking_System(string accType, string cardType)
	{
		if (accType == "saving")
		{
			Acc = new Saving_Account();

		}
		else if (accType == "checking") {
			Acc = new Checking_Account();
		}
		if (cardType == "MasterCard")
		{
			card = new Master_Card(cardType);
		}
		else if (cardType == "VisaCard")
		{
			card = new Visa_Card(cardType);
		}
		else if (cardType == "LocalCard")
		{
			card = new Local_Card(cardType);
		}
		else
		{
			cout << "Check spelling of type and try again!...\n\n";
		}

	}

	bool checkIfCardExists(long long int Cnum, long long int accnum)
	{
		ifstream accountdata("accountType.txt"); // file containing accounts details

		if (accountdata.is_open())
		{
			while (!accountdata.eof())
			{
				long long int accNum;
				string accType;
				string CardType;
				long long int CardNum;

				accountdata >> accNum;
				accountdata >> accType;
				accountdata >> CardType;
				accountdata >> CardNum;
				if (accnum == accNum)
				{
					if (Cnum == CardNum)
					{
						return true;
					}
					else
						return false;
				}
			}
		}
		else
		{
			cout << "Card Doesn't Exists...." << endl;
			return false;
		}
		accountdata.close();

		return false;
	}

	// Function for verification of existance of user from the fils
	bool checkIfExists(long long int CNIC, long long int AccNum)
	{
		ifstream allinfo("All users info.txt");  // file containing all users Data

		if (allinfo.is_open())
		{
			while (!allinfo.eof())
			{
				long long int accnum, cnic, phone;
				int d, m, y;
				string pass, fname, mname, lname;
				allinfo >> accnum;
				allinfo >> pass;
				allinfo >> fname >> mname >> lname;
				allinfo >> cnic >> phone;
				allinfo >> d >> m >> y;

				if (AccNum == accnum)
				{
					if (cnic == CNIC)
					{
						return true;
					}
					else
					{
						return false;
					}
				}

			}

		}
		else
		{
			cout << "Account Doesn't Exists...." << endl;
			return false;
		}
		allinfo.close();

		return false;
	}

	void showMenu()
	{
		cout << "Press 1 to Create Account.\n";
		cout << "Press 2 to Generate Mini Statement.\n";
		cout << "Press 3 to Withdraw Money.\n";
		cout << "Press 4 to Deposit Money.\n";
		cout << "Press 5 to get Balance Inquiry.\n";
		cout << "Press 6 to get Transaction History.\n";
	}


	void Get_Customer_Information()
	{
		fstream fout;
		fout.open("All users info.txt", fstream::app);

		fstream fout2;
		fout2.open("accountType.txt", fstream::app);

		string accType;
		cout << "Enter Account Type[saving or checking]: ";
		cin >> accType;


		if (accType == "saving")
		{
			delete Acc;

			Acc = new Saving_Account();

		}
		else if (accType == "checking") {
			delete Acc;
			Acc = new Checking_Account();
		}
		else { cout << endl << "Invalid Account Type....."; return; }

		Acc->SetaccType(accType);


		long long int acc;
		cout << "Enter Account Number: ";
		cin >> acc;
		Acc->SetAccountNumber(acc);
		fout << acc << " ";
		fout2 << acc << " ";
		fout2 << accType << " ";

		string pass;
		cout << "Enter Password: ";
		cin >> pass;
		Acc->SetPassword(pass);
		fout << pass << " ";

		string fname;
		cout << "Enter First Name: ";
		cin >> fname;
		Acc->SetFirstName(fname);
		fout << fname << " ";

		string Mname;
		cout << "Enter Middle Name: ";
		cin >> Mname;
		Acc->SetMiddleName(Mname);
		fout << Mname << " ";

		string Lname;
		cout << "Enter Last Name: ";
		cin >> Lname;
		Acc->SetLastName(Lname);
		fout << Lname << " ";

		long long int cnic;
		cout << "Enter CNIC Number[without dashes]: ";
		cin >> cnic;
		Acc->SetCNIC(cnic);
		fout << cnic << " ";

		long long int phone;
		cout << "Enter Phone Number: ";
		cin >> phone;
		Acc->SetTelephoneNumber(phone);
		fout << phone << " ";


		int date, month, year = 0;
		cout << "Enter your Date of Birth: \n";
		cout << "Enter Date: ";
		cin >> date;
		cout << "Enter Month: ";
		cin >> month;
		cout << "Enter Year: ";
		cin >> year;
		Acc->SetDate(date, month, year);
		fout << date << " " << month << " " << year << " " << endl;
		cout << "Enter Card Type[MasterCard , VisaCard or LocalCard]: ";
		string cardType;
		cin >> cardType;
		fout2 << cardType << " ";
		if (cardType == "MasterCard")
		{
			delete card;
			card = new Master_Card(cardType);
		}
		else if (cardType == "VisaCard")
		{
			delete card;
			card = new Visa_Card(cardType);
		}
		else if (cardType == "LocalCard")
		{
			delete card;
			card = new Local_Card(cardType);
		}
		else
		{
			cout << "Invalid card type..\n\n";
			return;
		}
		long long int cardNumber;
		cout << "Enter Card Number: ";
		cin >> cardNumber;
		fout2 << cardNumber << " \n";
		card->SetCardNumber(cardNumber);
		card->setCardType(cardType);
		// setting balance of new user to user unless any transaction
		ofstream f3("Balance.txt", fstream::app);
		f3 << acc << " " << 0 << endl << endl;

		setUserDetails(acc, pass);
	}

	void Create_Account()
	{
		Get_Customer_Information();
	}

	void See_MiniStatement(long long int cnic, long long int AccNum)
	{
		if (checkIfExists(cnic, AccNum) == true)
		{
			cout << "\nYour Mini Statement is: \n";
			string hist = Acc->GetTransactionHistory();
			int c = 0;
			for (int i = 0; i < hist.length(); i++)
			{
				if (hist[i] == ' ')
					c++;
			}
			int F = 0;
			bool check = false;
			if (c < 10)
			{
				for (int i = 0; i < Acc->GetTransactionHistory().length(); i++)
				{
					if (hist[i] != ' ')
					{
						cout << hist[i];
					}
					else
					{
						cout << endl;
					}


				}
			}
			else
			{
				for (int i = 0; i < Acc->GetTransactionHistory().length(); i++)
				{
					if (hist[i] != ' ' && check == true)
					{
						cout << hist[i];
					}
					else if (hist[i] == ' ')
					{
						F++;
					}
					if (c - F == 10)
					{
						check = true;
					}


				}
			}


		}
		else
		{
			cout << "Account NOT FOUND!\n\n";
		}
	}

	void Withdraw_Money_viaCard(long long int cNum, long long int AccNum, int Amount)
	{
		if (checkIfCardExists(cNum, AccNum) == true)
		{
			string bal[100];
			string temp4 = " ";
			int i = 0;
			fstream fin("Balance.txt");
			bool check = false;
			if (fin.is_open())
			{
				while (!fin.eof())
				{

					getline(fin, bal[i]);
					int j;
					if (i % 2 != 0 && check == true)
					{

						bal[i].append(temp4);
						Acc->setTransactionHistory(bal[i]);
					}
					check = false;
					if (bal[i].length() > 1 && i % 2 == 0)
					{
						for (j = 0; bal[i][j] != ' '; j++);
						string temp = bal[i].substr(0, j);
						long long int newacc = stoi(temp);
						if (newacc == AccNum)
						{
							string temp2 = bal[i].substr(j, bal[i].length());
							int balance = stoi(temp2);

							if (balance < Amount)
							{
								cout << "Not Possible" << endl;
								return;
							}
							if (Amount <= 50000 && card->GetCardType() == "MasterCard")
							{
								card->CalculateCard_Interest(Amount);
							}
							else if (Amount <= 100000 && card->GetCardType() == "VisaCard")
							{
								card->CalculateCard_Interest(Amount);
							}
							else if (card->GetCardType() == "LocalCard")
							{
								card->CalculateCard_Interest(Amount);
							}

							balance -= Amount;
							temp2 = to_string(balance);
							temp.append(" ");
							temp.append(temp2);
							bal[i] = temp;
							temp4 = to_string(Amount) + "-* ";
							check = true;
							Acc->SetBalance(balance);
							if (Amount != 0)
							{
								cout << "\n\nWithdraw Succesful\nWithdrawal Amount: " << Amount << "\nRemaining Balance: " << Acc->GetBalance();
							}
							else
							{

							}
						}
					}
					i++;
				}

			}
			fin.close();

			ofstream bala("Balance.txt");
			for (int j = 0; j <= i; j++)
			{
				bala << bal[j] << endl;
			}

		}
		else
		{
			cout << "Account NOT FOUND!\n\n";
		}


	}

	void Withdraw_Money(long long int cnic, long long int AccNum, int Amount)
	{


		if (checkIfExists(cnic, AccNum) == true)
		{

			string bal[100];
			string temp4 = " ";
			int i = 0;
			fstream fin("Balance.txt");
			bool check = false;
			if (fin.is_open())
			{
				while (!fin.eof())
				{

					getline(fin, bal[i]);
					int j;
					if (i % 2 != 0 && check == true)
					{

						bal[i].append(temp4);
						Acc->setTransactionHistory(bal[i]);
					}
					check = false;
					if (bal[i].length() > 1 && i % 2 == 0)
					{
						for (j = 0; bal[i][j] != ' '; j++);
						string temp = bal[i].substr(0, j);
						long long int newacc = stoi(temp);
						if (newacc == AccNum)
						{
							string temp2 = bal[i].substr(j, bal[i].length());
							int balance = stoi(temp2);

							if (balance < Amount)
							{
								cout << "Not Possible" << endl;
								return;
							}
							if (Amount >= 5000 && Amount < 50000)
							{
								Acc->calculateServiceTax(Amount);
							}
							else if (Amount >= 50000)
							{
								Acc->calculateGovtTax(Amount);
							}

							balance -= Amount;
							temp2 = to_string(balance);
							temp.append(" ");
							temp.append(temp2);
							bal[i] = temp;
							temp4 = to_string(Amount) + "- ";
							check = true;
							Acc->SetBalance(balance);
							if (Amount != 0)
							{
								cout << "\n\nWithdraw Succesful\nWithdrawal Amount: " << Amount << "\nRemaining Balance: " << Acc->GetBalance();
							}
							else
							{

							}
						}
					}
					i++;
				}

			}
			fin.close();

			ofstream bala("Balance.txt");
			for (int j = 0; j <= i; j++)
			{
				bala << bal[j] << endl;
			}

		}
		else
		{
			cout << "Account NOT FOUND!\n\n";
		}



	}

	void Deposit_Money(long long int cnic, long long int AccNum, int Amount)
	{

		if (checkIfExists(cnic, AccNum) == true)
		{
			string bal[100];
			string temp4 = " ";
			int i = 0;
			fstream fin("Balance.txt");
			bool check = false;
			if (fin.is_open())
			{
				while (!fin.eof())
				{

					getline(fin, bal[i]);
					int j;
					if (i % 2 != 0 && check == true)
					{

						bal[i].append(temp4);
						Acc->setTransactionHistory(bal[i]);
					}
					check = false;
					if (bal[i].length() > 1 && i % 2 == 0)
					{
						for (j = 0; bal[i][j] != ' '; j++);
						string temp = bal[i].substr(0, j);
						long long int newacc = stoi(temp);
						if (newacc == AccNum)
						{
							string temp2 = bal[i].substr(j, bal[i].length());
							int balance = stoi(temp2);
							balance += Amount;
							balance += Acc->Calculate_Interest(Amount);
							temp2 = to_string(balance);
							temp.append(" ");
							temp.append(temp2);
							bal[i] = temp;
							temp4 = to_string(Amount) + "+ ";
							check = true;
							Acc->SetBalance(balance);
							if (Amount != 0)
							{
								cout << "\n\nDeposit Succesful\nDeposit Amount: " << Amount << "\nAmount added as profit interest: " << Acc->Calculate_Interest(Amount) << "\nNew Balance: " << Acc->GetBalance();
							}
							else
							{

							}
						}
					}
					i++;
				}

			}
			fin.close();

			ofstream bala("Balance.txt");
			for (int j = 0; j <= i; j++)
			{
				bala << bal[j] << endl;
			}


		}
		else
		{
			cout << "Account NOT FOUND!\n\n";
		}

	}

	void Balance_Inquiry(long long int cnic, long long int AccNum)
	{
		if (checkIfExists(cnic, AccNum) == true)
		{
			cout << "\n\nYour Balance Inquiry is: " << Acc->GetBalance();
		}
		else
		{
			cout << "\nAccount NOT FOUND!\n\n";
		}

	}


	void Transaction_History(long long int cnic, long long int accNum)
	{
		if (checkIfExists(cnic, accNum) == true)
		{
			cout << "\n\nYour Transaction History is: ";
			Acc->PrintTransactionHistory();
		}
		else
		{
			cout << "\nAccount NOT FOUND!\n\n";
		}
	}

};

void main()
{
	FAST_Banking_System Sys("saving", "MasterCard");
	Sys.showMenu();
	cout << "\n\n----------------------------------------------------------------------\n\n";
	int choice = 0;
	long long int AccNum, cnic;
	cin >> choice;
	cout << "Your Choice-> " << choice;


	if (choice == 1)
	{
		Sys.Create_Account();
		cout << "\n\n----------------------------------------------------------------------\n\n";
	}
	else if (choice == 2)
	{
		long long int AccountNumber;
		long long int CNIC;
		cout << "Enter Account Number : ";
		cin >> AccountNumber;
		cout << "Enter CNIC: ";
		cin >> CNIC;
		Sys.See_MiniStatement(CNIC, AccountNumber);
		cout << "\n\n----------------------------------------------------------------------\n\n";
	}
	else if (choice == 3)
	{
		char c;
		cout << "Enter A or a to withdraw Money Directly: ";
		cout << "Enter Bor b to withdraw Money thorugh Card: ";
		cin >> c;
		if (c == 'A' || c == 'a')
		{
			long long int AccountNumber;
			long long int CNIC;
			int Amount;
			cout << "Enter Account Number : ";
			cin >> AccountNumber;
			cout << "Enter CNIC: ";
			cin >> CNIC;
			cout << "Enter Amount: ";
			cin >> Amount;
			Sys.Withdraw_Money(CNIC, AccountNumber, Amount);
			cout << "\n\n----------------------------------------------------------------------\n\n";
		}
		else if (c == 'B' || c == 'b')
		{
			long long int AccountNumber;
			long long int CardNumber;
			int Amount;
			cout << "Enter Account Number : ";
			cin >> AccountNumber;
			cout << "Enter Credit Card Number: ";
			cin >> CardNumber;
			cout << "Enter Amount: ";
			cin >> Amount;
			Sys.Withdraw_Money_viaCard(CardNumber, AccountNumber, Amount);
			cout << "\n\n----------------------------------------------------------------------\n\n";
		}

	}
	else if (choice == 4)
	{
		long long int AccountNumber;
		long long int CNIC;
		int Amount;
		cout << "Enter Account Number : ";
		cin >> AccountNumber;
		cout << "Enter CNIC: ";
		cin >> CNIC;
		cout << "Enter Amount: ";
		cin >> Amount;
		Sys.Deposit_Money(CNIC, AccountNumber, Amount);
		cout << "\n\n----------------------------------------------------------------------\n\n";
	}
	else if (choice == 5)
	{
		long long int AccountNumber;
		long long int CNIC;
		cout << "Enter Account Number : ";
		cin >> AccountNumber;
		cout << "Enter CNIC: ";
		cin >> CNIC;
		Sys.Balance_Inquiry(CNIC, AccountNumber);
		cout << "\n\n----------------------------------------------------------------------\n\n";
	}
	else if (choice == 6)
	{
		long long int AccountNumber;
		long long int CNIC;
		cout << "Enter Account Number : ";
		cin >> AccountNumber;
		cout << "Enter CNIC: ";
		cin >> CNIC;
		Sys.Transaction_History(CNIC, AccountNumber);
		cout << "\n\n----------------------------------------------------------------------\n\n";

	}
	else
	{
		cout << "Select the correct option. Thanks!\n";
		return;
	}





	cout << endl;
	cout << endl;
	system("pause");

}