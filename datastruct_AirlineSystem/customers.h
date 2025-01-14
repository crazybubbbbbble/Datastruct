#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// 客户信息结构
typedef struct Cus {
    string name;  // 姓名
    int fclass;   // 舱位等级 (1, 2, 3)
    int tickets;  // 订票量
    string Flight_number;    // 航班号
    string Date;             // 起飞日期
    int isWaiting;      //是否处于候补
};

// 队列节点结构
typedef struct CusNode {
    Cus customer;    // 客户信息
    CusNode* next;   
}*CNode;

// 客户队列结构
typedef struct CusQueue {
    CNode head;   // 队头指针
    CNode rear;   // 队尾指针
    int count;       // 队列长度
}CQueue;

// 初始化队列
void init_cqueue(CusQueue& q) {
    q.head = nullptr;
    q.rear = nullptr;
    q.count = 0;
}

// 判空
bool IsEmpty_cqueue(const CusQueue& q) {
    return q.head == nullptr;
}

// 显示全部队列
void display_ALLcqueue(const CusQueue& q) {
    if (IsEmpty_cqueue(q)) {
        cout << "The queue is empty." << endl;
        return;
    }

    CusNode* temp = q.head;

    // 输出标题行
    cout << left << setw(17) << "Name"
        << setw(11) << "Tickets"
        << setw(9) << "Class"
        << setw(25) << "Flight Number"
        << setw(10) << "Date"
        << setw(12) << "Is Waiting"
        << endl;

    cout << string(87, '-') << endl; // 分隔线

    // 输出每个客户的信息
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

    // 输出总客户数
    cout << string(87, '-') << endl; // 分隔线
    cout << "Total Customers: " << q.count << endl;
}

// 显示客户队列信息
void display_customer(const CQueue& q, const string& queueName) {
    cout << "  " << queueName << " (" << q.count << " customers):" << endl;

    // 队列为空的情况
    if (IsEmpty_cqueue(q)) {
        cout << "    [No customers in this queue]" << endl;
        return;
    }

    // 输出客户队列标题行
    cout << "    " << left << setw(20) << "Name"
        << setw(8) << "Class"
        << setw(10) << "Tickets"
        << setw(24) << "Flight Number"
        << setw(16) << "Date"
        << endl;
    cout << "    " << string(76, '-') << endl;

    // 遍历客户队列并输出每位客户的信息
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

//入队
void Push_cqueue(CusQueue& q, const Cus& c) {
    // 如果队列结构损坏
    if (q.head == nullptr && q.rear != nullptr) {
        cout << "Error: Queue corrupted. Resetting queue." << endl;

        // 释放所有节点
        while (q.rear != nullptr) {
            CusNode* temp = q.rear;
            q.rear = q.rear->next;
            delete temp;
        }

        // 重置队列
        q.head = q.rear = nullptr;
        q.count = 0;
    }

    // 创建新节点
    CNode temp = new CusNode;
    temp->customer = c;
    temp->next = nullptr;

    // 如果队列为空
    if (IsEmpty_cqueue(q)) {
        q.head = q.rear = temp; // 新节点既是头又是尾
    }
    else {
        q.rear->next = temp;   // 将新节点连接到队尾
        q.rear = temp;         // 更新队尾指针
    }

    q.count++; // 更新队列长度
}

// 出队
bool Pop_cqueue(CusQueue& q, Cus& customer) {
    if (IsEmpty_cqueue(q)) { // 判空
        cout << "The queue is empty." << endl;
        return false;
    }
    CusNode* temp = q.head;
    customer = q.head->customer; // 保存队头客户信息
    q.head = q.head->next;       // 更新队头指针
    if (q.head == nullptr) {
        q.rear = nullptr;        // 如果队列为空，更新队尾
    }
    delete temp;                 // 释放内存
    q.count--;                   // 更新队列长度
    return true;
}

// 设置一个客户队列
void set_queue(CusQueue& q) {
    init_cqueue(q); // 初始化队列
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
