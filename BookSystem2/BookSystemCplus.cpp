/***************************************************************
*  all these code were writen with cpp
    this system is not db(table),the next aim is include table
*  framework:
*  1��
   2��
   3��
   4��
   5��
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
#define BOOK_SYSTEM_RESET_CHANGE_PASSWD_COUNT  (10)  //��������������������


//���ξ���
#pragma warning( disable : 4996 )

//class define

//#if 0
class Book
{
protected:
    string code, name, author, press, time;
    int deadline; //��������
    double  price; //�۸�
    bool    is_Lend; //�Ƿ񱻽��

public:
    bool    is_teacher;
    static int Book_Number; //����������еľ�̬��������ȫ���������ȸ�ֵ
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

    //get �� set����
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

    //��Ԫ
    friend const std::string getCurrentSystemTime(); //��ȡ���ڵ�ʱ��
    friend istream& operator >> (istream &stream, Book &b); //���ز�����>>
    friend ostream& operator << (ostream &stream, Book &b); //���ز����� <<
};

//Global variable

//Function define

//Function 
ostream &operator << (ostream &stream, Book &b)
{
    stream << "���:" << setw(9) << b.code << "����:" << setw(9) << b.name \
        << "����:" << setw(9) << b.author << "������:" << setw(9) << b.press \
        << "����:" << setw(5) << b.price <<endl;

    return stream;
}

istream &operator >> (istream &stream, Book &b)
{
    cout << "��������:";
    stream >> b.code;
    cout << "����������:";
    stream >> b.name;
    cout << "������������:";
    stream >> b.author;
    cout << "�����������:";
    stream >> b.press;
    cout << "�����뵥��:";
    stream >> b.price;
    return stream;
}

const string getCurrentSystemTime()
{
    time_t t;
    struct tm* It;
    time(&t);
    It = localtime(&t);// תΪʱ��ṹ
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

void Book::Display()//����չʾ�������
{
    cout << "���" << setw(9) << GetCode() << " ����:" << setw(9)
        << GetName() << " ����:" << setw(9) << GetAuthor() << " ������:"
        << setw(9) << GetPress() << " ����:" << setw(5) << GetPrice() << " ����ʱ��:"
        << setw(10) << GetTime() << " ��������:" << GetDeadline() << "��" << endl;
}

//ȫ�ֱ���
int Book::Book_Number = 0;
static string LogName; //��¼��ǰ��½�û����û���



//�û���
class User
{
protected:
    string name; //�û���
    string key;  //�û�����
    bool is_Admin, is_Librarian, is_Reader; //�û�����
public:
    void key_change(User* user); //�޸��û�����
    int  Judge();                //�ж��û�����
    static int User_Number;

    User()            //Ĭ���û�����
    {
        is_Admin = 0;
        is_Librarian = 0;
        is_Reader = 1;
    }

    void Setname(string name1);
    void Setkey(string key1);
    void SetIdentity(bool ad, bool li, bool re) //�����û�����
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
        cout << "������ԭ����:";
        cin >> key;
        //����һ�������޸ĳ�������10��
        unsigned int try_new_time = 0;

        if (key == u[find].Getkey())
        {
            while (1)
            {
                cout << "������������:";
                cin >> key;
                cout << "������һ��������:";
                cin >> key1;

                if (try_new_time > BOOK_SYSTEM_RESET_CHANGE_PASSWD_COUNT)
                {
                    cout << "����������ﵽϵͳ���ޣ�" << endl;
                    break;
                }

                if (key == key1)
                {
                    //����һ��ԭʼ������������У�飺Ĭ��ԭʼ���벻�������������
                    if (key == u[find].Getkey())
                    {
                        cout << "��������������ظ������������룡" << endl;
                        try_new_time++;
                        continue;
                    }
                    u[find].Setkey(key);
                    cout << "�޸ĳɹ���" << endl;
                    break;
                }
                else
                {
                    cout << "�����������벻һ��,�޸�ʧ��!" << endl;
                    try_new_time++;
                    continue;
                }
            }

            break; //�������ڲ�����������ȷ�ķ���

        }
        else
        {
            cout << "�������" << endl;
            if (try_old_time > BOOK_SYSTEM_RESET_CHANGE_PASSWD_COUNT)
            {
                cout << "ԭʼ����������ﵽϵͳ���ޣ�" << endl;
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
    User tp;//�洢��½�ɹ����û���Ϣ  ,���û�
    int num;//�洢��ǰ�û���Ϣ��Ӧ��User���±�
    void Login(User* p);  //��½
    void SignIn(User* p); //ע��
    Log()
    {
        num = 0;
    };

    bool is_Log; //�ж��Ƿ��½�ɹ�

};

//��ע��
void Log::SignIn(User* p)
{

}

//��½
void Log::Login(User* p)
{
    string a, b;
    int flag = 0;

    cout << "�������˺ţ�"<<endl;
    cin >> a;
    cout << "����������" << endl;
    cin >> b;

    for (int i = 0;i < User::User_Number;i++)
    {
        if (a == p[i].Getname() && b == p[i].Getkey())
        {
            tp.SetIdentity(p[i].GetisAdmin(), p[i].GetisLibrarian(), p[i].GetisReader());
            flag = 1; //��Ǳ�����֤ͨ��
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
            cout << "��¼�ɹ���" << endl;
            is_Log = true;
            cout << "�𾴵Ķ���" << tp.Getname() << "������" << endl;

        }
        else if (tp.Judge() == 5)
        {
            LogName = tp.Getname();
            cout << "��½�ɹ���" << endl;
            is_Log = true;
            cout << "�𾴵�ͼ�����Ա" << tp.Getname() << ",���ã�" << endl;
        }
        else if (tp.Judge() == 6)
        {
            LogName = tp.Getname();
            cout << "��½�ɹ���" << endl;
            is_Log = true;
            cout << "�𾴵�ϵͳ����Ա" << tp.Getname() << ",���ã�" << endl;
        }
    }
    else 
    {
        cout << "�˺Ż��������" << endl;
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
