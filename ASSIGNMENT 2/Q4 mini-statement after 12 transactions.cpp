#include <iostream>
#include <iomanip>
class SavingsAccount {
private:
    int accountNumber;
    double balance;
    double transactions[10]{};
    int count=0;
    void record(double amount) {
        if(count<10) transactions[count++]=amount;
        else {
            for(int i=1;i<10;++i) transactions[i-1]=transactions[i];
            transactions[9]=amount;
        }
    }
public:
    SavingsAccount(int no,double opening) : accountNumber(no),balance(opening) {}
    void deposit(double amount) {
        if(amount>0) { balance+=amount; record(amount); }
    }
    bool withdraw(double amount);
    void miniStatement() const;
};
bool SavingsAccount::withdraw(double amount) {
    if(amount<=0 || amount>balance) return false;
    balance-=amount;record(-amount);return true;
}
void SavingsAccount::miniStatement() const {
    std::cout << "Account: " << accountNumber << " Balance: "
              << std::fixed << std::setprecision(2) << balance << '\n';
    for(int i=0;i<count;++i) std::cout << transactions[i] << ' ';
    std::cout << '\n';
}
int main() {
    SavingsAccount a(101,1000);
    for(int i=1;i<=11;++i) a.deposit(10*i);
    a.withdraw(100);a.miniStatement();
}
