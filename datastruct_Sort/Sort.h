#pragma once
#include <iostream>
#include <chrono>  
#include <cstdlib> // 用于 rand() 和 srand()
#include <ctime>   // 用于 time()
using namespace std;
using namespace chrono;

#define Sqlist_maxsize 200000

typedef struct Sqlist {
	int* data;
	int length;
};

void Init_sqlist(Sqlist* L)//顺序表
{
	L->data = new int[Sqlist_maxsize];
	L->length = 0;
}

void display_Sqlist(Sqlist* L) {
	cout << "Sqlist : ";
	for (int i = 1; i <= L->length; i++) {
		cout << L->data[i] << " ";
	}
	cout << endl << "Count : " << L->length << endl;
}

void set_Sqlist(Sqlist* L, int n) {
	Init_sqlist(L);
	cout << "Generating " << n << " random numbers..." << endl;
	srand(time(0)); // 初始化随机数种子
	for (int i = 1; i <= n; i++) {
		L->data[i] = rand() % 1000; // 生成 0 到 99999 的随机数
		L->length++;
	}
	cout << "Random data generated and stored in Sqlist." << endl;
	// display_Sqlist(L); // 如果数据量太大，可以不打印
}

int Insert_Sqlist(Sqlist* L, int position, int newdata) {
	cout << "Insert " << newdata << " into the position " << position << endl;
	if (position < 1 || position > L->length + 1) {
		cout << "Error position!!" << endl;
		return 0;
	}
	if (L->length == Sqlist_maxsize) {
		cout << "Full list!!" << endl;
		return -1;
	}
	for (int j = L->length; j > position - 1; j--) { // 修改循环边界
		L->data[j] = L->data[j - 1];
	}
	L->data[position - 1] = newdata;
	L->length++;
	cout << "Correct inserting!!!" << endl;
	display_Sqlist(L);
	return 1;
}

int Delete_Sqlist(Sqlist* L, int position) {
	cout << "Delete the data in the position " << position << endl;
	if (position < 1 || position > L->length) {
		cout << "Error position!!" << endl;
		return 0;
	}
	for (int j = position; j < L->length; j++) { // 修改循环边界
		L->data[j - 1] = L->data[j];
	}
	L->length--;
	cout << "Correct deleting" << endl;
	display_Sqlist(L);
	return 1;
}

int Search_Sqlist(Sqlist* L, int position)//查照
{
	if (position<1 || position>L->length + 1)//检查插入位置
	{
		cout << "Error pisition!!" << endl;
		return 0;
	}
	if (L->length == Sqlist_maxsize)//判满
	{
		cout << "Full list!!" << endl;
		return -1;
	}
	cout << "The data is: " << L->data[position - 1] << endl;//查找
}

int Change_Sqlist(Sqlist* L, int position, int newdata)//更改数据
{
	if (position<1 || position>L->length + 1)//检查插入位置
	{
		cout << "Error pisition!!" << endl;
		return 0;
	}
	if (L->length == Sqlist_maxsize)//判满
	{
		cout << "Full list!!" << endl;
		return -1;
	}
	L->data[position - 1] = newdata;//更改
	cout << "Correct changing" << endl;
	display_Sqlist(L);
}

void Free_sqlist(Sqlist* L) {
	delete[] L->data; // 释放动态分配的数组
	L->data = nullptr; // 将指针设置为nullptr以避免悬空指针
}


void swap(Sqlist* L, int i, int j)//交换
{
	int temp = L->data[i];
	L->data[i] = L->data[j];
	L->data[j] = temp;
}


//插入排序
void Straight_Insert_Sort(Sqlist* L)//直接插入排序
{
	cout << "Start InsertionSort..." << endl;
	auto start = high_resolution_clock::now();// 记录开始时间

	for (int i = 1; i <= L->length; i++) {  
		L->data[0] = L->data[i];  // 当前要插入的元素
		int j = i - 1;

		// 查找插入位置，并将元素移动
		while (j >= 0 && L->data[j] > L->data[0]) {
			L->data[j + 1] = L->data[j];  // 向右移动元素
			j--;
		}

		// 插入当前元素
		L->data[j + 1] = L->data[0];
		  
	}
	auto stop = high_resolution_clock::now();	// 记录结束时间
	display_Sqlist(L);
	auto duration = duration_cast<microseconds>(stop - start); 	// 计算排序所用的时间
	cout << "InsertionSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl<<endl;
}

void Half_Insert_Sort(Sqlist* L)//折半插入排序
{
	cout << "Start Half_Insert_Sort......" << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	for (int i = 2; i <= L->length; i++)
	{
		L->data[0] = L->data[i];
		int high = i - 1;
		int low = 1;
		while (low <= high)//寻找插入位置
		{
			int middle = (high + low) / 2;
			if (L->data[0]< L->data[middle])
			{
				high = middle - 1;
			}
			else {
				low = middle + 1;
			}
		}
		for (int j = i - 1; j > high+1; j--)//后移
		{
			L->data[j + 1] = L->data[j];
		}
		L->data[high + 1] = L->data[0];//插入
	}
	// 记录结束时间
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	// 计算排序所用的时间
	auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
	cout << "Half_Insert_Sort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

void Shell_Sort(Sqlist* L)//希尔排序
{
	cout << "Start ShellSort..." << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	int Gap = L->length/2;
	while (Gap > 0)
	{
		for (int i = Gap; i <= L->length; i++)
		{
			L->data[0] = L->data[i];
			int j = i;
			while (j > Gap && L->data[j - Gap] > L->data[0])
			{
				L->data[j] = L->data[j - Gap];
				j -= Gap; 
			}
			L->data[j] = L->data[0];
		}
		
		Gap /= 2; 
	}
	// 记录结束时间
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	// 计算排序所用的时间
	auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
	cout << "ShellSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl<<endl;
}

//选择排序
void Simple_Selection_Sort(Sqlist* L)//简单选择排序
{
	cout << "Start Simple_Selection_Sort......" << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	for (int i = 1; i < L->length; i++) {
		int minIndex = i;
		// 找到未排序部分的最小值
		for (int j = i + 1; j <= L->length; j++) {
			if (L->data[j] < L->data[minIndex]) {
				minIndex = j;
			}
		}

		// 如果minIndex变化，交换当前元素和最小值
		if (minIndex != i) {
			int temp = L->data[i];
			L->data[i] = L->data[minIndex];
			L->data[minIndex] = temp;
		}
	}
	// 记录结束时间
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	// 计算排序所用的时间
	auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
	cout << "Simple_Selection_Sort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

void HeapAdjust(Sqlist* L, int s, int m) {//堆排序
	int temp = L->data[s]; // 保存当前节点值
	for (int j = 2 * s; j <= m; j *= 2) { // 沿关键字较大的孩子节点向下筛选
		if (j < m&& L->data[j] < L->data[j + 1]) {
			++j; // j为关键字较大的孩子节点的下标
		}
		if (temp >= L->data[j]) {
			break; // 如果当前节点大于等于孩子节点，则不需要调整
		}
		L->data[s] = L->data[j]; // 将孩子节点上移
		s = j; // 继续向下调整
	}
	L->data[s] = temp; // 将temp放到最终位置
}
void HeapSort(Sqlist* L) {
	cout << "Start HeapSort......" << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	// 构建大顶堆
	for (int i = L->length / 2; i > 0; --i) {
		HeapAdjust(L, i, L->length);
	}

	// 逐步将堆顶元素与末尾元素交换，并重新调整堆
	for (int i = L->length; i > 1; --i) {
		swap(L, 1, i); // 将堆顶元素与当前末尾元素交换
		HeapAdjust(L, 1, i - 1); // 调整剩余元素为大顶堆
	}
	// 记录结束时间
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	// 计算排序所用的时间
	auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
	cout << "Simple_Selection_Sort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

//交换排序
void Bubble_Sort(Sqlist* L) //冒泡排序
{
	cout << "Start BubbleSort..." << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	for (int i = 0; i < L->length - 1; i++) {  // 控制排序的轮数
		for (int j = 0; j < L->length - 1 - i; j++) {  // 每轮比较的次数
			if (L->data[j] > L->data[j + 1]) {
				// 如果当前元素大于下一个元素，则交换它们
				int temp = L->data[j];
				L->data[j] = L->data[j + 1];
				L->data[j + 1] = temp;
			}
		}
	}
	// 记录结束时间
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
	cout << "BubbleSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

int MedianOfThree(Sqlist* L, int low, int high) {//取头尾，中位数，三数取中优化key的选择
	int mid = low + (high - low) / 2;
	if (L->data[low] > L->data[mid]) swap(L, low, mid);
	if (L->data[low] > L->data[high]) swap(L, low, high);
	if (L->data[mid] > L->data[high]) swap(L, mid, high);
	return mid; // 返回中位数的位置
}

void Fast(Sqlist* L,int low,int high)
{
	int i = low, j = high;
	int key = MedianOfThree(L, low, high); // 选择基准值;
	if (low >= high)
		return;
	while (i != j)
	{
		while (key <= L->data[j] && i < j)
			j--;
		while (key >= L->data[i] && i < j)
			i++;
		if (i < j)
			swap(L, i, j);
	}
	//插入基准值
	swap(L, low, i);
	Fast(L, low, i - 1);
	Fast(L, i + 1, high);
}//快速排序

void Fast_Sort(Sqlist* L)
{
	cout << "Start FastSort..." << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	Fast(L, 1, L->length);
	// 记录结束时间
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
	cout << "FastSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

//归并排序
void Merge(Sqlist* L, int low, int mid, int high) {// 合并两个有序子序列
	int* temp = new int[high - low + 1]; // 临时数组存放合并结果
	int i = low;    // 左子序列的起始位置
	int j = mid + 1; // 右子序列的起始位置
	int k = 0;      // 临时数组的索引

	// 合并两个有序子序列
	while (i <= mid && j <= high) {
		if (L->data[i] <= L->data[j]) {
			temp[k++] = L->data[i++];
		}
		else {
			temp[k++] = L->data[j++];
		}
	}

	// 将左子序列剩余部分复制到临时数组
	while (i <= mid) {
		temp[k++] = L->data[i++];
	}

	// 将右子序列剩余部分复制到临时数组
	while (j <= high) {
		temp[k++] = L->data[j++];
	}

	// 将临时数组中的内容复制回原数组
	for (i = low, k = 0; i <= high; i++, k++) {
		L->data[i] = temp[k];
	}

	delete[] temp; // 释放临时数组
}
void MergeSort(Sqlist* L, int low, int high) {// 归并排序递归函数
	if (low < high) {
		int mid = (low + high) / 2; // 计算中间位置
		MergeSort(L, low, mid);     // 对左子序列递归排序
		MergeSort(L, mid + 1, high); // 对右子序列递归排序
		Merge(L, low, mid, high);    // 合并两个有序子序列
	}
}
void MergeSort(Sqlist* L) {// 归并排序的封装函数
	cout << "Start MergeSort..." << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	if (L->length == 0) {
		cout << "Empty list!" << endl;
		return;
	}
	MergeSort(L, 1, L->length); // 从下标1开始排序
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
	cout << "MergeSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

//基数排序
int getMaxDigits(Sqlist* L) {// 获取数组中最大值的位数
	int maxVal = L->data[1];
	for (int i = 2; i <= L->length; i++) {
		if (L->data[i] > maxVal) {
			maxVal = L->data[i];
		}
	}
	int digits = 0;
	while (maxVal != 0) {
		digits++;
		maxVal /= 10;
	}
	return digits;
}
void RadixSort(Sqlist* L) {
	cout << "Start RadixSort..." << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	if (L->length == 0) {
		cout << "Empty list!" << endl;
		return;
	}

	int maxDigits = getMaxDigits(L); // 获取最大位数
	int radix = 1; // 基数，初始为1（个位）

	// 创建10个桶（0-9）
	int* bucket = new int[Sqlist_maxsize];
	int count[10] = { 0 }; // 记录每个桶中元素的个数

	// 从个位到最高位依次排序
	for (int d = 1; d <= maxDigits; d++) {
		// 初始化计数器
		for (int i = 0; i < 10; i++) {
			count[i] = 0;
		}

		// 统计每个桶中元素的个数
		for (int i = 1; i <= L->length; i++) {
			int digit = (L->data[i] / radix) % 10;
			count[digit]++;
		}

		// 计算每个桶的结束位置
		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}

		// 将元素放入桶中
		for (int i = L->length; i >= 1; i--) {
			int digit = (L->data[i] / radix) % 10;
			bucket[count[digit] - 1] = L->data[i];
			count[digit]--;
		}

		// 将桶中的元素复制回原数组
		for (int i = 0; i < L->length; i++) {
			L->data[i + 1] = bucket[i];
		}

		radix *= 10; // 处理下一位
	}

	delete[] bucket; // 释放桶的内存
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
	cout << "RadixSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

//外部排序
void External_Sort(Sqlist* L)
{
	//用于处理大规模数据的排序算法，当数据量太大而无法全部加载到内存时，外部排序通过将数据分成小块，在内存中排序这些小块，然后将它们合并成一个有序的序列。常见的外部排序算法包括多路归并排序（Multiway Merge Sort）。
	//基于文件的外部排序
	//我懒得ai了......
}