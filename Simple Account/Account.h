#include <iostream>
#include <string>
using namespace std;

class Account
{
public:
    Account() : name("张三"), Accout("abcdefg"), password("123456"), banlance(0) {}// 无参构造函数
    Account(string n, string Acc, string p) : name(n), Accout(Acc), password(p), banlance(0) {} // 不传余额的构造函数，参数从左往右依次是姓名，账号，密码
    Account(string n, string Acc, string p, float b) : name(n), Accout(Acc), password(p), banlance(b) {} // 构造函数，参数从左往右依次是姓名，账号，密码，余额
    void display(string, string);// 输出名字账号密码余额
    bool check(string, string); // 检查账号密码
    bool deposit(string, string,float &);// 存款
    bool drawing(string, string,float &); // 取款
    string getname(){return name;}//获取姓名
    string getAccount(){return Accout;}//获取账号
    string getpassw(){return password;}//获取密码
    float getbanlance(){return banlance;}//获取余额
    bool transfer(string,string,float,Account);//转账

private:
    string name;     // 姓名
    string Accout;   // 账号
    string password; // 密码
    float banlance;  // 余额
};