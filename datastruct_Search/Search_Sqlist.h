#pragma once
#include <chrono>  
#include <ctime>   // ���� time()
#include "Sqlist.h"
using namespace chrono;

void swap(Sqlist* L, int i, int j)//����
{
	int temp = L->data[i];
	L->data[i] = L->data[j];
	L->data[j] = temp;
}

//˳����� O(n) ASL�ɹ�=��n+1��/2    ASLʧ��=n
int Sequential_Search(Sqlist* L) {
	int data;
	cout << "Enter the data to be searched." << endl;
	cin >> data;
	cout << "Start Search......" << endl;
	// ��¼��ʼʱ��
	auto start = high_resolution_clock::now();
	for (int i = 0; i < L->length; i++) 
	{
		if (L->data[i] == data) 
		{
			cout << "Position: " << i << endl;
			// ��¼����ʱ��
			auto stop = high_resolution_clock::now();
			// �����������õ�ʱ��
			auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
			cout << "Sequential_Search completed!" << endl;
			cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
			return i + 1; // ����Ԫ�ص�λ�ã���1��ʼ������
		}
	}
	// ��¼����ʱ��
	auto stop = high_resolution_clock::now();
	// �����������õ�ʱ��
	auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
	cout << data << " not found in the Sqlist." << endl;
	cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
	return -1; // ���δ�ҵ�Ŀ��Ԫ�أ�����-1
}

//�۰����,�������ݱ���������� O(log2n)
int Half_Search(Sqlist* L)//�ǵݹ�
{
	int data;
	cout << "Enter the data to be searched." << endl;
	cin >> data;
	cout << "Start Search......" << endl;
	// ��¼��ʼʱ��
	auto start = high_resolution_clock::now();
	int low = 0, high = L->length - 1;
	while (low <= high)
	{
		int mid = low + (high-low) / 2;
		if (L->data[mid] == data)
		{
			cout << "Position: " << mid << endl;
			// ��¼����ʱ��
			auto stop = high_resolution_clock::now();
			// �����������õ�ʱ��
			auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
			cout << "Half_Search completed!" << endl;
			cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
			return mid;
		}
		else if (L->data[mid] < data)
			low=mid+1;
		else
			high=mid-1;
	}
	// ��¼����ʱ��
	auto stop = high_resolution_clock::now();
	// �����������õ�ʱ��
	auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
	cout << data << " not found in the Sqlist." << endl;
	cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
	return -1;
}

int Half_Search_Recursive(Sqlist* L, int data, int low, int high)//�ݹ�
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
	// ��¼��ʼʱ��
	auto start = high_resolution_clock::now();
	int result=Half_Search_Recursive(L, data, 0, L->length - 1);
	if (result != -1)
	{
		cout << "Position: " << result << endl;
		// ��¼����ʱ��
		auto stop = high_resolution_clock::now();
		// �����������õ�ʱ��
		auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
		cout << "Half_Search completed!" << endl;
		cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
	}
	else 
	{
		// ��¼����ʱ��
		auto stop = high_resolution_clock::now();
		// �����������õ�ʱ��
		auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
		cout << data << " not found in the Sqlist." << endl;
		cout << "Search time: " << duration.count() << " microseconds" << endl << endl;
	}
	
}

// ��ϣ����������������   ASL�ɹ�=ÿ����̽�����/����    ASLʧ��=��n+1��/2
int hashFunction(int key, int tableSize) {
	// ѡ��һ�����ʵ����� p��ͨ��С�ڹ�ϣ���С��
	int p = 7; // ���磬ѡ�� p = 7

	// �����ϣֵ
	int hashValue = key % p;

	// ȷ����ϣֵΪ�Ǹ���
	if (hashValue < 0) {
		hashValue += p;
	}

	return hashValue;
}