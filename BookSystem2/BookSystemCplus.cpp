/***************************************************************
*  all these code were writen with cpp
    this system is not db(table),the next aim is include table
*  framework:
*  1、
   2、
   3、
   4、
   5、
 * date:2020.09.22  rain
******************************************************************/

// inlcude
#include<iostream>
#include<iostream>  //file in and out
#include<iomanip>  //control the style of output ***
#include<string>
#include<time.h>   //time realtion

using namespace std;

//define 
#define BOOK_SYSTEM_RESET_CHANGE_PASSWD_COUNT  (10)  //允许重置密码出错的上限


//屏蔽警告
#pragma warning( disable : 4996 )

//class define

//#if 0
class Book
{
protected:
    string code, name, author, press, time;
    int deadline; //借书期限
    double  price; //价格
    bool    is_Lend; //是否被借出

public:
    bool    is_teacher;
    static int Book_Number; //对于这个类中的静态变量，在全局区必须先赋值
    Book(string c,string n,string a,string p,double pr)
    {
        code = c;
        name = n;
        author = a;
        press = p;
        price = pr;
        is_Lend = 0;
        Book_Number++;
    };

    Book()
    {
        is_Lend = false;
    };

    //get 和 set操作
    string GetTime() { return time; };
    string GetCode() { return code; };
    string GetName() { return name; };
    string GetAuthor() { return author; };
    string GetPress() { return press; };
    int    GetDeadline() { return deadline; };
    double GetPrice() { return price; };
    bool   GetIs_Lend() { return is_Lend; };

    void   SetDeadline(int);
    void   SetTime(string);
    void   SetIs_Lend(bool);
    void   SetCode(string);
    void   SetName(string);
    void   SetAuthor(string);
    void   SetPress(string);
    void   SetPrice(float);

    void   Display();

    //友元
    friend const std::string getCurrentSystemTime(); //获取现在的时间
    friend istream& operator >> (istream &stream, Book &b); //重载操作符>>
    friend ostream& operator << (ostream &stream, Book &b); //重载操作符 <<
};

//Global variable

//Function define

//Function 
ostream &operator << (ostream &stream, Book &b)
{
    stream << "编号:" << setw(9) << b.code << "书名:" << setw(9) << b.name \
        << "作者:" << setw(9) << b.author << "出版社:" << setw(9) << b.press \
        << "单价:" << setw(5) << b.price <<endl;

    return stream;
}

istream &operator >> (istream &stream, Book &b)
{
    cout << "请输入编号:";
    stream >> b.code;
    cout << "请输入书名:";
    stream >> b.name;
    cout << "请输入作者名:";
    stream >> b.author;
    cout << "请输入出版社:";
    stream >> b.press;
    cout << "请输入单价:";
    stream >> b.price;
    return stream;
}

const string getCurrentSystemTime()
{
    time_t t;
    struct tm* It;
    time(&t);
    It = localtime(&t);// 转为时间结构
    char date[60] = { 0 };
    sprintf(date, "%d-%02d-%02d %02d-:%02d:%02d",
        (int)It->tm_year + 1900, (int)It->tm_mon + 1, (int)It->tm_mday,
        (int)It->tm_hour, (int)It->tm_min, (int)It->tm_sec);

    return string(date);
}

void Book::SetDeadline(int a) { deadline = a; }
void Book::SetTime(string a) { time = a; }
void Book::SetIs_Lend(bool a) { is_Lend = a; }

void Book::SetCode(string code1)
{
    code = code1;
}
void Book::SetName(string name1)
{
    name = name1;
}
void Book::SetAuthor(string author1)
{
    author = author1;
}
void Book::SetPress(string press1)
{
    press = press1;
}
void Book::SetPrice(float price1)
{
    price = price1;
}

void Book::Display()//用来展示借书情况
{
    cout << "编号" << setw(9) << GetCode() << " 书名:" << setw(9)
        << GetName() << " 作者:" << setw(9) << GetAuthor() << " 出版社:"
        << setw(9) << GetPress() << " 单价:" << setw(5) << GetPrice() << " 借书时间:"
        << setw(10) << GetTime() << " 借书期限:" << GetDeadline() << "天" << endl;
}

//全局变量
int Book::Book_Number = 0;
static string LogName; //记录当前登陆用户的用户名



//用户类
class User
{
protected:
    string name; //用户名
    string key;  //用户密码
    bool is_Admin, is_Librarian, is_Reader; //用户类型
public:
    void key_change(User* user); //修改用户密码
    int  Judge();                //判断用户类型
    static int User_Number;

    User()            //默认用户类型
    {
        is_Admin = 0;
        is_Librarian = 0;
        is_Reader = 1;
    }

    void Setname(string name1);
    void Setkey(string key1);
    void SetIdentity(bool ad, bool li, bool re) //设置用户类型
    {
        is_Admin = ad;
        is_Librarian = li;
        is_Reader = re;
    }

    string Getname() { return name; }
    string Getkey() { return key; }
    bool   GetisAdmin() { return is_Admin; }
    bool   GetisLibrarian() { return is_Librarian; }
    bool   GetisReader() { return is_Reader; }

};

//
int User::User_Number = 0;



void User::Setname(string name1)
{
    name = name1;
}
void User::Setkey(string key1)
{
    key = key1;
}

int User::Judge()
{
    if (is_Librarian == 1)
    {
        return 5;
    }
    else if (is_Admin == 1)
    {
        return 6;
    }
    else
    {
        return 7;
    }
}
void User::key_change(User *u)
{
    int find = 0;
    string key, key1;
    for (int i = 0;i < User::User_Number;i++)
    {
        if (u[i].Getname() == LogName)
        {
            find = i;
            break;
        }
    }

    unsigned int try_old_time = 0;;

    while (1)
    {
        cout << "请输入原密码:";
        cin >> key;
        //设置一个密码修改出错上限10次
        unsigned int try_new_time = 0;

        if (key == u[find].Getkey())
        {
            while (1)
            {
                cout << "请输入新密码:";
                cin >> key;
                cout << "再输入一次新密码:";
                cin >> key1;

                if (try_new_time > BOOK_SYSTEM_RESET_CHANGE_PASSWD_COUNT)
                {
                    cout << "密码错误数达到系统上限！" << endl;
                    break;
                }

                if (key == key1)
                {
                    //增加一次原始密码和新密码的校验：默认原始密码不能与新密码相等
                    if (key == u[find].Getkey())
                    {
                        cout << "新密码与旧密码重复，请重新输入！" << endl;
                        try_new_time++;
                        continue;
                    }
                    u[find].Setkey(key);
                    cout << "修改成功！" << endl;
                    break;
                }
                else
                {
                    cout << "两次密码输入不一致,修改失败!" << endl;
                    try_new_time++;
                    continue;
                }
            }

            break; //这里是内层密码输入正确的返回

        }
        else
        {
            cout << "密码错误！" << endl;
            if (try_old_time > BOOK_SYSTEM_RESET_CHANGE_PASSWD_COUNT)
            {
                cout << "原始密码错误数达到系统上限！" << endl;
                break;
            }
            try_old_time++;
            continue;
        }
    }
}


//
class Log
{
public:
    User tp;//存储登陆成功的用户信息  ,单用户
    int num;//存储当前用户信息对应的User类下标
    void Login(User* p);  //登陆
    void SignIn(User* p); //注册
    Log()
    {
        num = 0;
    };

    bool is_Log; //判断是否登陆成功

};

//先注册
void Log::SignIn(User* p)
{

}

//登陆
void Log::Login(User* p)
{
    string a, b;
    int flag = 0;

    cout << "请输入账号："<<endl;
    cin >> a;
    cout << "请输入密码" << endl;
    cin >> b;

    for (int i = 0;i < User::User_Number;i++)
    {
        if (a == p[i].Getname() && b == p[i].Getkey())
        {
            tp.SetIdentity(p[i].GetisAdmin(), p[i].GetisLibrarian(), p[i].GetisReader());
            flag = 1; //标记本次验证通过
            tp.Setname(a);
            tp.Setkey(b);
            num = i;
        }
    }

    if (flag)
    {
        if (tp.Judge() == 7)
        {
            LogName = tp.Getname();
            cout << "登录成功！" << endl;
            is_Log = true;
            cout << "尊敬的读者" << tp.Getname() << "，您好" << endl;

        }
        else if (tp.Judge() == 5)
        {
            LogName = tp.Getname();
            cout << "登陆成功！" << endl;
            is_Log = true;
            cout << "尊敬的图书管理员" << tp.Getname() << ",您好！" << endl;
        }
        else if (tp.Judge() == 6)
        {
            LogName = tp.Getname();
            cout << "登陆成功！" << endl;
            is_Log = true;
            cout << "尊敬的系统管理员" << tp.Getname() << ",您好！" << endl;
        }
    }
    else 
    {
        cout << "账号或密码错误！" << endl;
        is_Log = false; 
    }


}


//#endif
int main()
{


    printf("123/n\n123");
    system("pause");
    return 0;
}
