#include<fstream>
#include<iomanip>
#include <ctime>
#include <windows.h>
#include "Account.h"

using namespace std;

int count=0;//用于判断是否已经登录，成功登录+1，退出登录-1
Account acc;//全局变量
string inname;//用于存放名字
string inacc;//用于存放账号
string inpasw;//用于存放密码
float inbanl;//用于存放余额
string null;

string FloatToStr(float floatnum, int pre)
// 将float类型数据转化为string类型的，并控制精度pre
{
    int f = (int)floatnum;
    float tmp = floatnum - f;

    string res = to_string(f) + ".";
    for (int i = 0; i < pre; i++)
    {
        tmp *= 10;
        int num = (int)tmp;
        res += to_string(num);
    }

    return res;
}

string FloatToStr(double floatnum, int pre)
// 将double类型数据转化为string类型的，并控制精度pre
{
    int f = (int)floatnum;
    double tmp = floatnum - f;

    string res = to_string(f) + ".";
    for (int i = 0; i < pre; i++)
    {
        tmp *= 10;
        int num = (int)tmp;
        res += to_string(num);
    }

    return res;
}

string dataplace(string s, int c)
// 将字符串长度控制在c位，假如位数不够在前面补空格
{
    while (s.length() < c)
    {
        s = " " + s;
    }
    return s;
}

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
    banlance -= ban;
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

bool sign_up(Account &acc)
//登录函数 
{
    ifstream infile;
    infile.open("Account.txt",ios::in);
    if(!infile.is_open())
    {
        cout << "数据加载失败" << endl;
        return false;
    }

    string name,account,password;
    float banlance;
    while (infile >> null >> name >> account >> password >> banlance)
    {
        if (acc.check(account, password))
        {
            infile.close();
            // cout << "登录成功！" << endl;
            ::count = 1;
            acc = Account(name, account, password, banlance);
            return true;
            break;
        }
        // else
        // return false;
        //     // cout<<"登录失败！"<<endl;
    }
}

void sign_in(string name, string account, string password)
{
    ifstream infile;
    infile.open("Account.txt", ios::in);
    if (!infile.is_open())
    {
        cout << "数据加载失败" << endl;
        return;
    }
    string n, a, p;
    float b;
    while (infile >> null >> n >> a >> p >> b)
    {
        if (name == n)
        {
            cout << "账号已存在，请重新输入" << endl;
            return;
        }
    }

    ofstream outfile;
    outfile.open("Account.txt", ios::app);
    if (!outfile.is_open())
    {
        cout << "数据加载失败" << endl;
        return;
    }
    float blance = 0;
    string strb = FloatToStr(blance, 2);
    name = dataplace(name, 8);
    account = dataplace(account, 8);
    password = dataplace(password, 8);
    strb = dataplace(strb, 16);

    outfile << endl
            << "date:" << name << " " << account << " " << password << " " << strb;
    outfile.close();
    cout << "注册成功！" << endl;
}

void save_moeny(Account &acc, string account, string pasw, float ban)
{

    fstream modfile;
    modfile.open("Account.txt", ios::binary | ios::in | ios::out);
    if (!modfile.is_open())
    {
        cout << "数据加载失败" << endl;
        return;
    }
    string line, date;

    string strname, stracc, strpasw, strbla;
    strname = dataplace(acc.getname(), 8);
    stracc = dataplace(acc.getAccount(), 8);
    strpasw = dataplace(acc.getpassw(), 8);
    strbla = dataplace(FloatToStr(acc.getbanlance(), 2), 16);

    string seach = "date:" + strname + " " + stracc + " " + strpasw + " " + strbla;
    acc.deposit(account, pasw, ban);
    strbla = dataplace(FloatToStr(acc.getbanlance(), 2), 16);
    date = "date:" + strname + " " + stracc + " " + strpasw + " " + strbla;

    while (getline(modfile, line))
    {
        size_t pos = line.find(seach);
        if (pos != string::npos)
        {
            line.replace(pos, seach.length(), date);
            modfile.seekp(pos - seach.length() - 1, ios::cur);
            modfile << date; //<<endl;
            modfile.seekp(0, ios::end);
            cout << "存款成功！" << endl;
        }
    }
}

void take_money(Account &acc, string account, string pasw, float ban)
{
    if (ban > acc.getbanlance())
    {
        cout << "取款金额不得大于账户余额！" << endl;
        return;
    }

    fstream modfile;
    modfile.open("Account.txt", ios::binary | ios::in | ios::out);
    if (!modfile.is_open())
    {
        cout << "数据加载失败" << endl;
        return;
    }
    string line, date;

    string strname, stracc, strpasw, strbla;
    strname = dataplace(acc.getname(), 8);
    stracc = dataplace(acc.getAccount(), 8);
    strpasw = dataplace(acc.getpassw(), 8);
    strbla = dataplace(FloatToStr(acc.getbanlance(), 2), 16);

    string seach = "date:" + strname + " " + stracc + " " + strpasw + " " + strbla;
    acc.drawing(account, pasw, ban);
    strbla = dataplace(FloatToStr(acc.getbanlance(), 2), 16);
    date = "date:" + strname + " " + stracc + " " + strpasw + " " + strbla;

    cout << seach << endl;
    cout << date << endl;

    while (getline(modfile, line))
    {
        size_t pos = line.find(seach);
        if (pos != string::npos)
        {
            line.replace(pos, seach.length(), date);
            modfile.seekp(pos - seach.length() - 1, ios::cur);
            modfile << date; //<<endl;
            modfile.seekp(0, ios::end);
            cout << "取款成功！" << endl;
        }
    }
    cout << seach.length() << endl
         << date.length() << endl;
}

void textout()
{
    cout << "1.登录账号" << endl;
    cout << "2.注册账号" << endl;
    cout << "3.查询余额" << endl;
    cout << "4.存款" << endl;
    cout << "5.取款" << endl;
    cout << "6.退出登录" << endl;
    cout << "0.退出软件" << endl;
    cout << "请选择:" ;
}
void choice()
{
    int a;
    cin >> a;
    switch (a)
    {
    case 1:
        cout << "请输入账号：" << endl;
        cin >> inacc;
        cout << "请输入密码：" << endl;
        cin >> inpasw;
        acc = Account("", inacc, inpasw);
        if (sign_up(acc))
            cout << "登录成功！" << endl;
        else
            cout << "登录失败,请检查账号或密码是否正确" << endl;
        break;

    case 2:
        cout << "请输入姓名：" << endl;
        cin >> inname;
        cout << "请输入账号：" << endl;
        cin >> inacc;
        cout << "请输入密码：" << endl;
        cin >> inpasw;
        sign_in(inname, inacc, inpasw);
        break;

    case 3:
        if (::count == 0)
        {
            cout << "请先登录！" << endl;
            Sleep(3000); // 等等3秒
            break;
        }
        if (sign_up(acc))
            acc.display(inacc, inpasw);
        Sleep(7000); // 等等7秒
        break;

    case 4:
        if (::count == 0)
        {
            cout << "请先登录！" << endl;
            Sleep(3000); // 等等3秒
            break;
        }
        cout << "请输入存款金额：" << endl;
        cin >> inbanl;
        save_moeny(acc, acc.getAccount(), acc.getpassw(), inbanl);
        Sleep(3000); // 等等3秒
        break;

    case 5:
        if (::count == 0)
        {
            cout << "请先登录！" << endl;
            Sleep(3000); // 等等3秒
            break;
        }
        cout << "请输入取款金额：" << endl;
        cin >> inbanl;
        take_money(acc, acc.getAccount(), acc.getpassw(), inbanl);
        Sleep(3000); // 等等3秒
        break;

    case 6:
        if (::count == 0)
        {
            cout << "账号未登录" << endl;
            break;
        }
        ::count = 0;
        cout << "账号已退出" << endl;
        Sleep(5000); // 等等5秒
        break;

    case 0:
    default:exit(0);
        break;
    }
}