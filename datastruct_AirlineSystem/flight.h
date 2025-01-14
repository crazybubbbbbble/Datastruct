#pragma once
#include<iostream>
#include <string>
#include <iomanip>
#include<vector>
#include"customers.h"
using namespace std;

// ������Ϣ�ṹ
typedef struct Flight {
    string Destination;      // Ŀ�ĵ�
    string Flight_number;    // �����
    string Aircraft_number;  // �ɻ���
    string Date;             // �������
    int Capacity;               // ����
    int Remaining_Tickets;           // ��Ʊ
    CQueue success;        // �Ѷ�Ʊ�ͻ�����
    CQueue waiting;        // �򲹿ͻ�����
} Flight;

//����ڵ�ṹ
typedef struct FlightNode {
    Flight Flight;//������Ϣ
    FlightNode* next;
}*FNode;

//������нṹ
typedef struct FlightQueue {
    FNode head;// ��ͷָ��
    FNode rear;// ��βָ��
    int count;// ���г���
}FQueue;


// ��ʼ���������
void init_fqueue(FQueue& q) {
    q.head = nullptr;
    q.rear = nullptr;
    q.count = 0;
}

// �п�
bool IsEmpty_fqueue(const FQueue& q) {
    return q.head == nullptr;
}

// ��ʾȫ�����������Ϣ
void display_ALLfqueue(const FQueue& q) {
    if (IsEmpty_fqueue(q)) {
        cout << "The flight queue is empty." << endl;
        return;
    }

    FNode temp = q.head;

    // ���������
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

    // ���ÿ��������Ϣ
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

    // ����ܺ�����
    cout << string(120, '=') << endl;
    cout << "Total Flights: " << q.count << endl;
}

// ��ʾ������Ϣ
void display_flight(const Flight& q) {
    // ���������
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

    // ������������Ϣ
    cout << left << setw(16) << q.Destination
        << setw(20) << q.Flight_number
        << setw(26) << q.Aircraft_number
        << setw(16) << q.Date
        << setw(16) << q.Capacity
        << setw(20) << q.Remaining_Tickets
        << endl;

    // ��� success ������Ϣ
    //cout << "\nCustomers with Confirmed Tickets :" << endl;
    //display_customer(q.success, "Success Customers");

    // ��� waiting ������Ϣ
    display_customer(q.waiting, "Waiting Customers");

    // �ָ���
    cout << string(120, '=') << endl;
}

// �������
void Push_fqueue(FQueue& q, const Flight& flight) {
    FNode NewNode = new FlightNode; // �����º���ڵ�
    NewNode->Flight = flight;
    NewNode->next = nullptr;

    if (IsEmpty_fqueue(q)) { // ����Ϊ��ʱ
        q.head = q.rear = NewNode;
    }
    else {                 // ���뵽��β
        q.rear->next = NewNode;
        q.rear = NewNode;
    }
    q.count++; // ���¶��г���
}

// �������
bool Pop_fqueue(FQueue& q, Flight& flight) {
    if (IsEmpty_fqueue(q)) { // �п�
        cout << "The flight queue is empty." << endl;
        return false;
    }
    FNode temp = q.head;
    flight = q.head->Flight; // �����ͷ������Ϣ
    q.head = q.head->next;   // ���¶�ͷָ��
    if (q.head == nullptr) {
        q.rear = nullptr;    // ���б��ʱ���¶�βָ��
    }
    delete temp;             // �ͷ��ڴ�
    q.count--;               // ���¶��г���
    return true;
}

// ���ú������
void set_fqueue(FQueue& q) {
    init_fqueue(q); // ��ʼ���������
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
        flight.Remaining_Tickets = flight.Capacity; // ��ʼ��Ʊ���ڶ���
        //init_cqueue(flight.success);      // ��ʼ���Ѷ�Ʊ����
        //init_cqueue(flight.waiting);      // ��ʼ���򲹶���
        Push_fqueue(q, flight);
    }
    display_ALLfqueue(q);
}