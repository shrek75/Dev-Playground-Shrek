using System.Collections;
using System.Numerics;
using System.Runtime.CompilerServices;

class Program
{

    static void Main(string[] args)
    {
        

    }




}

static class CMySort
{
    // public static void MergeSort(List<int> list, int start, int end)
    // {
    //     MergeSort(list, start, end / 2);
    //     MergeSort(list, end / 2 + 1, end);
    //
    //
    // }

    public static void QuickSort(List<int> list, int start, int end)
    {
        // 재귀 끝나는 조건
        if (end - start < 1) return;

        // pivot 설정
        int pivot = (start + end) / 2;

        // pivot 기준으로 정렬하기
        int i = start;
        int j = end;

        while (true)
        {
            //i j 땡기기
            while (list[i] <= list[pivot] && i != pivot)
                i++;
            while (list[j] >= list[pivot] && j != pivot)
                j--;

            //만나지않앗으면 Swap
            if (i != j)
            {
                int temp = list[i];
                list[i] = list[j];
                list[j] = temp;

                //둘중하나가 pivot이였으면 swap햇으니 pivot도 바꿔주기
                if (i == pivot) pivot = j;
                else if (j == pivot) pivot = i;
            }

            //만났으면 pivot기준으로 정렬끝
            else break;
        }

        QuickSort(list, start, pivot - 1);
        QuickSort(list, pivot + 1, end);

    }
}





