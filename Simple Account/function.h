#include<fstream>
#include<iomanip>
#include "Account.h"

using namespace std;

int count=0;//用于判断是否已经登录，成功登录+1，退出登录-1
Account acc;//全局变量
string inname;//用于存放名字
string inacc;//用于存放账号
string inpasw;//用于存放密码
float inbanl;//用于存放余额

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

bool Account::transfer(string Acc,string passw,float banl,Account Account)
//转账函数
{
    if(!check(Acc,passw))
        return false;
    else if(banl>banlance)
        return false;
    else
        return true;
}

void land(Account &acc)
//登录函数 
{
    ifstream infile;
    infile.open("Account.txt",ios::in);
    if(!infile.is_open())
    {cout<<"Error,program has exited!"<<endl;
    exit(-1);}
    
    string name,account,password;
    float banlance;
    while (infile>>name>>account>>password>>banlance)
    {
        if(acc.getpassw()==password)
        {
            infile.close();
            cout<<"登录成功！"<<endl;
            count+=1;
            acc=Account(name,account,password,banlance);
            break;
        }
        else
            cout<<"登录失败！"<<endl;
    }
    
}

void textout()
{
    cout<<"请选择"<<endl;
    cout<<"1.登录账号"<<endl;
    cout<<"2.注册账号"<<endl;
    cout<<"3.查询余额"<<endl;
    cout<<"4.存款"<<endl;
    cout<<"5.取款"<<endl;
    cout<<"0.退出软件"<<endl;
}
void choice()
{
    int a;
    cin>>a;
    switch (a)
    {
    case 1:cout<<"请输入账号："<<endl;
    cin>>inacc;
    cout<<"请输入密码："<<endl;
    cin>>inpasw;
    acc=Account("",inacc,inname);
    land(acc) ;
        break;

    case 2: ;
    break;

    case 3: ;
    break;

    case 0:
    default:exit(0);
        break;
    }
}