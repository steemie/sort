/**************************************************
*��飺
*
*���ڣ�2020.09.21
*
**************************************************/

//ͷ�ļ�
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<algorithm>

using namespace std;


//�궨����
#define BOOK_SYSTEM_CLIENT_MAX_VERIFY_TIMES (1024)      //ϵͳ�û��˻������֤��У�����

//���ݽṹ

struct library 
{
    int     id;             //ͼ����
    char    name[30];       //ͼ������
    double  price;          //ͼ��۸�
    char    author[30];     //ͼ������
    int     stock;          //ͼ����
    char    preface[2000];  //ͼ����
}stu[100];

//�˻���Ϣ
struct Asccount 
{
    char asname[30];  //�˻���
    char password[12]; //�˻�����
    char nickname[30];  //�˻��ǳ�
}client_info[100];

//������Ϣ
struct Book 
{
    char name[30]; //����
    char time[40]; //ʱ��
};

//�û���Ϣ
typedef struct UserNode 
{
    char            users[30];   //�û�������
    int             sexes;       //�û�
    int             r;           //���û������ж�����Ŀ
    struct Book     book[30];    //�û�����ͼ�����Ϣ
    UserNode        *Next;
}UserInfo;


//ȫ�ֱ���       ��÷ŵ�һ�����л��߳�ʼ����ȥ��ʼ��ģ����
int g_num   = 42;
int g_login_count    = 2;      //��¼�û�����
int g_kk    = g_login_count;   //��¼����
int g_passwd_error_count = 0; //�û���½�������������������֧�����Σ������˻��ͱ�����
int g_login = 0;
int g_login_operator = 0; //��½����ѡ�񣺺˶��˻��������˻����һ����롢�༭����
int g_check_passwd_count = 0; //��½��ʱ��������֤����

char g_login_name[30];


UserInfo *g_user_info       = NULL;    //ȫ���û�������Ϣ
UserInfo *g_add_user_info   = new UserInfo;   //ȫ�������û�������Ϣ
UserInfo *g_pHead           = new UserInfo;   //ͷָ�룬new��������ʱdelete







 //���ع��
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


//���ݴ洢ģ�� 
//�������ݵ��ڴ�
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
*�˻�ģ��
**********************/
//����˺Ų˵�
void PrintUser(void)
{
    printf("\t\t\t************************************\n");
    printf("\t\t\t*    ��¼ �밴 1                   *\n");
    printf("\t\t\t*    ע�����˺� �밴 2             *\n");
    printf("\t\t\t*    �һ����� �밴 3               *\n");
    printf("\t\t\t*    �޸����� �밴 4               *\n");
    printf("\t\t\t*    �˳����� �밴 5               *\n");
    printf("\t\t\t************************************\n");
}

//���˺Ŷ����ڴ���
void LoadUser(void)
{
    int i = 0;
    freopen("fundaccount.txt", "r", stdin);    //�ض������뵽�ļ���
    for (i = 0; i < g_login_count; i++)
    {
        scanf("%s", client_info[i].asname);
        scanf("%s", client_info[i].password);
        scanf("%s", client_info[i].nickname);
    }
    freopen("CON", "r", stdin);    //��������̨
}

//�����Ǵ���
void IsWrong(void)
{
    char s[50];
    gets_s(s);    //gets��gets_sȡ��
    system("cls");
    printf("\t\t\t������󣡣�\n");
    system("PAUSE");
    system("cls");
}

//�û���һϵ�в���
void CheckUser()
{
    int i = 0, flag = 0, K = 0, KK =0 ;
    char ss[30];
    char passwd[10]; //����֧�ֵ�10λ
    printf("\t\t\t\t�������¼�˺ţ�\n\n\t\t\t\t ");
    scanf("%s", ss);
    for (i = 0; i < g_login_count; i++) 
    {
        if (strcmp(client_info[i].asname, ss) == 0) 
        {
            strcpy(g_login_name, ss);  //��½���ҵ��洢�����֣����ñ�־λ�����Ҹ�ֵ ��ȫ�ֱ���
            flag = 1;
            break;
        }
    }

    //���û���ҵ����û���������˻�δע��
    if (!flag) {
        printf("\n\t\t\t\t���˺Ż�δע�ᣡ��\n\n\t\t\t   ");
        system("PAUSE");
        system("cls");
        return;
    }

    //�ҵ�����������
    printf("\t\t\t\t���������룺\n\n\t\t\t\t ");
    scanf("%s", passwd);
    if (strcmp(client_info[i].password, passwd) == 0) 
    {
        //����У����ȷ
        g_check_passwd_count = 0;
        flag = 2;
    }
    if (flag == 1) 
    {
        system("cls");
        printf("\t\t\t\t������󣡣�\n\n\t\t\t   ");
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
            printf("\t\t\t   �������������֤�룺\n");
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
                //�Ż�����֤�����Ӧ������
                verify_code++;
                if (verify_code >= BOOK_SYSTEM_CLIENT_MAX_VERIFY_TIMES)
                {
                    printf("\n\t\t\t��֤�����볬��������������ϸ�˶���֤�벢��������Ƿ�ͨ������\n");
                    system("PAUSE");
                    system("cls");
                    continue;
                }
                printf("\n\t\t\t��֤�����,��������֤����\n");
                system("PAUSE");
                system("cls");

                continue;
            }

            break;  //��֤��У��ɹ�
        }

        //�ߵ������½�Ѿ��ɹ�
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
// �����¼���ص��ڴ�
void LoadBorrow(UserInfo* userInfo)
{
    int i, j;
    UserInfo *p;
    UserInfo *rear = userInfo;
    freopen("borrow.txt", "r", stdin);  //�ض���
    for (i = 0; i < g_kk; i++) 
    {
        p = new UserInfo;
        
        // �ڵ���Ϣ���أ��û���Ҫ�����
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
//�½��˻�
void AddUser()
{
    //�����û��Ļ�����Ϣ�����Ϸ��Ժ󣬴�ŵ����ش�����
    FILE *fp;
    int j = 0, i = 0;
    char c[12], str[30];
    printf("\t\t\t�������˺ţ�\n\n\t\t\t  ");
    scanf("%s", str);

    //����˻��Ƿ����
    for (i = 0; i < g_login_count; i++)
    {
        if (strcmp(client_info[i].asname, str) == 0) 
        {
            printf("\t\t\t���˺��ѱ�ע�ᣬ���������룡��\n\n\t\t\t   ");
            system("PAUSE");
            return;
        }
    }
    strcpy(client_info[g_login_count].asname, str);
    printf("\t\t\t���������루���볤�Ȳ�����ʮ���ַ�����\n\n\t\t\t  ");
    scanf("%s", client_info[g_login_count].password);
    printf("\t\t\t��������һ�����룺\n\n\t\t\t  ");
    scanf("%s", c);

    if (strcmp(client_info[g_login_count].password, c) != 0)
    {
        printf("\t\t\t�������벻һ�����������\n\n\t\t\t");
        system("PAUSE");
        system("cls");
        printf("\n");
        AddUser();         //�з��յģ����һֱ�ڶ���������룬һֱ�ݹ���ȥ��
        j = 1;
    }

    if (j)
    {
        return;
    }
    
    printf("\n\t\t\t�������ǳ�\n\n\t\t\t  ");
    scanf("%s", client_info[g_login_count].nickname);
    SaveUser();
    printf("\t\t\t\t�˺�����ɹ�����\n\n\t\t\t");
    g_login_count++;
    strcpy(g_add_user_info->users, client_info[g_login_count - 1].asname);
    g_add_user_info->sexes = 0;
    strcpy(g_add_user_info->book[0].name, "0");
    strcpy(g_add_user_info->book[0].time, "0");
    g_add_user_info->r = 100;
    g_add_user_info->Next = NULL;    //
    g_user_info = g_add_user_info;

    SaveData();  //�洢�û���Ϣ
    
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

//��½
int Login()
{
    g_user_info = NULL;
    //g_add_user_info = new UserNode;
    //g_check_passwd_count = g_login;

    int login_operator = 0;
    int result = 0; //scanf���صĽ����Ĭ�Ͻ��ʧ��

    while (1)
    {
        PrintUser();
        
        LoadUser();

        LoadData();

        result = scanf("%d", &login_operator);
        if (!result) {
            IsWrong();
            continue; //�����һ��continue,���ܴ���һֱ������ѭ�������
        }

        //�����û��Ĳ���ģʽ
        switch (login_operator)
        {
        case 1://����˻�
            CheckUser(); 
            break;
        case 2: //����û�
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
            printf("\t\t\t��ӭ�´�ʹ��С����ͼ�����ϵͳ\n"); 
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
    //1�����ݼ���
    LoadData();
    //2���˺ŵ�½
    if (Login())
    {

    }




    system("pause");

    return 0;

}