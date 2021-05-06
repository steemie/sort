#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//创建小顶堆，然后逐个删除顶部放到后面，最后按照层序遍历出来的数据就是有序的
//1、时间复杂度：O(nlogn) 2、空间复杂度：O(1) 3、非稳定排序 4、原地排序

//1、稳定排序：如果 a 原本在 b 的前面，且 a == b，排序之后 a 仍然在 b 的前面，则为稳定排序。

//2、非稳定排序：如果 a 原本在 b 的前面，且 a == b，排序之后 a 可能不在 b 的前面，则为非稳定排序。

//3、原地排序：原地排序就是指在排序过程中不申请多余的存储空间，只利用原来存储待排数据的存储空间进行比较和交换的数据排序。

//4、非原地排序：需要利用额外的数组来辅助排序。

//5、时间复杂度：一个算法执行所消耗的时间。

//6、空间复杂度：运行完一个算法所需的内存大小。

/*
void max_heapify(int arry[],int start,int end)
{
    int father = start;
    int son = father * 2  + 1;

}

//初始化
void heap_sort(int arry[],int len)
{
    for (int i = len / 2;i >= 0;i--)
    {
        max_heapify(arry,i,len - 1);
    }

}
*/

static int debug_times = 0;
//堆排序的初始化函数
void HeapAdjust(vector<int> &list_1,int parent,int length)
{
    debug_times++;
    cout << "调试建堆的次数:" << debug_times << endl;

    //保存要下沉的元素
    int tmp = list_1[parent];

    //定位左孩子节点的位置
    int left_child = 2 * parent + 1; //按照顺序数
//        0
//    /        \
//    1         2
//   /\        / \
//   3 4       5  6
    while (left_child <= length)
    {
        //如果右孩子比左孩子大，则定位到右孩子
        if ((left_child + 1 <= length) && list_1[left_child + 1] > list_1[left_child])
        {
            left_child++;
        }

        //创建大顶堆
        //如果孩子节点小于或等于父节点，则下沉结束,不会进行实际的数值交换
        if (list_1[left_child] <= tmp)
        {
            break;
        }

        //否则就进行调整
        list_1[parent] = list_1[left_child];
        parent = left_child;
        left_child = 2 * parent + 1;


    }

    //循环完毕，后赋值
    list_1[parent] = tmp;
}

vector<int> HeapSort(vector<int> list_1)
{
    int length = list_1.size();

    //循环建立初始堆
    for (int i = (length - 2) / 2;i >= 0;i-- )
    {
        HeapAdjust(list_1,i,length - 1);

    }

    cout << "堆排序调整" << endl;
    //进行堆排序
    for (int i = length - 1;i >= 1;i--)
    {
        //把堆顶元素和最后一个元素交换
        int tmp = list_1[i];
        list_1[i] = list_1[0];
        list_1[0] = tmp;
        //把打乱的推进行调证，恢复堆的特性
        HeapAdjust(list_1, 0, i - 1);
    }

    cout << "建完堆后的数据:";
    for (int i = 0;i < length;i++)
    {
        cout << list_1[i] << " ";
    }
    cout << endl;

    return  list_1;
}


int main()
{
    int arry[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int len = (int)sizeof(arry) / sizeof(int);
    vector<int> list_1(arry, arry + 30);
    printf("次数:\n");
    HeapSort(list_1);
    printf("hesssssssssss\n");

    system("pause");
    return 0;
}
