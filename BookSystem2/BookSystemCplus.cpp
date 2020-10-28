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
#include<fstream>  //file in and out
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
    int f1;
    string a, b, bb;
    while (1)
    {
        f1 = 1;
        cout << "�����û�����";
        cin >> a;

        for (int i = 0; i <= User::User_Number;i++)
        {
            if (p[i].Getname() == a)
            {
                cout << "�û����Ѵ��ڣ�����������." << endl;
                f1 = 0;
            }
        }

        if (f1 == 0)
        {

        }

        if (f1 == 1)
        {
            break;
        }
    }

    //��������
    while (1)
    {
        cout << "����������:";
        cin >> b;
        cout << "�ٴ���������:";
        cin >> bb;
        if (bb != b)
        {
            cout << "�������벻һ�£�����������." << endl;
        }
        if (bb == b)
        {
            break;
        }
    }

    //��ע��ɹ����û���Ϣ�洢��User����
    cout << "name:" << a << endl;
    (p + User::User_Number)->Setname(a);
    (p + User::User_Number)->Setkey(b);
    (p + User::User_Number)->SetIdentity(0, 0, 1);
    tp.Setname(a);
    num = User::User_Number;
    User::User_Number++;
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

    cout << "��ǰ������Ϊ�� User::User_Number:" << User::User_Number << endl;
    for (int i = 0;i < User::User_Number;i++)
    {
        cout << p[i].Getname() << endl;
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


//ͼ�����Ա
class Librarian :public User, public Log
{
public:
    static int Librarian_Number;
    void zc(User* U, Log a, Librarian *L)
    {
        a.SignIn(U);
        cout << "ע��ɹ���" << endl;
        Librarian_Number++;
        U[a.num].SetIdentity(0, 1, 0);
        SetIdentity(0, 1, 0);
        User::name = a.tp.Getname();
        User::key = a.tp.Getkey();

        L[Librarian::Librarian_Number].Setname(a.tp.Getname());

    }

    Librarian()
    {
        SetIdentity(0, 1, 0);
    }

    Librarian(string name1, string key1, User* U)
    {
        U[User_Number].Setname(name1);
        U[User_Number].Setkey(key1);
        U[User_Number].SetIdentity(0,1,0);
        SetIdentity(0, 1, 0);
        U->User_Number++;
        name = name1;
        key = key1;
    }

    void Book_Add(Book *B); //����ͼ��
    void Book_Del(Book *B); //ɾ��ͼ��
    void Book_Alter(Book *B); //�޸�ͼ��
    void Book_Find(Book *B); //����ͼ��
    void Book_AddUp(Book *B); //ͳ��ͼ��


};
int Librarian::Librarian_Number = 1;

void Librarian::Book_Add(Book *B) //����ͼ��
{
    string aa;
    cout<< "---------------���ͼ��---------------" << endl;

    while (1)
    {
        cin >> B[Book::Book_Number];   //������>>����
        ofstream bookmessage("Bookmessage.txt", ios::app);
        if (bookmessage.is_open())
        {
            bookmessage << getCurrentSystemTime();
            bookmessage << "����������ͼ��" << endl;
            bookmessage << B[Book::Book_Number] << endl;
            bookmessage.close();
        }

        Book::Book_Number++;
        cout << "¼��ɹ���" << endl;
        aa = cin.get();
        cout<<"�����������¼��(����'0'�ɷ������˵�)��";
        if (aa == "0")
        {
            break;
        }
    }
}

void Librarian::Book_Del(Book *B) //ɾ��ͼ��
{
    cout << "---------------ɾ��ͼ��---------------" << endl;
    string a;
    if (Book::Book_Number == 0)
    {
        cout << "Ŀǰ��ͼ��,�������ͼ��!" << endl;
    }
    else
    {
        cout << "������ͼ���Ż�����";
        cin >> a;
        int flag = 0, find = 0;
        for (int j = 0;j < Book::Book_Number;j++)
        {
            if (a == B[j].GetCode() || a == B[j].GetName())
            {
                flag = 1;
                find = j;
                break;
            }
        }

        if (flag == 1)
        {
            char a;
            cout << "�Ѿ��ҵ�ͼ�飬��Ӧ���Ϊ��" << B[find].GetCode() << "����Ϊ��" << B[find].GetName()<< "���Ƿ�ѡ��ɾ����(y or n)" <<endl;
            cin >> a;

            if (a == 'y')
            {
                //��Ҫɾ������Ϣ�ȱ��ݣ�����ɾ���ȡ��������һ����Ϣ
                Book book_t(B[find]);       //�Ƿ��忽��
                for (int k = find;k < Book::Book_Number;k++)
                {
                    if (k == Book::Book_Number - 1)
                    {
                        Book::Book_Number--;
                        break;
                    }

                    B[k] = B[k + 1];
                }

                ofstream bookmessage("Bookmessage.txt", ios::app);
                if (bookmessage.is_open())
                {
                    bookmessage << getCurrentSystemTime();
                    bookmessage << "����:ɾ��ͼ�� " << endl;
                    bookmessage << B[find] << endl;         //��ѯ���Ĳ����ǵ�ǰɾ��������
                    bookmessage.close();
                }

                cout << "ɾ���ɹ���" << endl;
            }
            else
            {
                cout << "��ȡ��ɾ����";
            }
        
        }
        else
        {
            cout << "ͼ�鲻���ڣ���ȷ���Ƿ��Ѿ�¼�롣" << endl;
        }
    }

}

//�޸�ͼ��
void DisplayAlter()
{
    cout << "��ѡ���޸���:" << endl;
    cout << "1-�޸ı��" << endl;
    cout << "2-�޸�����" << endl;
    cout << "3-�޸�����" << endl;
    cout << "4-�޸ĳ�����" << endl;
    cout << "5-�޸ĵ���" << endl;
    cout << "0-�˳��޸�" << endl;
}

void Librarian::Book_Alter(Book *B) //�޸�ͼ��
{
    string a;
    cout << "---------------�޸�ͼ��---------------" << endl;
    if (Book::Book_Number == 0)
    {
        cout << "Ŀǰ��ͼ��,�������ͼ��" << endl;
    }
    else
    {
        cout << "������ͼ���Ż�����";

        cin >> a;
        int flag = 0, find = 0;
        for (int i = 0;i < Book::Book_Number;i++)
        {
            if (a == B[i].GetCode() || a == B[i].GetName()) //ͼ�����ֻ��߱�����
            {
                flag = 1;
                find = i;
                break;
            }
        }

        if (flag == 1)
        {
            //�����ҵ���Ĵ����߼�
            char b;
            cout << "�Ѿ��ҵ�ͼ�飬�Ƿ�ѡ���޸ģ�(y or n)" << endl;
            cin >> b;
            if (b == 'y')
            {
                DisplayAlter();   //��ʾ�޸ĵ�ѡ��
                int c;
                cin >> c;

                switch (c)
                {
                    case 1:
                    {
                        while (1)
                        {
                            cout << "�������޸ĺ�ı��:" << endl;
                            int flag = 1;
                            cin >> a;
                            for (int l = 0;l < Book::Book_Number;l++)
                            {
                                if (B[l].GetCode() == a)
                                {
                                    flag = 0;
                                    break;
                                }
                            }

                            if (flag) 
                            { 
                                B[find].SetCode(a);
                                cout << "���޸�!" << endl;
                                break; 
                            }
                            else
                            {
                                cout << "�Ѵ��ڸñ�ţ����޸�!" << endl;
                            }

                        }
                        break;
                    }
                    case 2:
                    {
                        cout << "�������޸ĺ������:" << endl;
                        cin >> a;B[find].SetName(a);
                        cout << "���޸�!" << endl;
                        break;
                    }
                    case 3:
                    {
                        cout << "�������޸ĺ��������:" << endl;
                        cin >> a;B[find].SetAuthor(a);
                        cout << "���޸�!" << endl;
                        break;
                    }
                    case 4:
                    {
                        cout << "�������޸ĺ�ĳ�������:" << endl;
                        cin >> a;B[find].SetPress(a);
                        cout << "���޸�!" << endl;
                        break;
                    }
                    case 5:
                    {
                        cout << "�������޸ĺ�ļ۸�:" << endl;
                        double p;
                        cin >> p;B[find].SetPrice(p);
                        cout << "���޸�!" << endl;
                        break;
                    }
                    case 0:
                    {
                        break;
                    }

                    default: cout << "��������ȷ����:" << endl;
                }

                ofstream bookmessage("Bookmessage.txt", ios::app);
                if (bookmessage.is_open())
                {
                    bookmessage << getCurrentSystemTime();
                    bookmessage << "����:�޸�ͼ�� " << endl;
                    bookmessage << B[find] << endl;
                    bookmessage.close();
                }
            }
        }
    }
}

void Librarian::Book_Find(Book *B) //����ͼ��
{
    cout << "-------��ѯͼ��-------" << endl;
    cout << "������ͼ���Ż�����:";

    string a1;
    cin >> a1;

    int flag = 0;
    int count = 0;
    for (int j = 0;j < Book::Book_Number;j++)
    {
        if (B[j].GetName() == a1 || B[j].GetCode() == a1)
        {
            flag = 1;
            cout << B[j];
            count++;
        }
    }

    if (count == 0)cout << "δ�ҵ�����..." << endl;
    else
        cout << "���ҵ�" << count << "���顣" << endl;
}

void Librarian::Book_AddUp(Book *B) //ͳ��ͼ��
{
    cout << "Ŀǰ����" << Book::Book_Number << "���顣" << endl;
    for (int i = 0;i < Book::Book_Number;i++)
    {
        cout << B[i];
    }
}
//#endif


//////////////////////////////////////////////////////////////////
/****************************************************************
����ģ��

*****************************************************************/
//////////////////////////////////////////////////////////////////


class Reader:public User,public Log,public Book
{
    Book s[100];
public:
    void zc(User *U,Log a,Reader *R)
    {
        a.SignIn(U);
        cout << "�Ƿ�Ϊ��ʦ�û���(y or n)";
        string c;
        cin >> c;
        if (c == "y")
        {
            R[a.num].is_teacher = true;
        }
        else
        {
            R[a.num].is_teacher = false;
        }

        cout << "ע��ɹ���" << endl;

        U[a.num].SetIdentity(0, 0, 1);
        SetIdentity(0, 0, 1);
        User::Setname(a.tp.Getname());
        User::Setkey(a.tp.Getkey());
        R[Reader::Reader_Number].Setname(a.tp.Getname());
        cout << "ע��ǰ���û���" << Reader::Reader_Number << endl;
        cout << "ע�����û����֣�" << a.tp.Getname() << endl;

        Reader::Reader_Number++;
    }

    static int Reader_Number;
    void Book_Lend(Book *B);
    void Book_Return(Book *B);
    void Book_LR();
    void Book_show(Book *B);

    Reader() :User()
    {
        User::is_Admin = 0;
        User::is_Librarian = 0;
        User::is_Reader = 1;

    }



};
int Reader::Reader_Number = 0;

void Reader::Book_show(Book *B)
{
    for (int i = 0;i < Book::Book_Number;i++)
    {
        cout << B[i];
    }
}

void Reader::Book_LR()
{
    
    cout << "---------������Ϣ---------" << endl;
    int ST = 10;  //        ��ʦ�ɽ�������
    int TE = 20;//ѧ���ɽ�������
    int flag = 0;

    if (is_teacher == true)
    {
        cout << "��ʦ" << "     " << "���Խ�������:" << TE << "��" << endl;
    }
    else
    {
        cout << "ѧ��" << "     " << "���Խ�������:" << ST << "��" << endl;
    }

    cout << "��ǰ������Ϣ:" << endl;

    for (int i = 0;i <= s->Book_Number;i++)
    {
        if (s[i].GetIs_Lend() == true) 
        { 
            flag = 1;
            break; 
        }
    }


    if (flag == 0)
    {
        cout << "�޽����¼\n";
    }
    else
    {
        int LendBookNumber = 0;
        for (int i = 0;i <= Book::Book_Number;i++)
        {
            if (s[i].GetIs_Lend() == true)
            {
                s[i].Display();
                LendBookNumber++;
            }
        }

        if (is_teacher == true)
        {
            cout << "�����Խ�" << TE - LendBookNumber << "����." << endl;
        }
        else
        {
            cout << "�����Խ�" << ST - LendBookNumber << "����." << endl;
        }
    }
}


void Reader::Book_Lend(Book *B)
{
    for (int i = 0;i < Book_Number;i++)
    {
        (s + i)->SetCode((B + i)->GetCode());
        (s + i)->SetName((B + i)->GetName());
        (s + i)->SetAuthor((B + i)->GetAuthor());
        (s + i)->SetPress((B + i)->GetPress());
        (s + i)->SetPrice((B + i)->GetPrice());
        (s + i)->Book_Number = (B + i)->Book_Number;

        if (is_teacher == true)
        {
            (s + i)->SetDeadline(60);
        }
        else
        {
            (s + i)->SetDeadline(30);
        }
    }

    Book *b = B;
    string a;

    cout << "---------����---------" << endl;
    cout << "��������Ҫ�����鼮�ı�Ż�����:";
    cin >> a;

    int Find = 0, flag1 = 0;
    int LendBookNumber = 0;

    for (int j = 0;j <= Book::Book_Number;j++)
    {
        if ((a == b[j].GetCode() || a == b[j].GetName()) && b[j].GetIs_Lend() == false)
        {
            flag1 = 1;Find = j;break;
        }
    }

    for (int i = 0;i <= Book::Book_Number;i++)
    {
        if (s[i].GetIs_Lend() == true)
        {
            LendBookNumber++;
        }
    }

    if (!flag1)
    {
        cout << "ͼ�鲻���ڻ��Ѿ������!" << endl;
    }
    else
    {
        if (is_teacher == true && LendBookNumber == 20) 
        {
            throw LendBookNumber;
        }
        else if (is_teacher == false && LendBookNumber == 10) 
        {
            throw LendBookNumber;
        }

        cout << "���ĳɹ�!" << endl;
        b[Find].SetIs_Lend(true);
        s[Find].SetIs_Lend(true);
        s[Find].SetTime(getCurrentSystemTime());
        s[Find].SetDeadline(s[Find].GetDeadline());
        ofstream lendmessage("Lendmessage.txt", ios::app);
        if (lendmessage.is_open())
        {
            lendmessage << "����:" << LogName << endl;
            lendmessage << "    ������:" << s[Find].GetCode();
            lendmessage << "    ����ʱ��:" << s[Find].GetTime() << endl;
            lendmessage.close();
        }

    }
}

void Reader::Book_Return(Book *B)
{
    Book *b = B;
    int flag = 0;
    int find = 0;

    cout << "---------����---------" << endl;
    string a;
    cout << "��������Ҫ�黹�鼮�ı�Ż�����:";
    cin >> a;

    for (int j = 0;j < Book::Book_Number;j++)
    {
        if (a == b[j].GetCode() || a == b[j].GetName())
        {
            flag = 1;
            find = j;
            break;
        }
    
    }

    if (flag == 1)
    {
        //�н��������Ż��й黹
        if (s[find].GetIs_Lend() == true)
        {
            cout << "�黹ʱ��:" << getCurrentSystemTime() << endl;
            string lend_time = s[find].GetTime();
            string return_time = getCurrentSystemTime();
            //�ж��Ƿ�ʱ
            int mml, mmr, ddl, ddr;
            mmr = return_time[6] - '0' + (return_time[5] - '0') * 10;
            mml = lend_time[6] - '0' + (lend_time[5] - '0') * 10;
            ddr = return_time[9] - '0' + (return_time[8] - '0') * 10;
            ddl = lend_time[9] - '0' + (lend_time[8] - '0') * 10;

            int day = 0;
            if (is_teacher == true)
                day = 60;
            else
                day = 30;
            //û������
            if (mmr * 30 + ddr - mml * 30 - ddl <= day)
            {
                s[find].SetIs_Lend(false);
                b[find].SetIs_Lend(false);
                ofstream lendmessage("Lendmessage.txt", ios::app);
                if (lendmessage.is_open())
                {
                    lendmessage << "����:" << LogName << endl;
                    lendmessage << "    ������:" << s[find].GetCode();
                    lendmessage << "    ����ʱ��:" << return_time << endl;
                    lendmessage.close();
                }
                cout << "�黹�ɹ���" << endl;
            }
            else
            {
                throw mmr * 30 + ddr - mml * 30 - ddl - day;
            }
        }
        else
        {
            cout << "����δ������" << endl;
        }
    }
    else
    {
        cout << "δ�ҵ����飡" << endl;
    }

}


//ϵͳ����Ա
class Admin :public User, public Log
{
public:
    void Reader_Add(User *U, Reader *R); //��Ӷ���
    void Reader_Dele(User *U, Reader *R);//ɾ������
    void Librarian_Add(User *U, Librarian *L);//���ͼ�����Ա
    void Librarian_Dele(User *U, Librarian *L);//ɾ��ͼ�����Ա
    void Reader_Alter(Reader *R, User *U, Admin *A, Librarian *L);//����Ȩ�޸���
    void Librarian_Alter(Librarian *L, User *U, Admin *A, Reader *R);//ͼ�����ԱȨ�޸���
    void User_keychange(User *U);//�޸��û�����
    static int Admin_Number;

    Admin()
    {
        is_Admin = 1;
        is_Librarian = 0;
        is_Reader = 0;
    }

    Admin(string name1, string key1, User *U)
    {
        U[U->User_Number].Setname(name1);
        U[U->User_Number].Setkey(key1);
        is_Admin = 1;
        is_Librarian = 0;
        is_Reader = 0;
        U[U->User_Number].SetIdentity(1,0,0);
        U->User_Number++;
        name = name1;
        key = key1;
    }
};
int Admin::Admin_Number = 1;

void Admin::User_keychange(User *U)
{
    int find = 0;
    string Name, key, key1;
    bool is_find = false;
    cout << "�������û�����";
    cin >> Name;

    for (int i = 0;i < User::User_Number;i++)
    {
        if (U[i].Getname() == Name)
        {
            find = i;
            is_find = true;
            break;
        }
    }                   //carolyn9365

    if (is_find == true)
    {
        //�ҵ���Ӧ���˻�
        cout << "������������:";
        cin >> key;
        cout << "������һ��������:";
        cin >> key1;

        if (key == key1)
        {
            U[find].Setkey(key);
            cout << "�޸ĳɹ���" << endl;
        }
        else
        {
            cout << "�����������벻һ��,�޸�ʧ��!" << endl;
        }
    }
    else
    {
        cout << "δ�ҵ����û�." << endl;
    }
}


//����Ȩ���޸�
void Admin::Reader_Alter(Reader *R, User *U, Admin *A, Librarian *L)
{
    string name, key;
    string a;
    cout << "��������Ҫ���в����Ķ����û���:";
    cin >> a;

    int flag = 0, find = 0;
    for (int i = 0; i < Reader::Reader_Number;i++)
    {
        if (R[i].GetName() == a)
        {
            flag = 1;
            find = i;
            name = R[i].Getname();
            key = R[i].Getkey();
            break;
        }
    }

    if (flag)
    {
        int t = 0;
        cout << "��ѡ����Ҫ�����Ȩ������:" << endl;
        cout << "��ͼ�����Ա" << endl;
        cout << "��ϵͳ����Ա" << endl;
        cout << "�۷���" << endl;
        cin >> a;

        if (a == "1")
        {
            t = 1;
        }
        else if (a == "2")
        {
            t = 2;
        }
        else
        {
            cout << "���سɹ�!"; 
            t = 0;
        }

        //�޸�ԭ���Ӷ���������ɾ��������ӵ���Ҫ���ӵ�ͼ�����Ա����ϵͳ����Ա������
        if (t == 1 || t == 2)
        {
            for (int j = find; j < Reader::Reader_Number;j++)
            {
                if (j == Reader::Reader_Number - 1) 
                {
                    Reader::Reader_Number--;
                    break;
                }
                R[j] = R[j + 1];
            }

            if (t == 1)
            {
                for (int j = 0;j < U->User_Number;j++)
                {
                    if (U[j].Getname() == name) {
                        U[j].SetIdentity(0, 1, 0);
                        break;
                    }
                }
                L[Librarian::Librarian_Number].Setname(name);
                L[Librarian::Librarian_Number].Setkey(key);
                L[Librarian::Librarian_Number].SetIdentity(0, 1, 0);
                L->Librarian_Number++;
            }

            if (t == 2)
            {
                for (int j = 0;j < U->User_Number;j++)
                {
                    if (U[j].Getname() == name) {
                        U[j].SetIdentity(1, 0, 0);
                        break;
                    }
                }
                A[Admin::Admin_Number].Setname(name);
                A[Admin::Admin_Number].Setkey(key);
                A[Admin::Admin_Number].SetIdentity(1, 0, 0);
                A->Admin_Number++;
            }
            cout << "����ɹ�!" << endl;
        }
    }
    else    
        cout << "�����û������ڣ�" << endl;

}

//ͼ�����ԱȨ���޸�
void Admin::Librarian_Alter(Librarian *L, User *U, Admin *A, Reader *R)
{
    string name, key;
    string a;cout << "��������Ҫ���в�����ͼ�����Ա�û���:";cin >> a;
    int flag = 0, find = 0;
    for (int i = 0;i < Librarian::Librarian_Number;i++)
    {
        if (L[i].Getname() == a) {
            flag = 1;find = i;name = L[i].Getname();key = L[i].Getkey();break;
        }
    }

    if (flag)
    {
        int t = 0;
        cout << "��ѡ����Ҫ�����Ȩ������:" << endl;
        cout << "�ٶ���" << endl;
        cout << "��ϵͳ����Ա" << endl;
        cout << "�۷���" << endl;
        cin >> a;
        if (a == "1")
        {
            t = 1;
        }
        else if (a == "2")
        {
            t = 2;
        }
        else
        {
            cout << "���سɹ�!"; t = 0;
        }
        if (t == 1 || t == 2)
        {
            for (int j = find;j < Librarian::Librarian_Number;j++)
            {
                if (j == Librarian::Librarian_Number - 1) { Librarian::Librarian_Number--;break; }
                L[j] = L[j + 1];
            }
            if (t == 1)
            {
                for (int j = 0;j < U->User_Number;j++)
                {
                    if (U[j].Getname() == name) {
                        U[j].SetIdentity(0, 0, 1);
                        break;
                    }
                }
                R[Reader::Reader_Number].Setname(name);
                R[Reader::Reader_Number].Setkey(key);
                R[Reader::Reader_Number].SetIdentity(0, 0, 1);
                R->Reader_Number++;
            }

            if (t == 2)
            {
                for (int j = 0;j < U->User_Number;j++)
                {
                    if (U[j].Getname() == name) {
                        U[j].SetIdentity(1, 0, 0);
                        break;
                    }
                }
                A[Admin::Admin_Number].Setname(name);
                A[Admin::Admin_Number].Setkey(key);
                A[Admin::Admin_Number].SetIdentity(1, 0, 0);
                A->Admin_Number++;
            }
            cout << "����ɹ�!" << endl;
        }
    }
    else    cout << "�����û������ڣ�" << endl;
}

//���Ӷ���
void Admin::Reader_Add(User *U, Reader *R)
{
    Log a;
    R[Reader::Reader_Number].zc(U, a, R);
}

//����ͼ�����Ա
void Admin::Librarian_Add(User *U, Librarian *L)
{
    Log a;
    L[Librarian::Librarian_Number].zc(U, a, L);
}


//ɾ������
void Admin::Reader_Dele(User *U, Reader *R)
{
    string a;
    cout << "��������Ҫ���в������û���:";
    cin >> a;
    int flag = 0, find = 0, find1 = 0;

    for (int i = 0;i < Reader::Reader_Number;i++)
    {
        if (R[i].GetName() == a)
        {
            flag = 1;
            find = i;
            break;
        }
    }

    if (flag)
    {
        for (int j = find;j < Reader::Reader_Number;j++)
        {
            if (j == Reader::Reader_Number - 1)
            {
                Reader::Reader_Number--;
            }
            R[j] = R[j + 1];
        }

        for (int j = 0;j < U->User_Number;j++)
        {
            if (U[j].Getname() == a)
            {
                find1 = j;
                break;
            }
        }

        for (int j = find1;j < U->User_Number;j++)
        {
            if (j == U->User_Number - 1) 
            { 
                U->User_Number--;
                break; 
            }
            U[j] = U[j + 1];
        }

        cout << "ɾ���ɹ���" << endl;
    }
    else    
        cout << "�û������ڣ�" << endl;

}

//ɾ������Ա
void Admin::Librarian_Dele(User *U, Librarian *L)
{
    string a;
    cout << "��������Ҫ���в������û���:";cin >> a;
    int flag = 0, find = 0, find1 = 0;
    for (int i = 0;i < Librarian::Librarian_Number;i++)
    {
        if (L[i].Getname() == a) {
            flag = 1;find = i;break;
        }

    }
    if (flag)
    {
        for (int j = find;j < Librarian::Librarian_Number;j++)
        {
            if (j == Librarian::Librarian_Number - 1) { Librarian::Librarian_Number--;break; }
            L[j] = L[j + 1];
        }
        for (int k = 0;k < U->User_Number;k++)
        {
            if (U[k].Getname() == a)
            {
                find1 = k;break;
            }
        }
        for (int j = find1;j < U->User_Number;j++)
        {
            if (j == U->User_Number - 1) { U->User_Number--;break; }
            U[j] = U[j + 1];
        }
        cout << "ɾ���ɹ���" << endl;
    }
    else    cout << "�û������ڣ�" << endl;
}

void jiemian()//������
{
    cout << "|ͼ�����Ա:L   ����:8  |  ϵͳ����Ա:A    ����:8|" << endl;
    cout << "|Ĭ��3����     ���:10000,����:C++               |" << endl;
    cout << "|              ���:10001,����:C                 |" << endl;
    cout << "|              ���:10002,����:C#                |" << endl;
    cout << "I��������������������������ͼ�����ϵͳ3.0��������������������������������I" << endl;
    cout << "I����������������������������------ע��------������������������������I" << endl;
    cout << "I����������������������������------��½------������������������������I" << endl;
    cout << "I����������������������������------�˳�------������������������������I" << endl;
}
void reajm()//���߽���
{
    cout << "��-------�鿴ͼ��" << endl;
    cout << "��-------����" << endl;
    cout << "��-------����" << endl;
    cout << "��-------��ѯ�軹��Ϣ" << endl;
    cout << "��-------�޸�����" << endl;
    cout << "��-------�˳�" << endl;
}
void libjm()//ͼ�����Ա����
{
    cout << "��-------����ͼ��" << endl;//�٢ڢۢܢݢޢߢ��
    cout << "��-------�޸�ͼ��" << endl;
    cout << "��-------ɾ��ͼ��" << endl;
    cout << "��-------��ѯͼ��" << endl;
    cout << "��-------ͳ��ͼ��" << endl;
    cout << "��-------�޸�����" << endl;
    cout << "��-------�˳�" << endl;
}
void admjm()//ϵͳ����Ա����
{
    cout << "��-------���Ӷ���" << endl;//�٢ڢۢܢݢޢߢ��
    cout << "��-------ɾ������" << endl;
    cout << "��-------����ͼ�����Ա" << endl;
    cout << "��-------ɾ��ͼ�����Ա" << endl;
    cout << "��-------����Ȩ���޸�" << endl;
    cout << "��-------ͼ�����ԱȨ���޸�" << endl;
    cout << "��-------�޸��û�����" << endl;
    cout << "��-------�޸�����" << endl;
    cout << "��-------�˳�" << endl;
}
Book B[100]{ Book("10000","C++","����","666",51.3),Book("10001","C","����","777",48.8),Book("10002","C#","����","888",59.9) };
User U[100];
Reader R[100];
Librarian L[100]
{ 
    Librarian("L","8",U) 
};
Admin A[100]
{ 
    Admin("A","8",U) 
};
Log c;

#define AAA "1234"
int main_old()
{


    printf("123/n\n123");

    std::cout << AAA"567" << std::endl;
    system("pause");
    return 0;
}


int main(int agrc,const char* argv[])
{
    while (true)
    {
        jiemian();
        int a;string aa;cin >> aa;//��ֹһ��ʼ�������������bug.
        if (aa == "1")a = 1;
        else if (aa == "2")a = 2;
        else if (aa == "3")a = 3;
        else 
        {
            cout << "������1��3�ڵ�����" << endl;continue;
        }

        switch (a) 
        {
            //��װ������
        case 1:
            {
                cout << "����ע��" << endl;
                R[Reader::Reader_Number].zc(U, c, R);
                break;
            }

        //��װ������
        case 2:
        {
            cout << "��  ½" << endl;
            c.Login(U);
            if (c.is_Log == false)break;

            //��װ������
            if (c.tp.Judge() == 5)//ͼ�����Ա
            {
                int n = 1;
                while (n) {
                    libjm();
                    int b;cin >> b;
                    switch (b) {
                    case 1:
                    {
                        L[c.num].Book_Add(B);
                        break;}
                    case 2:
                    {
                        L[c.num].Book_Alter(B);
                        break;}
                    case 3:
                    {
                        L[c.num].Book_Del(B);
                        break;}
                    case 4:
                    {
                        L[c.num].Book_Find(B);
                        break;}
                    case 5:
                    {
                        L[c.num].Book_AddUp(B);
                        break;}
                    case 6:
                    {
                        L[c.num].key_change(U);
                        break;}
                    default:
                        n = 0;
                    }
                }
            }
            //��װ������
            else if (c.tp.Judge() == 6)//ϵͳ����Ա
            {

                int n = 1;
                while (n) {
                    admjm();
                    int b;cin >> b;
                    switch (b) {
                    case 1://���Ӷ���
                    {
                        A[c.num].Reader_Add(U, R);
                        break;}
                    case 2://ɾ������
                    {
                        A[c.num].Reader_Dele(U, R);
                        break;}
                    case 3://����ͼ�����Ա
                    {
                        A[c.num].Librarian_Add(U, L);
                        break;
                    }
                    case 4://����ͼ�����Ա
                    {
                        A[c.num].Librarian_Dele(U, L);
                        break;
                    }
                    case 5://����Ȩ���޸�
                    {
                        A[c.num].Reader_Alter(R, U, A, L);
                        break;
                    }
                    case 6://ͼ�����ԱȨ���޸�
                    {
                        A[c.num].Librarian_Alter(L, U, A, R);
                        break;
                    }
                    case 7://�޸��û�����
                    {
                        A[c.num].User_keychange(U);
                        break;
                    }
                    case 8://�޸�����
                    {
                        A[c.num].key_change(U);
                        break;
                    }
                    default:
                        n = 0;break;
                    }
                }
            }
            //��װ������
            else if (c.tp.Judge() == 7)//����
            {
                int n = 1;
                while (n) {
                    reajm();
                    int b;cin >> b;
                    switch (b) {
                    case 1://�鱾չʾ
                    {
                        R[c.num].Book_show(B);
                        break;
                    }
                    case 2://����
                    {
                        try {
                            R[c.num].Book_Lend(B);
                        }
                        catch (int Num)
                        {
                            cout << "��������������������ʧ�ܡ�" << endl;
                        }

                        break;}
                    case 3://����
                    {
                        try {
                            R[c.num].Book_Return(B);
                        }

                        catch (int day)
                        {
                            cout << "�黹ͼ�鳬ʱ" << day << "��" << "����50��" << endl;
                        }
                        break;}

                    case 4://��ʾ�軹��Ϣ
                    {
                        R[c.num].Book_LR();
                        break;
                    }
                    case 5://�޸�����
                    {
                        R[c.num].key_change(U);
                        break;
                    }
                    default:
                        n = 0;
                    }
                }
            }
            else break;
            break;}
        //��װ������
        case 3:
        {cout << "             ϵͳ���˳�" << endl;
        return 0;
        break;}
        default:
            break;
        }
        cin.get();//���ջس���
        cout << "���س�������������\n";
        cin.get();
    }

    return 0;
}

//finish date:2020.10.28
//�ο��� CSND������cc
//���ӣ�https://blog.csdn.net/xsydalao/article/details/92799184