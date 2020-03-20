// 堆排序
// 创建大顶堆，然后交换

//static int arr1[] = {9,8,7,6,5,4,3,2,1};


void swap(int a[],int b,int c)
{
    int temp = a[b];
    a[b] = a[c];
    a[c] = temp;

}

void adjustHeap(int arr[],int i,int length)
{
    //先取出当前元素i
    int temp = arr[i];
    for(int k = i*2 + 1;k < length;k = k*2+1)
    {

        //从i节点左节点开始
        if(k + 1 < length && arr[k] < arr[k+1])
        {

            // 如果左子节点小于右子节点，k指向右子节点
            k++;
        }

        if(arr[k] > temp)
        {
            arr[i] = arr[k];
            i = k;

        }
        else
        {
            break;

        }
    }

    arr[i] = temp;

}

void heap_sort(int arr[],int length)
{
    int length1 = length;
    //构建大顶堆
    for(int  i= length1 / 2 - 1;i >=0 ;i--)
    {
        //从第一个非叶子节点从下至上，从右至左调整结构

        adjustHeap(arr,i,length1);
    }

    // 调整堆结构，交换堆顶元素与末尾元素
    for(j = length1 - 1;j>0;j--)
    {
        swap(arr,0,j);
        adjustHeap(arr,0,j);

    }

    

}


int main()
{
    int arr[] = {9,8,7,6,5,4,3,2,1};

    heap_sort(arr,sizeof(arr) / sizeof(int));

    for(int i = 0 ;i < sizeof(arr) / sizeof(int);i++)
    {
        cout<<arr[i]<<" ";

    }

    cout<<endl;


    system("pause");
}
