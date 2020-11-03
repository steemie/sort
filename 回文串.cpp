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


	//test 数组
	/*
	int arry1[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };
	int (*p)[4];
	p = arry1;
	cout << p << endl;

	Test1 t1(2), t2(4, 6);

	int v1 = 0;
	int *p1 = &v1;
	const int *p2 = p1; //非const可以赋值给const
	*/
	vector<string> v1{ 10,"hi" };
	cout << v1.size() << endl;

	string str1[10];
	int    int1[10];

	return 0;
}

#if 0
/*************************
*日期：2020.11.03
*说明：回文串 ：暴力求解
*结果：超限
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
                string tmpr(tmp);//将这个子串反转一下与原串对比是否相同
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

/*中心扩散法*/
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
            spread(s, i, i);    //单个字符扩散
            spread(s, i, i + 1); //相邻两个字符扩散
        }

        return ret;
    }

};

#endif
/** 动态规划**/
class Solution
{
public:
    string longestPalindrome(string s)
    {
        if (s.size() == 0)
        {
            return s;
        }

        //动态分配内存
        int **dp = new int*[s.size()]; //创建一个存放状态的数据
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
            for (int j = 0;j < s.size();j++)   //这个双循环是在判断i到j位置的子串是否为回文串
            {
                dp[i][j] = s[i] == s[j] && (i - j <= 2 || dp[i - 1][j + 1]);
                //i-j <=2这句是因为如果子串为bb时就是极限状态，他也构成回文
               //dp[i-1][j+1]这句就是判断中间的子串是否为回文，很好理解

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