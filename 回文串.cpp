#include<iostream>
#include<string>
#include <vector>
#include "test1.h"

using namespace std;

class Test1
{
	int x, y;
public:
	Test1(int i, int j = 0)
	{
		x = i;
		y = j;
	}

	int get(int i, int j)
	{
		return i + j;
	}

};

string str2[10];
int    int2[10];
int main()
{
	int test = 1;
	std::cout << "test:" << test << std::endl;
	/*std::cout << "class test" << std::endl;
	Test testClass(1, 2, "dali");
	std::cout << testClass.name << std::endl;
	*/
	const char* ch = "12334";
	std::cout << "len:" << strlen(ch) << std::endl;
	string t_str = "aaa";
	const char* t_char = t_str.c_str();
	cout << "t_char:" << t_char << endl;


	//test ����
	/*
	int arry1[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };
	int (*p)[4];
	p = arry1;
	cout << p << endl;

	Test1 t1(2), t2(4, 6);

	int v1 = 0;
	int *p1 = &v1;
	const int *p2 = p1; //��const���Ը�ֵ��const
	*/
	vector<string> v1{ 10,"hi" };
	cout << v1.size() << endl;

	string str1[10];
	int    int1[10];

	return 0;
}

#if 0
/*************************
*���ڣ�2020.11.03
*˵�������Ĵ� ���������
*���������
**************************/
class Solution
{
public:
    string longestPalindrome(string s)
    {
        if (s.size() == 0 || s.size() < 2)
        {
            return s;
        }

        int max = 0;
        string ret = "";
        
        for (int i = 0; i < s.size();i++)
        {
            for (int j = 1;j < s.size();j++)
            {
                string tmp = s.substr(i, j - i + 1);
                string tmpr(tmp);//������Ӵ���תһ����ԭ���Ա��Ƿ���ͬ
                reverse(tmp.begin(), tmp.end());
                if (tmp == tmpr && tmp.size() > max)
                {
                    max = tmp.size();
                    ret = s.substr(i, j - i + 1);
                }
            }
        }

        return ret;
    }

};

/*������ɢ��*/
class Solution
{
public:
    int max = 0;
    string ret = "";
    void spread(string &s, int left, int right)
    {
        int L = left;
        int R = right;

        while (L >= 0 && R < s.size() && s[L] == s[R])
        {
            if (R - L + 1 > max)
            {
                max = R - L + 1;
                ret = s.substr(L, R - L + 1);
            }

            L--;
            R++;
        }

    }

    string longestPalindrome(string s)
    {
        if (s.size() <= 1)
        {
            return s;
        }

        for (int i = 0;i < s.size();i++)
        {
            spread(s, i, i);    //�����ַ���ɢ
            spread(s, i, i + 1); //���������ַ���ɢ
        }

        return ret;
    }

};

#endif
/** ��̬�滮**/
class Solution
{
public:
    string longestPalindrome(string s)
    {
        if (s.size() == 0)
        {
            return s;
        }

        //��̬�����ڴ�
        int **dp = new int*[s.size()]; //����һ�����״̬������
        for (int i = 0;i < s.size();i++)
        {
            dp[i] = new int[s.size()];
        }

        for (int i = 0;i < s.size();i++)
        {
            for (int j = 0;j < s.size();j++)
            {
                dp[i][j] = 0;
            }
        }

        int max = 0;
        string ret = "";
        for (int i = 0;i < s.size();i++)
        {
            for (int j = 0;j < s.size();j++)   //���˫ѭ�������ж�i��jλ�õ��Ӵ��Ƿ�Ϊ���Ĵ�
            {
                dp[i][j] = s[i] == s[j] && (i - j <= 2 || dp[i - 1][j + 1]);
                //i-j <=2�������Ϊ����Ӵ�Ϊbbʱ���Ǽ���״̬����Ҳ���ɻ���
               //dp[i-1][j+1]�������ж��м���Ӵ��Ƿ�Ϊ���ģ��ܺ����

                if (dp[i][j])
                {
                    if (i - j + 1 > max)
                    {
                        max = i - j + 1;
                        ret = s.substr(j, i - j + 1);
                    }
                }
            }
        }




        for (int i = 0;i < s.size();i++)
        {
            delete[] dp[i];
        }
        delete[] dp;

        return ret;
    }

};