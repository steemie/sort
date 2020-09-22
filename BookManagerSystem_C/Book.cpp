/**************************************************
*简介：
*
*日期：2020.09.21
*
**************************************************/

//头文件
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<algorithm>

using namespace std;


//宏定义区
#define BOOK_SYSTEM_CLIENT_MAX_VERIFY_TIMES (1024)      //系统用户账户最大验证码校验次数

//数据结构

struct library 
{
    int     id;             //图书编号
    char    name[30];       //图书书名
    double  price;          //图书价格
    char    author[30];     //图书作者
    int     stock;          //图书库存
    char    preface[2000];  //图书简介
}stu[100];

//账户信息
struct Asccount 
{
    char asname[30];  //账户名
    char password[12]; //账户密码
    char nickname[30];  //账户昵称
}client_info[100];

//书名信息
struct Book 
{
    char name[30]; //书名
    char time[40]; //时间
};

//用户信息
typedef struct UserNode 
{
    char            users[30];   //用户的名字
    int             sexes;       //用户
    int             r;           //该用户名下有多少数目
    struct Book     book[30];    //用户名下图书的信息
    UserNode        *Next;
}UserInfo;


//全局变量       最好放到一个类中或者初始化、去初始化模块中
int g_num   = 42;
int g_login_count    = 2;      //登录用户个数
int g_kk    = g_login_count;   //登录个数
int g_passwd_error_count = 0; //用户登陆密码输入错误次数，最大支持三次，超过账户就被锁定
int g_login = 0;
int g_login_operator = 0; //登陆操作选择：核对账户、增加账户、找回密码、编辑密码
int g_check_passwd_count = 0; //登陆的时候密码验证次数

char g_login_name[30];


UserInfo *g_user_info       = NULL;    //全局用户个人信息
UserInfo *g_add_user_info   = new UserInfo;   //全局新增用户个人信息
UserInfo *g_pHead           = new UserInfo;   //头指针，new了两个何时delete







 //隐藏光标
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


//数据存储模块 
//加载数据到内存
void LoadData()
{
    FILE *fp;
    fp = fopen("dataCount.txt", "r");
    fscanf(fp, "%d", &g_num);
    fscanf(fp, "%d", &g_login_count);
    fclose(fp);
    printf("LoadData:g_num:%d,g_jj:%d\n", g_num, g_login_count);
    g_kk = g_login_count;

}
void SaveUser()
{
    int i = 0;
    FILE *fp;
    fp = fopen("fundaccount.txt", "w");
    for (i = 0; i <= g_login_count; i++) 
    {
        fprintf(fp, "%s\n", client_info[i].asname);
        fprintf(fp, "%s\n", client_info[i].password);
        fprintf(fp, "%s\n", client_info[i].nickname);
    }
    fclose(fp);
}
void SaveData()
{
    FILE *fp;
    fp = fopen("dataCount.txt", "w");
    fprintf(fp, "%d\n", g_num);
    fprintf(fp, "%d\n", g_login_count);
    fclose(fp);
}

/********************
*账户模块
**********************/
//输出账号菜单
void PrintUser(void)
{
    printf("\t\t\t************************************\n");
    printf("\t\t\t*    登录 请按 1                   *\n");
    printf("\t\t\t*    注册新账号 请按 2             *\n");
    printf("\t\t\t*    找回密码 请按 3               *\n");
    printf("\t\t\t*    修改密码 请按 4               *\n");
    printf("\t\t\t*    退出程序 请按 5               *\n");
    printf("\t\t\t************************************\n");
}

//将账号读入内存中
void LoadUser(void)
{
    int i = 0;
    freopen("fundaccount.txt", "r", stdin);    //重定向输入到文件中
    for (i = 0; i < g_login_count; i++)
    {
        scanf("%s", client_info[i].asname);
        scanf("%s", client_info[i].password);
        scanf("%s", client_info[i].nickname);
    }
    freopen("CON", "r", stdin);    //读到控制台
}

//输入是错误
void IsWrong(void)
{
    char s[50];
    gets_s(s);    //gets被gets_s取代
    system("cls");
    printf("\t\t\t输入错误！！\n");
    system("PAUSE");
    system("cls");
}

//用户的一系列操作
void CheckUser()
{
    int i = 0, flag = 0, K = 0, KK =0 ;
    char ss[30];
    char passwd[10]; //密码支持到10位
    printf("\t\t\t\t请输入登录账号：\n\n\t\t\t\t ");
    scanf("%s", ss);
    for (i = 0; i < g_login_count; i++) 
    {
        if (strcmp(client_info[i].asname, ss) == 0) 
        {
            strcpy(g_login_name, ss);  //登陆中找到存储的名字，则置标志位，并且赋值 给全局变量
            flag = 1;
            break;
        }
    }

    //如果没有找到该用户，则输出账户未注册
    if (!flag) {
        printf("\n\t\t\t\t此账号还未注册！！\n\n\t\t\t   ");
        system("PAUSE");
        system("cls");
        return;
    }

    //找到后输入密码
    printf("\t\t\t\t请输入密码：\n\n\t\t\t\t ");
    scanf("%s", passwd);
    if (strcmp(client_info[i].password, passwd) == 0) 
    {
        //密码校验正确
        g_check_passwd_count = 0;
        flag = 2;
    }
    if (flag == 1) 
    {
        system("cls");
        printf("\t\t\t\t密码错误！！\n\n\t\t\t   ");
        system("PAUSE");
        system("cls");
        g_check_passwd_count++;
        return;
    }
    else if (flag == 2) 
    {
        unsigned int verify_code = 0;
        while (1)
        {
            printf("\t\t\t   请输入下面的验证码：\n");
            srand((unsigned)time(NULL));
            K = rand();
            printf("\n\t\t\t\t  %d\n\t\t\t\t  ", K);
            int result = scanf("%d", &KK);
            if (!result)
            {
                IsWrong();
                return;
            }

            if (KK != K)
            {
                //优化：验证码错误应该重试
                verify_code++;
                if (verify_code >= BOOK_SYSTEM_CLIENT_MAX_VERIFY_TIMES)
                {
                    printf("\n\t\t\t验证码输入超过最大次数，请仔细核对验证码并检查网络是否通畅！！\n");
                    system("PAUSE");
                    system("cls");
                    continue;
                }
                printf("\n\t\t\t验证码错误,请重新验证！！\n");
                system("PAUSE");
                system("cls");

                continue;
            }

            break;  //验证码校验成功
        }

        //走到这里登陆已经成功
        g_login = 1;
    }
}


void SaveBorrow(UserInfo* head)
{
    int i;
    UserInfo* p = head->Next;
    FILE *fp;
    fp = fopen("borrow.txt", "w");
    while (p) 
    {
        fprintf(fp, "%s\n", p->users);
        fprintf(fp, "%d\n", p->sexes);
        for (i = 0; i < p->sexes; i++) 
        {
            fprintf(fp, "%s\n", p->book[i].name);
            fprintf(fp, "%s\n", p->book[i].time);
        }
        fprintf(fp, "%d\n", p->r);
        p = p->Next;
    }
    fclose(fp);
}
// 借书记录加载到内存
void LoadBorrow(UserInfo* userInfo)
{
    int i, j;
    UserInfo *p;
    UserInfo *rear = userInfo;
    freopen("borrow.txt", "r", stdin);  //重定向
    for (i = 0; i < g_kk; i++) 
    {
        p = new UserInfo;
        
        // 节点信息加载，用户需要输入的
        scanf("%s", p->users);
        scanf("%d", &p->sexes);
        for (j = 0; j < p->sexes; j++) 
        {
            scanf("%s", p->book[j].name);
            scanf("%s", p->book[j].time);
        }
        scanf("%d\n", &p->r);
        rear->Next = p;
        rear = p;
    }
    rear->Next = NULL;
    freopen("CON", "r", stdin);
    if (g_user_info != NULL)
    {
        rear->Next = g_add_user_info;
        rear = g_add_user_info;
    }
    rear->Next = NULL;

    SaveBorrow(userInfo);
}
//新建账户
void AddUser()
{
    //读入用户的基本信息，检查合法性后，存放到本地磁盘中
    FILE *fp;
    int j = 0, i = 0;
    char c[12], str[30];
    printf("\t\t\t请输入账号：\n\n\t\t\t  ");
    scanf("%s", str);

    //检查账户是否存在
    for (i = 0; i < g_login_count; i++)
    {
        if (strcmp(client_info[i].asname, str) == 0) 
        {
            printf("\t\t\t该账号已被注册，请重新申请！！\n\n\t\t\t   ");
            system("PAUSE");
            return;
        }
    }
    strcpy(client_info[g_login_count].asname, str);
    printf("\t\t\t请输入密码（密码长度不超过十个字符）：\n\n\t\t\t  ");
    scanf("%s", client_info[g_login_count].password);
    printf("\t\t\t请再输入一次密码：\n\n\t\t\t  ");
    scanf("%s", c);

    if (strcmp(client_info[g_login_count].password, c) != 0)
    {
        printf("\t\t\t两次密码不一致请从新申请\n\n\t\t\t");
        system("PAUSE");
        system("cls");
        printf("\n");
        AddUser();         //有风险的，如果一直第二次输错密码，一直递归下去了
        j = 1;
    }

    if (j)
    {
        return;
    }
    
    printf("\n\t\t\t请输入昵称\n\n\t\t\t  ");
    scanf("%s", client_info[g_login_count].nickname);
    SaveUser();
    printf("\t\t\t\t账号申请成功！！\n\n\t\t\t");
    g_login_count++;
    strcpy(g_add_user_info->users, client_info[g_login_count - 1].asname);
    g_add_user_info->sexes = 0;
    strcpy(g_add_user_info->book[0].name, "0");
    strcpy(g_add_user_info->book[0].time, "0");
    g_add_user_info->r = 100;
    g_add_user_info->Next = NULL;    //
    g_user_info = g_add_user_info;

    SaveData();  //存储用户信息
    
    LoadBorrow(g_pHead);  //
    
    SaveBorrow(g_pHead);   //
    
    system("PAUSE");
}

void FindPassword()
{

}

void EditPassword()
{

}

//登陆
int Login()
{
    g_user_info = NULL;
    //g_add_user_info = new UserNode;
    //g_check_passwd_count = g_login;

    int login_operator = 0;
    int result = 0; //scanf返回的结果，默认结果失败

    while (1)
    {
        PrintUser();
        
        LoadUser();

        LoadData();

        result = scanf("%d", &login_operator);
        if (!result) {
            IsWrong();
            continue; //出错就一致continue,可能存在一直挑不出循环的情况
        }

        //处理用户的操作模式
        switch (login_operator)
        {
        case 1://检查账户
            CheckUser(); 
            break;
        case 2: //添加用户
            /*AddUser(); 
            saveuu(); 
            system("cls");    */
            break;
        case 3:
            /*FindPassword();
            system("cls");    */
            break;
        case 4:
            //EditPassword(); 
            break;
        case 5:
            system("cls");
            printf("\n");
            printf("\t\t\t欢迎下次使用小哥哥的图书管理系统\n"); 
            return 0;
        default:
            system("cls"); 
            //hhk();
            system("cls"); 
            break;
        }



    }
}


int main()
{

    //HideCursor();
    //1、数据加载
    LoadData();
    //2、账号登陆
    if (Login())
    {

    }




    system("pause");

    return 0;

}