#include "Account.h"

void Account::display(string acc, string pas)
// 将姓名，账号，余额输出
{
    if (!check(acc, pas))
        cout << "账号或密码输入错误，请检查账号或密码和再次输入" << endl;
    else
        cout << "姓名：" << name << endl
             << "账号：" << Accout << endl
             << "余额：" << banlance << endl;
}
bool Account::check(string acc, string p)
// 检查账号密码，正确返回true，错误返回false
{
    if (acc == Accout && p == password)
        return true;
    else
        return false;
}
bool Account::deposit(string acc,string passw,float &ban)
//存款函数
{
    if(!check(acc,passw))
    return false;
    else
    {
        banlance+=ban;
        return true;
    }
}
bool Account::drawing(string acc,string passw,float &ban)
//取款函数
{
    if(!check(acc,passw))
    return false;
    else if(ban>banlance)
    return false;
    else 
    {
        banlance+=ban;
        return true;
    }
}