#include <iostream>
#include <vector>

#include "Account.h"
#include "Bank.h"
#include "Common.h"


using namespace std;

Bank& g_bank = Bank::getBank(); 
vector<Account*> g_accounts;

void listAccounts()
{
    Account* acc = 0;

    int i = 0;
    vector<Account*>::iterator itr;

    for(itr = g_accounts.begin();
        itr != g_accounts.end();
        ++itr)
    {
        acc = *itr;
        cout << i << ")" << acc << endl;
        ++i;
    }
}


void	addAccount()	
{	
    Account* acc;
    Type type;
    int ch;

    cout << "Select type of account to add: " 	<< endl;
    cout << "1 - Saving account " 	<< endl;
    cout << "2 - Family account " 	<< endl;
    cout << "3 - Stock account " 	<< endl;

    cin >> ch;

    switch(ch) {
        case 1 : type = TYPE_SAVING; break;			
        case 2 : type = TYPE_FAMILY; break;			
        case 3 : type = TYPE_STOCK; break;			

        default: cout << "Invalid type" << endl; return;
    }

    acc = g_bank.CreateAccount(type);
    g_accounts.push_back(acc);

}	
	

void deleteAccount()
{
    int ch;
    cout << "Select number of account to delete: " 	<< endl;
    cin >> ch;

    if (ch > (int)g_accounts.size() || ch < 0)
    {
        cout << "Invalid Index" << endl;
        return;
    }

    vector<Account*>::iterator itr = g_accounts.begin();

    itr += ch;
    g_bank.DeleteAccount(*itr);
    g_accounts.erase(itr);

}

void deleteZero()
{
    g_bank.DeleteAccount(0);
}

void operationSaving()
{
    g_bank.OpSavings();
}
void operationFamily()
{
    g_bank.OpFamily();
}
void operationStock()
{
    g_bank.OpStock();
}



void deleteLastAccount()
{
    g_bank.DeleteAccount(*g_accounts.end());
}

int main() {

	int cont=1;
	int ch  =0;
	
	while(cont) {
        cout << endl;
		cout << "1 - List accounts " 	<< endl;
		cout << "2 - Add account " 	<< endl;
		cout << "3 - Delete account " 	<< endl;
		cout << "4 - Operate on Saving accounts " 	<< endl;
		cout << "5 - Operate on Family accounts " 	<< endl;
		cout << "6 - Operate on Stock accounts " 	<< endl;
		cout << "7 - try to delete zero pointer (g_bank.DeleteAccount(0))" 	<< endl;

		cout << "Any other - exit" 	<< endl;
		cout << " Please, choose option: " << endl;
	
		cin >> ch;

        cout << endl;
		switch(ch) {
			case 1 : listAccounts(); break;			
			case 2 : addAccount(); break;			
			case 3 : deleteAccount(); break;			
			case 4 : operationSaving(); break;			
			case 5 : operationFamily(); break;			
			case 6 : operationStock(); break;			
			case 7 : deleteZero(); break;			

			default: cont = 0;
		}
	}

	return 0;
}



