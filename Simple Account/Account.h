#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;

class Account
{
public:
    Account():name("张三"),Accout("abcdefg"),password("123456"),banlance(0){}
    Account(string n,string Acc,string p):name(n),Accout(Acc),password(p),banlance(0){}
    Account(string n,string Acc,string p,float b):name(n),Accout(Acc),password(p),banlance(b){}
    void display();//输出名字账号密码余额
    bool check();//检查账号密码
    bool deposit();//存款
    bool drawing();//取款

private:
    string name;
    string Accout;
    string password;
    float banlance;
    
};