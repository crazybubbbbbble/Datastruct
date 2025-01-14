#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// �ͻ���Ϣ�ṹ
typedef struct Cus {
    string name;  // ����
    int fclass;   // ��λ�ȼ� (1, 2, 3)
    int tickets;  // ��Ʊ��
    string Flight_number;    // �����
    string Date;             // �������
    int isWaiting;      //�Ƿ��ں�
};

// ���нڵ�ṹ
typedef struct CusNode {
    Cus customer;    // �ͻ���Ϣ
    CusNode* next;   
}*CNode;

// �ͻ����нṹ
typedef struct CusQueue {
    CNode head;   // ��ͷָ��
    CNode rear;   // ��βָ��
    int count;       // ���г���
}CQueue;

// ��ʼ������
void init_cqueue(CusQueue& q) {
    q.head = nullptr;
    q.rear = nullptr;
    q.count = 0;
}

// �п�
bool IsEmpty_cqueue(const CusQueue& q) {
    return q.head == nullptr;
}

// ��ʾȫ������
void display_ALLcqueue(const CusQueue& q) {
    if (IsEmpty_cqueue(q)) {
        cout << "The queue is empty." << endl;
        return;
    }

    CusNode* temp = q.head;

    // ���������
    cout << left << setw(17) << "Name"
        << setw(11) << "Tickets"
        << setw(9) << "Class"
        << setw(25) << "Flight Number"
        << setw(10) << "Date"
        << setw(12) << "Is Waiting"
        << endl;

    cout << string(87, '-') << endl; // �ָ���

    // ���ÿ���ͻ�����Ϣ
    while (temp != nullptr) {
        cout << left << setw(20) << temp->customer.name
            << setw(10) << temp->customer.tickets
            << setw(10) << temp->customer.fclass
            << setw(20) << temp->customer.Flight_number
            << setw(15) << temp->customer.Date
            << setw(12) << (temp->customer.isWaiting ? "Yes" : "No")
            << endl;
        temp = temp->next;
    }

    // ����ܿͻ���
    cout << string(87, '-') << endl; // �ָ���
    cout << "Total Customers: " << q.count << endl;
}

// ��ʾ�ͻ�������Ϣ
void display_customer(const CQueue& q, const string& queueName) {
    cout << "  " << queueName << " (" << q.count << " customers):" << endl;

    // ����Ϊ�յ����
    if (IsEmpty_cqueue(q)) {
        cout << "    [No customers in this queue]" << endl;
        return;
    }

    // ����ͻ����б�����
    cout << "    " << left << setw(20) << "Name"
        << setw(8) << "Class"
        << setw(10) << "Tickets"
        << setw(24) << "Flight Number"
        << setw(16) << "Date"
        << endl;
    cout << "    " << string(76, '-') << endl;

    // �����ͻ����в����ÿλ�ͻ�����Ϣ
    CNode temp = q.head;
    while (temp != nullptr) {
        cout << "    " << left << setw(20) << temp->customer.name
            << setw(10) << temp->customer.fclass
            << setw(10) << temp->customer.tickets
            << setw(20) << temp->customer.Flight_number
            << setw(16) << temp->customer.Date
            << endl;
        temp = temp->next;
    }
}

//���
void Push_cqueue(CusQueue& q, const Cus& c) {
    // ������нṹ��
    if (q.head == nullptr && q.rear != nullptr) {
        cout << "Error: Queue corrupted. Resetting queue." << endl;

        // �ͷ����нڵ�
        while (q.rear != nullptr) {
            CusNode* temp = q.rear;
            q.rear = q.rear->next;
            delete temp;
        }

        // ���ö���
        q.head = q.rear = nullptr;
        q.count = 0;
    }

    // �����½ڵ�
    CNode temp = new CusNode;
    temp->customer = c;
    temp->next = nullptr;

    // �������Ϊ��
    if (IsEmpty_cqueue(q)) {
        q.head = q.rear = temp; // �½ڵ����ͷ����β
    }
    else {
        q.rear->next = temp;   // ���½ڵ����ӵ���β
        q.rear = temp;         // ���¶�βָ��
    }

    q.count++; // ���¶��г���
}

// ����
bool Pop_cqueue(CusQueue& q, Cus& customer) {
    if (IsEmpty_cqueue(q)) { // �п�
        cout << "The queue is empty." << endl;
        return false;
    }
    CusNode* temp = q.head;
    customer = q.head->customer; // �����ͷ�ͻ���Ϣ
    q.head = q.head->next;       // ���¶�ͷָ��
    if (q.head == nullptr) {
        q.rear = nullptr;        // �������Ϊ�գ����¶�β
    }
    delete temp;                 // �ͷ��ڴ�
    q.count--;                   // ���¶��г���
    return true;
}

// ����һ���ͻ�����
void set_queue(CusQueue& q) {
    init_cqueue(q); // ��ʼ������
    Cus customer;
    cout << "Please input customer information. Enter 'exit' as name to quit." << endl;
    while (true) {
        cout << "Name: ";
        cin >> customer.name;
        if (customer.name == "exit") break;
        cout << "Tickets: ";
        cin >> customer.tickets;
        cout << "Class (1, 2, 3): ";
        cin >> customer.fclass;
        Push_cqueue(q, customer);
    }
    display_ALLcqueue(q);
}
