#include<iostream>
#include<string>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<fstream>
using namespace std;

class Stocks {
private:
	char symbol;
	int total_stocks;
	double total_cost;
	double current_price;
	double profit;
	string type;
public:
	int get_total_stocks() { return total_stocks; }
	double get_total_cost() { return total_cost; }
	double get_current_price() { return current_price; }
	char get_symbol() { return symbol; }
	string get_type() {
		return type;
	}

	void set_total_stocks(int stocks, double price) { total_stocks = stocks; set_total_cost(stocks * price); current_price = price; }
	void set_total_cost(double cost) { total_cost = cost; }
	void set_current_price(double price) { current_price = price; }
	void set_symbol(char symb) { symbol = symb; }
	void set_type(string t) {
		type = t;
	}
	void add_stocks()
	{
		int stocks;
		int price;
		cout << "Enter Number of Stocks:";
		cin >> stocks;
		cout << "Enter cost per each stock:";
		cin >> price;

		total_stocks += stocks;
		total_cost += price * stocks;
	}


	void subtract_stocks()
	{
		int stocks;
		int price;
		cout << "Enter Number of Stocks:";
		cin >> stocks;
		cout << "Enter cost per each stock:";
		cin >> price;

		if (stocks > total_stocks)
			cout << "Not enought stocks\n";
		else {
			total_cost -= total_cost / total_stocks * stocks  ;
			total_stocks -= stocks;
			
		}
	}
	// For Polymorphism

	virtual double get_profit() = 0;

	virtual void set_dividend(double div) {
	
	}

	virtual double get_dividend() { return 0; }



};


class Simple_Stocks: public Stocks {
	
public:
	
	Simple_Stocks(char sym,string type) {
		set_symbol(sym);
		int stocks;
		double price;
		cout << "Enter Number of Stocks:";
		cin >> stocks;
		cout << "Enter Price Per Stock:";
		cin >> price;
		set_total_stocks(stocks, price);

		set_type(type);

	}



	double get_profit() {
		return get_current_price() * get_total_stocks() - get_total_cost();
	}

};


class Dividend_Stocks : public Stocks {
	double dividend;
public:

	Dividend_Stocks(char sym, string type) {
		set_symbol(sym);
		int stocks;
		double price;
		cout << "Enter Number of Stocks:";
		cin >> stocks;
		cout << "Enter Price Per Stock:";
		cin >> price;
		set_total_stocks(stocks, price);
		cout << "Enter Amount of Dividends:";
		cin >> dividend;
		set_type(type);

	}

	void set_dividend(double div) {
		dividend = div;
	}
	double get_dividend() { return dividend; }

	double get_profit() {
		return get_current_price() * get_total_stocks() - get_total_cost();
	}

};

class Real_Estate {

	string location;
	double area;
	int year_of_purchase;
	double cost;
	double current_market_value;
public:
	string get_location() { return location; }
	double get_area() { return area; }
	double get_current_price() { return current_market_value; }
	void set_current_price(double price) { current_market_value = price; }
	void get_info() {
		cout << "Enter Location[NO SPACES]:";
		cin >> location;
		cout << "Enter Area[SQ. METERS]:";
		cin >> area;
		cout << "Enter Year of Purchase:";
		cin >> year_of_purchase;
		cout << "Enter Cost:";
		cin >> cost;
		current_market_value = cost;


	}
	double get_profit() {
		return current_market_value - cost;
	}

};
class Investor {
	Stocks** stocks;
	Real_Estate* real_estates;
	int index;
	string username;
	double currency;
	int res_index;
public:
	Investor(){
		stocks = new Stocks*[10];
		real_estates = new Real_Estate[10];
		res_index = 0;
		index = 0;
		currency = 0;
	}
	void add_assets()
	{
		int choice;
		cout << "----------------------------ADD ASSETS------------------------" << endl;
		cout << "1. Add Stocks"<<endl;
		cout << "2. Add Real Estate" << endl;
		cout << "3. Add Currency" << endl;
		cin >> choice;
		
		if (choice == 1)
		{
			cout << "----------------------------ADD STOCKS------------------------" << endl;

			cout << "1. Simple Stocks"<<endl;
			cout << "2. Dividend Stocks"<<endl;
			cin >> choice;
			if (choice == 1)
			{
				cout << "Enter Symbol:";
				char symbol;
				cin >> symbol;
				bool found = false;
				for (int i = 0; i < index; i++)
				{
					if (symbol == stocks[i]->get_symbol())
					{
						stocks[i]->add_stocks();
						found = true;
					}
				}

				if (!found)
				{
					stocks[index++] = new Simple_Stocks(symbol,"simple");
				}
			}
			else if (choice == 2)
			{
				cout << "Enter Symbol:";
				char symbol;
				cin >> symbol;
				bool found = false;
				for (int i = 0; i < index; i++)
				{
					if (symbol == stocks[i]->get_symbol())
					{
						stocks[i]->add_stocks();
						found = true;
					}
				}

				if (!found)
				{
					stocks[index++] = new Dividend_Stocks(symbol, "dividend");
				}
			}
		}
		else if (choice == 2)
		{
			real_estates[res_index++].get_info();
		}
		else if (choice == 3) {
			double am;
			cout << "Enter Amount:";
			cin >> am;
			currency += am;
		}

	}

	void set_username(string usrnm) {
		username = usrnm;
	}
	string get_username() {
		return username;
	}

	void check_assets() {
		cout << "-----------------------------CHECK ASSETS------------------------" << endl << endl;

		cout << "Currency    :     "<<currency<<endl<<endl;
		cout << "--------------------------------STOCKS---------------------------" << endl ;
		cout << "Stock Symbol          Current Price       Total Stocks      Type      Dividends to get"<<endl;

		for (int i = 0; i < index; i++)
		{
			cout << setw(12) << stocks[i]->get_symbol() << setw(22) << stocks[i]->get_current_price() << setw(20) << stocks[i]->get_total_stocks() << setw(10) << stocks[i]->get_type();
			if (stocks[i]->get_type() == "dividend")
				cout << setw(10) << stocks[i]->get_dividend() * stocks[i]->get_total_stocks();
			
			cout << endl;
		}
		cout << "-----------------------------REAL ESTATES------------------------" << endl ;
		cout << "Location          Current Price       Area" << endl;

		for (int i = 0; i < res_index; i++)
		{
			cout << std::left  << setw(18) << real_estates[i].get_location() << setw(20) << real_estates[i].get_current_price() << setw(20) << real_estates[i].get_area() << endl;
		}

		

	}

	void check_profit() {
		cout << "-----------------------------CHECK PROFIT------------------------" << endl << endl;
		cout << "--------------------------------STOCKS---------------------------" << endl;
		cout << "Stock Symbol          Total Profit       Total Stocks      Type" << endl;

		double max = -1;

		string max_profit_string="";
		double profit=0;

		for (int i = 0; i < index; i++)
		{
			cout << setw(12) << stocks[i]->get_symbol() << setw(22) << stocks[i]->get_profit() << setw(20) << stocks[i]->get_total_stocks() << setw(10) << stocks[i]->get_type() << endl;
			if (stocks[i]->get_profit() > max)
			{
				max = stocks[i]->get_profit();
				
				string s = "1";
				s[0] = stocks[i]->get_symbol();
				max_profit_string = "Max Profit is from " + s + " Stock of Type " + stocks[i]->get_type();
			}

			profit += stocks[i]->get_profit();
		
		}
		cout << "-----------------------------REAL ESTATES------------------------" << endl;

		cout << "Location          Profit       Area" << endl;

		for (int i = 0; i < res_index; i++)
		{
			cout <<std::left<< setw(18) << real_estates[i].get_location() << setw(14) << real_estates[i].get_profit() << setw(20) << real_estates[i].get_area() << endl;
			double pr = real_estates[i].get_profit();

			if (pr > max) {
				max = pr;
				max_profit_string = "Max Profit is from Asset at Locatioin " + real_estates[i].get_location();
			}
			profit += pr;
		
		}
		cout << max_profit_string << endl;
		cout << "Total Profit :" << profit << endl;

	}

	void change_prices()
	{
		int choice;
		cout << "----------------------------CHANGE PRICES------------------------" << endl;
		cout << "---------------------THE STOCK IS DIVIDEND STOCK-----------------" << endl;

		cout << "1. Stocks" << endl;
		cout << "2. Real Estate" << endl;

		cin >> choice;
		if (choice == 1)
		{
			cout << "Enter Symbol:";
			char symbol;
			cin >> symbol;
			bool found = false;
			for (int i = 0; i < index; i++)
			{
				if (symbol == stocks[i]->get_symbol())
				{
					if (stocks[i]->get_type() == "simple")
					{
						double price;
						cout << "Enter Current Price:";
						cin >> price;
						stocks[i]->set_current_price(price);
						found = true;
					}
					else {
						cout << "---------------------THE STOCK IS DIVIDEND STOCK-----------------" << endl;

						cout << "Do you want to change price or dividend(1 for price, 2 for dividend):";
						cin >> choice;
						if (choice==1)
						{
							double price;
							cout << "Enter Current Price:";
							cin >> price;
							stocks[i]->set_current_price(price);
							found = true;
						}
						else {
							double price;
							cout << "Enter Dividend:";
							cin >> price;
							stocks[i]->set_dividend(price);
							found = true;
						}


					}
				}
			}

			if (!found)
			{
				cout << "Stock Not Found" << endl;
			}
		}
		else if (choice == 2) {
			cout << "-----------------------------REAL ESTATES------------------------" << endl;
			cout << "SR.NO     Location          Current Price       Area" << endl;
			for (int i = 0; i < res_index; i++)
			{
				cout << std::left <<setw(10)<<i<< setw(18) << real_estates[i].get_location() << setw(20) << real_estates[i].get_current_price() << setw(20) << real_estates[i].get_area() << endl;
			}

			cout << "Enter SR.NO of asset:";
			int sr;
			cin >> sr;
			sr--;
			if (sr > res_index || sr<0)
				cout << "Invalid SR.NO" << endl;
			else {
				cout << "Enter Price:";
				double price;
				cin >> price;
				real_estates[sr].set_current_price(price);
			}
			
		}

	}
	void manage_assets() {
		int choice;
		cout << "----------------------------MANAGE ASSETS------------------------" << endl;


		cout << "1. Add Assets"<<endl;
		cout << "2. Check All Assets"<<endl;
		cout << "3. Check Profits" << endl;
		cout << "4. Change Prices" << endl;
		cout << "Your Choice:";
		cin >> choice;
		if (choice == 1) {
			add_assets();
		}
		else if (choice == 2) {
			check_assets();
		}
		else if (choice == 3) {
			check_profit();
		}
		else if (choice == 4) {
			change_prices();
		}

	}
};



int main() {

	int choice;
	int index = 0;
	Investor *investors = new Investor[100];


	investors[index++].set_username("UmarFarooq478");
	investors[index++].set_username("Shaheer123");
	investors[index++].set_username("abc");
	while (1)
	{
		cout << "---------------------ASSETS MANAGEMENT SYSTEM--------------------" << endl;
		cout << "1. Add an investor" << endl;
		cout << "2. Manage Assets" << endl;
		cout << "Your Choice:";
		cin >> choice;

		if (choice == 1) {
			string usrname;
			cout << "Enter Username [without spaces]:";
			cin >> usrname;

			bool found = false;
			for (int i = 0; i < index; i++)
				if (investors[i].get_username() == usrname)
				{
					found = true;
				}

			if (found)
				cout << "User Already Exists"<<endl;
			else
				investors[index++].set_username(usrname);
		}
		else if (choice == 2) {
			string usrname;
			cout << "Enter Username [without spaces]:";
			cin >> usrname;
			bool found = false;
			for (int i = 0; i < index; i++)
				if (investors[i].get_username() == usrname)
				{
					investors[i].manage_assets();
					found = true;
				}

			if (!found)
				cout << "User Not Exists"<<endl;
		}

	}


}


