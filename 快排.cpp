//快排
int GetPatition(int arr[], int left, int right)
{

    //优化一下，加个随机数
    srand(int(time(0)));
    int s = rand() % (right - left + 1) + left; // +1是因为，产生的随机数可以取到与这个范围相等的值
    int tmp = arr[s];
    arr[s] = arr[left];
    arr[left] = tmp;
    //优化结束
    
    int base = arr[left];


    while (left < right)
    {
        while (left < right && arr[right] >= base)
        {
            right--;
        }

        arr[left] = arr[right];

        while (left < right && arr[left] <= base)
        {
            left++;
        }
        arr[right] = arr[left];

    }
    arr[left] = base;

    return left;

}

void QuickSortY(int arr[], int left, int right)
{
    if (left < right)
    {
        int pation = GetPatition(arr, left, right);
        QuickSortY(arr, left, pation - 1);
        QuickSortY(arr, pation + 1, right);
    }


}
