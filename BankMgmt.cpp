//Bank Account Management System
//Written by Wesley Aubynn


#include <iostream>
#include <string>
using namespace std;


class accountInfo
{   
    protected:
        double acctBalance;
        int numDeposits = 0;
        int numWithdraws = 0;
        double annInterest;
        double monthSercharge = 0.0;
        double initialBalance = 0.0;
        double finalBalance = 0.0;

    public:

        accountInfo(){};
        accountInfo(double acctBal=0, double annInt=0.02){
            acctBalance= acctBal;
            initialBalance = acctBal;
            annInterest = annInt;
            
        };

        virtual void deposit (double depositAmt){
            acctBalance+= depositAmt;
            finalBalance = acctBalance;
            numDeposits++ ;
        }

        virtual void withdraw (double withdrawAmt){
            acctBalance -= withdrawAmt;
            finalBalance = acctBalance;
            numWithdraws ++;
        }

        virtual void calcInt(){
            double monthlyRate = annInterest/12;
            double monthlyInt = acctBalance* monthlyRate;
            acctBalance += monthlyInt;
        }

        virtual void monthlyProc(){
            calcInt();
            acctBalance -= monthSercharge;
            cout<< acctBalance;
            numDeposits= numWithdraws= monthSercharge= 0;
        }

};

class savings: public accountInfo
{   
    public:
     savings(double initBalance, double annInt) : accountInfo(initBalance, annInt){
        acctState();
    };

    double savDepsoitTotal =0.0;
    double savWithdrawTotal =0.0;
    bool status;


    void acctState(){
        if (acctBalance< 25){
        status = true;
        cout<<"\nACTIVE\n"; 
    }else{
        status = false;  
        cout<<"\nINACTIVE\n"; 
        }
    }
    

    void withdraw (double drawAmt){
        if (status== false){
                cout<< "\nAccount inactive"<<endl
                    << "Cannot make withdrawal"<<endl;
            }else{
                accountInfo::withdraw(drawAmt);
                savWithdrawTotal += drawAmt;
                if (numWithdraws > 4){
                    monthSercharge += numWithdraws-4;
                }
            }
        
    }

    void deposit (double depositTotal){
        if (status==false){
            if((acctBalance + depositTotal)> 25){
                status = true;
                accountInfo::deposit(depositTotal);
                savDepsoitTotal++;
            }else{
                status = false;
            }
        }else{ 
           accountInfo::deposit(depositTotal);
           savDepsoitTotal+= depositTotal;
        }
    }

    void monthlyProc(){
        if(numWithdraws > 4){
            monthSercharge += numWithdraws - 4;
        }
        acctBalance -= monthSercharge;
        finalBalance = acctBalance;
        accountInfo::monthlyProc();
        acctState();
    }

    void print_stats(){
                cout << "Total number of deposits: "<<savings::numDeposits<< endl;
                cout << "Total amount of deposits: "<< savDepsoitTotal << endl;
                cout << "Total number of withdrawals :"<< savings::numWithdraws<<endl;
                cout << "Total amount of withdrawls: " << savWithdrawTotal << endl;
                cout << "Service Charge: " << monthSercharge << endl;
                cout << "Beginning Balance: " << initialBalance << endl;
                cout << "End Balance: " << finalBalance << endl;
    }


};



class chequeing :public accountInfo
{

    public:
    chequeing (double x, double y): accountInfo(x,y){};
    double cheqDepsoitTotal =0 ;
    double cheqWithdrawTotal =0;
    double cheqMonthCharges =0; 
    
    void deposit(double amount){
            accountInfo::deposit(amount);
            cheqDepsoitTotal += amount;
        }
    void withdraw(double amount){
        if ((acctBalance - amount) < 0){
            acctBalance -= 15;
        }
        accountInfo::withdraw(amount);

        cheqWithdrawTotal += amount;
        monthSercharge += (5 + 0.10*numWithdraws);
    }

    void monthlyProc(){
        acctBalance-= monthSercharge;
        finalBalance = acctBalance;
        accountInfo::monthlyProc();
        monthSercharge = 0;
    }


    void print_stats(){
            cout << "Total number of deposits: "<<chequeing::numDeposits<< endl;
            cout << "Total amount of deposits: "<< cheqDepsoitTotal << endl;
            cout << "Total number of withdrawals: "<< chequeing::numWithdraws << endl;
            cout << "Total amount of withdrawls: " << cheqWithdrawTotal << endl;
            cout << "Service Charge: " << monthSercharge << endl;
            cout << "Beginning Balance: " << initialBalance << endl;
            cout << "End Balance: " << finalBalance << endl;
        }

};

int main()
{
    
    savings savAcc(10, 0.02);
    chequeing chequAcc(30, 0.01);

    int choice;
    double amount;

    do {
        cout<<"\nBank Account Menu: \n";
        cout<<"1. Savings Deposits: \n";
        cout<<"2. Savings Withdrawals: \n";
        cout<<"3. Chequing deposits: \n";
        cout<<"4. Chequing withdrawals: \n";
        cout<<"5. Monthly statsistics: \n";
        cout<<"6. Statistics Print: \n";
        cout<<"7. Exit: \n";
        cin>> choice;



        switch (choice) {
                case 1:
                    cout << "Enter amount you are depositing: " << endl;
                    cin >> amount;
                    savAcc.deposit(amount);
                    break;

                case 2:
                    cout << "Enter amount you are withdrawing: " << endl;
                    cin >> amount;
                    savAcc.withdraw(amount);
                    break;

                case 3:
                    cout << "Enter amount you are depositing: " << endl;
                    cin >> amount;
                    chequAcc.deposit(amount);
                    break;

                case 4:
                    cout << "Enter amount you are withdrawing: " << endl;
                    cin >> amount;
                    chequAcc.withdraw(amount);
                    break;

                case 5:
                    savAcc.monthlyProc();
                    chequAcc.monthlyProc();
                    break;
                
                case 6:
                    cout << "Saving account stats: " << endl;
                    savAcc.print_stats();
                    cout << endl;
                    cout << "checking account stats: " << endl;
                    chequAcc.print_stats();
                    cout << endl;

                case 7:
                    break;
                
                default:
                    cout << "Invalid input" << endl;
                    break;

            }
    }
    while(choice != 7);
    return 0;
}