#include"Sort.h"

int main()
{
	Sqlist L;
	set_Sqlist(&L,1000);

	//Straight_Insert_Sort(&L);
	//Half_Insert_Sort(&L);
	//Shell_Sort(&L);

	//Simple_Selection_Sort(&L);
	//HeapSort(&L);

	//Bubble_Sort(&L);
	//Fast_Sort(&L);

	//MergeSort(&L);

	RadixSort(&L);

}
//输入示例：67 25 83 45 90 12 38 76 54 89 66 81 41 22 93 51 59 31 60 8 3 14 48 71 85 74 30 61 19 77

