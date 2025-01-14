#pragma once
#include <iostream>
#include <chrono>  
#include <cstdlib> // ���� rand() �� srand()
#include <ctime>   // ���� time()
using namespace std;
using namespace chrono;

#define Sqlist_maxsize 200000

typedef struct Sqlist {
	int* data;
	int length;
};

void Init_sqlist(Sqlist* L)//˳���
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
	srand(time(0)); // ��ʼ�����������
	for (int i = 1; i <= n; i++) {
		L->data[i] = rand() % 1000; // ���� 0 �� 99999 �������
		L->length++;
	}
	cout << "Random data generated and stored in Sqlist." << endl;
	// display_Sqlist(L); // ���������̫�󣬿��Բ���ӡ
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
	for (int j = L->length; j > position - 1; j--) { // �޸�ѭ���߽�
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
	for (int j = position; j < L->length; j++) { // �޸�ѭ���߽�
		L->data[j - 1] = L->data[j];
	}
	L->length--;
	cout << "Correct deleting" << endl;
	display_Sqlist(L);
	return 1;
}

int Search_Sqlist(Sqlist* L, int position)//����
{
	if (position<1 || position>L->length + 1)//������λ��
	{
		cout << "Error pisition!!" << endl;
		return 0;
	}
	if (L->length == Sqlist_maxsize)//����
	{
		cout << "Full list!!" << endl;
		return -1;
	}
	cout << "The data is: " << L->data[position - 1] << endl;//����
}

int Change_Sqlist(Sqlist* L, int position, int newdata)//��������
{
	if (position<1 || position>L->length + 1)//������λ��
	{
		cout << "Error pisition!!" << endl;
		return 0;
	}
	if (L->length == Sqlist_maxsize)//����
	{
		cout << "Full list!!" << endl;
		return -1;
	}
	L->data[position - 1] = newdata;//����
	cout << "Correct changing" << endl;
	display_Sqlist(L);
}

void Free_sqlist(Sqlist* L) {
	delete[] L->data; // �ͷŶ�̬���������
	L->data = nullptr; // ��ָ������Ϊnullptr�Ա�������ָ��
}


void swap(Sqlist* L, int i, int j)//����
{
	int temp = L->data[i];
	L->data[i] = L->data[j];
	L->data[j] = temp;
}


//��������
void Straight_Insert_Sort(Sqlist* L)//ֱ�Ӳ�������
{
	cout << "Start InsertionSort..." << endl;
	auto start = high_resolution_clock::now();// ��¼��ʼʱ��

	for (int i = 1; i <= L->length; i++) {  
		L->data[0] = L->data[i];  // ��ǰҪ�����Ԫ��
		int j = i - 1;

		// ���Ҳ���λ�ã�����Ԫ���ƶ�
		while (j >= 0 && L->data[j] > L->data[0]) {
			L->data[j + 1] = L->data[j];  // �����ƶ�Ԫ��
			j--;
		}

		// ���뵱ǰԪ��
		L->data[j + 1] = L->data[0];
		  
	}
	auto stop = high_resolution_clock::now();	// ��¼����ʱ��
	display_Sqlist(L);
	auto duration = duration_cast<microseconds>(stop - start); 	// �����������õ�ʱ��
	cout << "InsertionSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl<<endl;
}

void Half_Insert_Sort(Sqlist* L)//�۰��������
{
	cout << "Start Half_Insert_Sort......" << endl;
	// ��¼��ʼʱ��
	auto start = high_resolution_clock::now();
	for (int i = 2; i <= L->length; i++)
	{
		L->data[0] = L->data[i];
		int high = i - 1;
		int low = 1;
		while (low <= high)//Ѱ�Ҳ���λ��
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
		for (int j = i - 1; j > high+1; j--)//����
		{
			L->data[j + 1] = L->data[j];
		}
		L->data[high + 1] = L->data[0];//����
	}
	// ��¼����ʱ��
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	// �����������õ�ʱ��
	auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
	cout << "Half_Insert_Sort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

void Shell_Sort(Sqlist* L)//ϣ������
{
	cout << "Start ShellSort..." << endl;
	// ��¼��ʼʱ��
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
	// ��¼����ʱ��
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	// �����������õ�ʱ��
	auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
	cout << "ShellSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl<<endl;
}

//ѡ������
void Simple_Selection_Sort(Sqlist* L)//��ѡ������
{
	cout << "Start Simple_Selection_Sort......" << endl;
	// ��¼��ʼʱ��
	auto start = high_resolution_clock::now();
	for (int i = 1; i < L->length; i++) {
		int minIndex = i;
		// �ҵ�δ���򲿷ֵ���Сֵ
		for (int j = i + 1; j <= L->length; j++) {
			if (L->data[j] < L->data[minIndex]) {
				minIndex = j;
			}
		}

		// ���minIndex�仯��������ǰԪ�غ���Сֵ
		if (minIndex != i) {
			int temp = L->data[i];
			L->data[i] = L->data[minIndex];
			L->data[minIndex] = temp;
		}
	}
	// ��¼����ʱ��
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	// �����������õ�ʱ��
	auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
	cout << "Simple_Selection_Sort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

void HeapAdjust(Sqlist* L, int s, int m) {//������
	int temp = L->data[s]; // ���浱ǰ�ڵ�ֵ
	for (int j = 2 * s; j <= m; j *= 2) { // �عؼ��ֽϴ�ĺ��ӽڵ�����ɸѡ
		if (j < m&& L->data[j] < L->data[j + 1]) {
			++j; // jΪ�ؼ��ֽϴ�ĺ��ӽڵ���±�
		}
		if (temp >= L->data[j]) {
			break; // �����ǰ�ڵ���ڵ��ں��ӽڵ㣬����Ҫ����
		}
		L->data[s] = L->data[j]; // �����ӽڵ�����
		s = j; // �������µ���
	}
	L->data[s] = temp; // ��temp�ŵ�����λ��
}
void HeapSort(Sqlist* L) {
	cout << "Start HeapSort......" << endl;
	// ��¼��ʼʱ��
	auto start = high_resolution_clock::now();
	// �����󶥶�
	for (int i = L->length / 2; i > 0; --i) {
		HeapAdjust(L, i, L->length);
	}

	// �𲽽��Ѷ�Ԫ����ĩβԪ�ؽ����������µ�����
	for (int i = L->length; i > 1; --i) {
		swap(L, 1, i); // ���Ѷ�Ԫ���뵱ǰĩβԪ�ؽ���
		HeapAdjust(L, 1, i - 1); // ����ʣ��Ԫ��Ϊ�󶥶�
	}
	// ��¼����ʱ��
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	// �����������õ�ʱ��
	auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
	cout << "Simple_Selection_Sort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

//��������
void Bubble_Sort(Sqlist* L) //ð������
{
	cout << "Start BubbleSort..." << endl;
	// ��¼��ʼʱ��
	auto start = high_resolution_clock::now();
	for (int i = 0; i < L->length - 1; i++) {  // �������������
		for (int j = 0; j < L->length - 1 - i; j++) {  // ÿ�ֱȽϵĴ���
			if (L->data[j] > L->data[j + 1]) {
				// �����ǰԪ�ش�����һ��Ԫ�أ��򽻻�����
				int temp = L->data[j];
				L->data[j] = L->data[j + 1];
				L->data[j + 1] = temp;
			}
		}
	}
	// ��¼����ʱ��
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
	cout << "BubbleSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

int MedianOfThree(Sqlist* L, int low, int high) {//ȡͷβ����λ��������ȡ���Ż�key��ѡ��
	int mid = low + (high - low) / 2;
	if (L->data[low] > L->data[mid]) swap(L, low, mid);
	if (L->data[low] > L->data[high]) swap(L, low, high);
	if (L->data[mid] > L->data[high]) swap(L, mid, high);
	return mid; // ������λ����λ��
}

void Fast(Sqlist* L,int low,int high)
{
	int i = low, j = high;
	int key = MedianOfThree(L, low, high); // ѡ���׼ֵ;
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
	//�����׼ֵ
	swap(L, low, i);
	Fast(L, low, i - 1);
	Fast(L, i + 1, high);
}//��������

void Fast_Sort(Sqlist* L)
{
	cout << "Start FastSort..." << endl;
	// ��¼��ʼʱ��
	auto start = high_resolution_clock::now();
	Fast(L, 1, L->length);
	// ��¼����ʱ��
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
	cout << "FastSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

//�鲢����
void Merge(Sqlist* L, int low, int mid, int high) {// �ϲ���������������
	int* temp = new int[high - low + 1]; // ��ʱ�����źϲ����
	int i = low;    // �������е���ʼλ��
	int j = mid + 1; // �������е���ʼλ��
	int k = 0;      // ��ʱ���������

	// �ϲ���������������
	while (i <= mid && j <= high) {
		if (L->data[i] <= L->data[j]) {
			temp[k++] = L->data[i++];
		}
		else {
			temp[k++] = L->data[j++];
		}
	}

	// ����������ʣ�ಿ�ָ��Ƶ���ʱ����
	while (i <= mid) {
		temp[k++] = L->data[i++];
	}

	// ����������ʣ�ಿ�ָ��Ƶ���ʱ����
	while (j <= high) {
		temp[k++] = L->data[j++];
	}

	// ����ʱ�����е����ݸ��ƻ�ԭ����
	for (i = low, k = 0; i <= high; i++, k++) {
		L->data[i] = temp[k];
	}

	delete[] temp; // �ͷ���ʱ����
}
void MergeSort(Sqlist* L, int low, int high) {// �鲢����ݹ麯��
	if (low < high) {
		int mid = (low + high) / 2; // �����м�λ��
		MergeSort(L, low, mid);     // ���������еݹ�����
		MergeSort(L, mid + 1, high); // ���������еݹ�����
		Merge(L, low, mid, high);    // �ϲ���������������
	}
}
void MergeSort(Sqlist* L) {// �鲢����ķ�װ����
	cout << "Start MergeSort..." << endl;
	// ��¼��ʼʱ��
	auto start = high_resolution_clock::now();
	if (L->length == 0) {
		cout << "Empty list!" << endl;
		return;
	}
	MergeSort(L, 1, L->length); // ���±�1��ʼ����
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
	cout << "MergeSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

//��������
int getMaxDigits(Sqlist* L) {// ��ȡ���������ֵ��λ��
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
	// ��¼��ʼʱ��
	auto start = high_resolution_clock::now();
	if (L->length == 0) {
		cout << "Empty list!" << endl;
		return;
	}

	int maxDigits = getMaxDigits(L); // ��ȡ���λ��
	int radix = 1; // ��������ʼΪ1����λ��

	// ����10��Ͱ��0-9��
	int* bucket = new int[Sqlist_maxsize];
	int count[10] = { 0 }; // ��¼ÿ��Ͱ��Ԫ�صĸ���

	// �Ӹ�λ�����λ��������
	for (int d = 1; d <= maxDigits; d++) {
		// ��ʼ��������
		for (int i = 0; i < 10; i++) {
			count[i] = 0;
		}

		// ͳ��ÿ��Ͱ��Ԫ�صĸ���
		for (int i = 1; i <= L->length; i++) {
			int digit = (L->data[i] / radix) % 10;
			count[digit]++;
		}

		// ����ÿ��Ͱ�Ľ���λ��
		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}

		// ��Ԫ�ط���Ͱ��
		for (int i = L->length; i >= 1; i--) {
			int digit = (L->data[i] / radix) % 10;
			bucket[count[digit] - 1] = L->data[i];
			count[digit]--;
		}

		// ��Ͱ�е�Ԫ�ظ��ƻ�ԭ����
		for (int i = 0; i < L->length; i++) {
			L->data[i + 1] = bucket[i];
		}

		radix *= 10; // ������һλ
	}

	delete[] bucket; // �ͷ�Ͱ���ڴ�
	auto stop = high_resolution_clock::now();
	display_Sqlist(L);
	auto duration = duration_cast<microseconds>(stop - start);  // ����΢��
	cout << "RadixSort completed!" << endl;
	cout << "Sorting time: " << duration.count() << " microseconds" << endl << endl;
}

//�ⲿ����
void External_Sort(Sqlist* L)
{
	//���ڴ�����ģ���ݵ������㷨����������̫����޷�ȫ�����ص��ڴ�ʱ���ⲿ����ͨ�������ݷֳ�С�飬���ڴ���������ЩС�飬Ȼ�����Ǻϲ���һ����������С��������ⲿ�����㷨������·�鲢����Multiway Merge Sort����
	//�����ļ����ⲿ����
	//������ai��......
}