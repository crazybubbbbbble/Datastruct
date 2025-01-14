#pragma once
#include <chrono>  
#include <ctime>   // 用于 time()
#include "Sqlist.h"
using namespace chrono;

void swap(Sqlist* L, int i, int j)//交换
{
	int temp = L->data[i];
	L->data[i] = L->data[j];
	L->data[j] = temp;
}

//顺序查找 O(n) ASL成功=（n+1）/2    ASL失败=n
int Sequential_Search(Sqlist* L) {
	int data;
	cout << "Enter the data to be searched." << endl;
	cin >> data;
	cout << "Start Search......" << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	for (int i = 0; i < L->length; i++) 
	{
		if (L->data[i] == data) 
		{
			cout << "Position: " << i << endl;
			// 记录结束时间
			auto stop = high_resolution_clock::now();
			// 计算排序所用的时间
			auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
			cout << "Sequential_Search completed!" << endl;
			cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
			return i + 1; // 返回元素的位置（从1开始计数）
		}
	}
	// 记录结束时间
	auto stop = high_resolution_clock::now();
	// 计算排序所用的时间
	auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
	cout << data << " not found in the Sqlist." << endl;
	cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
	return -1; // 如果未找到目标元素，返回-1
}

//折半查找,表中数据必须是有序的 O(log2n)
int Half_Search(Sqlist* L)//非递归
{
	int data;
	cout << "Enter the data to be searched." << endl;
	cin >> data;
	cout << "Start Search......" << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	int low = 0, high = L->length - 1;
	while (low <= high)
	{
		int mid = low + (high-low) / 2;
		if (L->data[mid] == data)
		{
			cout << "Position: " << mid << endl;
			// 记录结束时间
			auto stop = high_resolution_clock::now();
			// 计算排序所用的时间
			auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
			cout << "Half_Search completed!" << endl;
			cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
			return mid;
		}
		else if (L->data[mid] < data)
			low=mid+1;
		else
			high=mid-1;
	}
	// 记录结束时间
	auto stop = high_resolution_clock::now();
	// 计算排序所用的时间
	auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
	cout << data << " not found in the Sqlist." << endl;
	cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
	return -1;
}

int Half_Search_Recursive(Sqlist* L, int data, int low, int high)//递归
{
	if (low > high)
		return -1;

	int mid = low + (high-low) / 2;
	if (L->data[mid] == data)
		return mid;
	else if (L->data[mid] < data)
		return Half_Search_Recursive(L, data, mid + 1, high);
	else
		return Half_Search_Recursive(L, data, low, mid - 1);
}
void Half_Search_Recursive_Wrapper(Sqlist* L)
{
	int data;
	cout << "Enter the data to be searched." << endl;
	cin >> data;
	cout << "Start Search......" << endl;
	// 记录开始时间
	auto start = high_resolution_clock::now();
	int result=Half_Search_Recursive(L, data, 0, L->length - 1);
	if (result != -1)
	{
		cout << "Position: " << result << endl;
		// 记录结束时间
		auto stop = high_resolution_clock::now();
		// 计算排序所用的时间
		auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
		cout << "Half_Search completed!" << endl;
		cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
	}
	else 
	{
		// 记录结束时间
		auto stop = high_resolution_clock::now();
		// 计算排序所用的时间
		auto duration = duration_cast<microseconds>(stop - start);  // 计算微秒
		cout << data << " not found in the Sqlist." << endl;
		cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
	}
	
}

// 哈希函数：除留余数法   ASL成功=每个数探测次数/总数    ASL失败=（n+1）/2
int hashFunction(int key, int tableSize) {
	// 选择一个合适的质数 p（通常小于哈希表大小）
	int p = 7; // 例如，选择 p = 7

	// 计算哈希值
	int hashValue = key % p;

	// 确保哈希值为非负数
	if (hashValue < 0) {
		hashValue += p;
	}

	return hashValue;
}