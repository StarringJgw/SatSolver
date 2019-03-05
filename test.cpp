#include "iostream"
#include "fstream"
#include "SudokuSolver.h"
#include "Dpll.h"
#include "CnfParser.h"
#include "myVector.h"

using namespace std;

int most(myVector<int> x) {
    int length = x.Size();
    int tail = length;
    int temp = 0, max = 0, maxNum = 0;
    int currentNum = 0;
    while (tail > 0) {
        temp = 0;
        currentNum = x[tail - 1];
        for (int i = tail; i > 0; i--) {
            if (currentNum == x[i - 1]) {
                temp++;
                x[i - 1] = x[tail - 1];
                tail--;
            }
        }
        if (temp > max) {
            cout << temp << "  " << currentNum << endl;
            max = temp;
            maxNum = currentNum;
        }
    }
    return maxNum;
}
int main(void) {
    myVector<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(2);
    x.push_back(4);
    x.push_back(2);
    x.push_back(3);
    x.push_back(2);
    x.push_back(1);
    x.push_back(1);
    x.push_back(7);
    cout << most(x);
    x.destroy();
    return 0;
}

//#include "stdio.h"
//int main()
//{
//
//    int list[]={1,2,3,4,4,3,2,1,1,2};
//    int length =sizeof(list)/sizeof(int);
//    printf("测试数组为：");
//    for(int i =0;i<length;i++)
//    {
//        printf("%d,",list[i]);
//    }
//    int  *result;
//    result = new int[length];
//    int count = 0;
//    // 这个是剩余可用的总数
//    int has = length;
//    int element;
//    int MaxNum =0;
//    int tempCount;
//    // 循环，直到列表里不再有数据
//    while (has > 0)
//    {
//        printf("\n%d",has);
//        // 拿到最后一个数据
//        element = list[has - 1];
//        // 计数
//        tempCount = 0;
//        // 向前查找相同的
//        for (int j = has - 1; j >= 0; j--)
//        {
//            // 如果找到，则计数加1，然后将数据和末尾交换
//            // 这也是为何要从末尾开始循环的理由
//            if (element == list[j])
//            {
//                tempCount++;
//                // 将当前位置交换为末尾的数据
//                // 注意末尾数据是动态变化的
//                list[j] = list[has - 1];
//                has--;
//            }
//        }
//        printf("\n修改数组为：");
//        for(int i =0;i<length;i++)
//        {
//            printf("%d,",list[i]);
//        }
//        // 如果这个计数最大，则更新输出的数据
//
//
//        if (tempCount > count)
//        {
//            count = tempCount;
//            MaxNum =0;
//            result[MaxNum]=element;
//            //printf("%d,",count);
//            // outValue.clear();
//            //  outValue.add(element);
//        }
//        else if (tempCount == count)
//        {
//            // 否则加入到最大数的列表里
//            // outValue.add(element);
//            MaxNum ++;
//            result[MaxNum]=element;
//            //printf("%d,",count);
//        }
//
//    }
//    printf("\n出现频率最高的次数是:%d 次", count );
//    printf("\n出现频率最高次数的数字是:\n");
//    for(int m =0;m<=MaxNum;m++)
//    {
//        printf("%d,",result[m]);
//    }
//
//    getchar();
//    return 0;
//}