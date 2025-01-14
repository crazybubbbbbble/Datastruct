#pragma once
#include<iostream>
#include <string>
#include <iomanip>
#include<vector>
#include"customers.h"
using namespace std;

// 航班信息结构
typedef struct Flight {
    string Destination;      // 目的地
    string Flight_number;    // 航班号
    string Aircraft_number;  // 飞机号
    string Date;             // 起飞日期
    int Capacity;               // 定额
    int Remaining_Tickets;           // 余票
    CQueue success;        // 已订票客户队列
    CQueue waiting;        // 候补客户队列
} Flight;

//航班节点结构
typedef struct FlightNode {
    Flight Flight;//航班信息
    FlightNode* next;
}*FNode;

//航班队列结构
typedef struct FlightQueue {
    FNode head;// 队头指针
    FNode rear;// 队尾指针
    int count;// 队列长度
}FQueue;


// 初始化航班队列
void init_fqueue(FQueue& q) {
    q.head = nullptr;
    q.rear = nullptr;
    q.count = 0;
}

// 判空
bool IsEmpty_fqueue(const FQueue& q) {
    return q.head == nullptr;
}

// 显示全部航班队列信息
void display_ALLfqueue(const FQueue& q) {
    if (IsEmpty_fqueue(q)) {
        cout << "The flight queue is empty." << endl;
        return;
    }

    FNode temp = q.head;

    // 输出标题行
    cout << string(120, '=') << endl;
    cout << "Flight Information" << endl;
    cout << string(120, '=') << endl;

    cout << left << setw(16) << "Destination"
        << setw(20) << "Flight Number"
        << setw(26) << "Aircraft Number"
        << setw(16) << "Date"
        << setw(16) << "Capacity"
        << setw(20) << "Remaining Tickets"
        << endl;
    cout << string(120, '=') << endl;

    // 输出每条航班信息
    while (temp != nullptr) {
        cout << left << setw(16) << temp->Flight.Destination
            << setw(20) << temp->Flight.Flight_number
            << setw(26) << temp->Flight.Aircraft_number
            << setw(16) << temp->Flight.Date
            << setw(16) << temp->Flight.Capacity
            << setw(20) << temp->Flight.Remaining_Tickets
            // << setw(15) << temp->Flight.success.count
            // << setw(15) << temp->Flight.waiting.count
            << endl;
        temp = temp->next;
    }

    // 输出总航班数
    cout << string(120, '=') << endl;
    cout << "Total Flights: " << q.count << endl;
}

// 显示航班信息
void display_flight(const Flight& q) {
    // 输出标题行
    cout << string(120, '=') << endl;
    cout << "Flight Information" << endl;
    cout << string(120, '=') << endl;

    cout << left << setw(16) << "Destination"
        << setw(20) << "Flight Number"
        << setw(26) << "Aircraft Number"
        << setw(16) << "Date"
        << setw(16) << "Capacity"
        << setw(20) << "Remaining Tickets"
        << endl;
    cout << string(120, '-') << endl;

    // 输出航班基本信息
    cout << left << setw(16) << q.Destination
        << setw(20) << q.Flight_number
        << setw(26) << q.Aircraft_number
        << setw(16) << q.Date
        << setw(16) << q.Capacity
        << setw(20) << q.Remaining_Tickets
        << endl;

    // 输出 success 队列信息
    //cout << "\nCustomers with Confirmed Tickets :" << endl;
    //display_customer(q.success, "Success Customers");

    // 输出 waiting 队列信息
    display_customer(q.waiting, "Waiting Customers");

    // 分隔线
    cout << string(120, '=') << endl;
}

// 航班入队
void Push_fqueue(FQueue& q, const Flight& flight) {
    FNode NewNode = new FlightNode; // 创建新航班节点
    NewNode->Flight = flight;
    NewNode->next = nullptr;

    if (IsEmpty_fqueue(q)) { // 队列为空时
        q.head = q.rear = NewNode;
    }
    else {                 // 插入到队尾
        q.rear->next = NewNode;
        q.rear = NewNode;
    }
    q.count++; // 更新队列长度
}

// 航班出队
bool Pop_fqueue(FQueue& q, Flight& flight) {
    if (IsEmpty_fqueue(q)) { // 判空
        cout << "The flight queue is empty." << endl;
        return false;
    }
    FNode temp = q.head;
    flight = q.head->Flight; // 保存队头航班信息
    q.head = q.head->next;   // 更新队头指针
    if (q.head == nullptr) {
        q.rear = nullptr;    // 队列变空时更新队尾指针
    }
    delete temp;             // 释放内存
    q.count--;               // 更新队列长度
    return true;
}

// 设置航班队列
void set_fqueue(FQueue& q) {
    init_fqueue(q); // 初始化航班队列
    Flight flight;
    cout << "Please input flight information. Enter 'exit' as destination to quit." << endl;
    while (true) {
        cout << "Destination: ";
        cin >> flight.Destination;
        if (flight.Destination == "exit") break;
        cout << "Flight Number: ";
        cin >> flight.Flight_number;
        cout << "Aircraft Number: ";
        cin >> flight.Aircraft_number;
        cout << "Date: ";
        cin >> flight.Date;
        cout << "Capacity: ";
        cin >> flight.Capacity;
        flight.Remaining_Tickets = flight.Capacity; // 初始余票等于定额
        //init_cqueue(flight.success);      // 初始化已订票队列
        //init_cqueue(flight.waiting);      // 初始化候补队列
        Push_fqueue(q, flight);
    }
    display_ALLfqueue(q);
}