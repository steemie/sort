//快排
int GetPatition(int arr[], int left, int right)
{

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
