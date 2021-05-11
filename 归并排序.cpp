#include<iostream>
#include<vector>

using namespace std;

void MergeKernal(vector<int> &input,int left,int mid,int right,vector<int> &out)
{
    int i = left;
    int j = mid + 1;
    int k = 0;  //临时存放合并序列的下表

    while (i <= mid && j <= right)
    {
        //判断两段序列取出的数据哪个更小，并存入out中
        if (input[i] <= input[j])
        {
            out[k++] = input[i++];

        }
        else
        {
            out[k++] = input[j++];
        }
    }

    //若第一段序列还没扫描完，将其全部放入out
    while (i <= mid)
    {
        out[k++] = input[i++];
    }

    // 若第二段序列还没扫描完，将其全部复制到合并序列
    while (j <= right)
    {
        out[k++] = input[j++];
    }

    k = 0;
    //全部放入原来序列
    while (left <= right) {
        input[left++] = out[k++];
    }

}

void MergeSortBuild(vector<int> &input,int left,int right,vector<int> &out)
{
    if (left < right)
    {
        int mid = (right + left) >> 1;
        MergeSortBuild(input, left, mid, out);
        MergeSortBuild(input, mid + 1,right,out);
        //合并
        MergeKernal(input,left,mid,right,out);

    }

}

void MergeSortTest(vector<int> &input)
{
    //排序前先申请好一个数组
    vector<int> cpy_out(input.size());
    MergeSortBuild(input,0,input.size() - 1,cpy_out);
}


void main_SortMergecpp() {
    int arr[] = { 6, 4, 8, 9, 2, 3, 1 };
    vector<int> test(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "排序前:";
    for (int i = 0; i < test.size(); i++) {
        cout << test[i] << " ";
    }
    cout << endl;

    vector<int> result = test;
    MergeSortTest(result);
    cout << "排序后:";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    system("pause");
}

//归并排序和快速排序都是利用分治的思想，代码都通过递归来实现，过程非常相似。
//归并排序非常稳定，时间复杂度始终都是 O(nlogn)，但不是原地排序；
//快速排序虽然最坏情况下时间复杂度为 O(n2)，但平均情况下时间复杂度为 O(nlogn)，
//最坏情况发生的概率也比较小，而且是原地排序算法，因此应用得更加广泛。
