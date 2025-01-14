#pragma once
#include <iostream>
using namespace std;

#define linklist_maxsize 100

typedef struct LNode {
    int data;
    struct LNode* next;
} LNode, * Linklist;

Linklist Init_list(Linklist& L) // ��ʼ��
{
    L = new LNode;
    L->next = NULL;
    return L;
}

void display_list(Linklist L) // ����
{
    int count = 0;
    Linklist p = L->next;
    cout << "Linklist : ";
    while (p)
    {
        count++;
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl << "Count : " << count << endl << endl;
}

Linklist HeadSet_list(Linklist& L) // ͷ�巨
{
    Init_list(L);
    cout << "Please input the data. Enter 9999 to quit." << endl;
    int input;
    cin >> input;
    while (input != 9999) // �жϽ���
    {
        Linklist A = new LNode;
        A->data = input;
        A->next = L->next;
        L->next = A;
        cin >> input;
    }
    display_list(L);
    return L;
}

Linklist TailSet_list(Linklist& L) // β�巨
{
    Init_list(L);
    LNode* A, * B = L;
    cout << "Please input the data. Enter 9999 to quit." << endl;
    int input;
    cin >> input;
    while (input != 9999) // �жϽ���
    {
        A = new LNode;
        A->data = input;
        B->next = A;
        B = A;
        cin >> input;
    }
    B->next = NULL; // βָ���ÿ�
    display_list(L);
    return L;
}

int CountList(Linklist L) // ���㳤��
{
    int count = 0;
    Linklist p = L->next;
    while (p)
    {
        count++;
        p = p->next;
    }
    //cout << "The length is : " << count << endl;
    return count;
}

Linklist SearchData_list(Linklist L, int x) // ��ֵ����
{
    Linklist p = L->next;
    while (p && p->data != x)
    {
        p = p->next;
    }
    return p; // �ҵ�ʱ����ָ��ýڵ��ָ�룬δ�ҵ��򷵻� NULL
}

Linklist IDData_list(Linklist L, int x) // ��λ����
{
    int i = 1;
    Linklist P = L->next;
    while (P && i < x)
    {
        P = P->next;
        i++;
    }
    if (i == x) return P;
    else return NULL;
}

Linklist Insert_list(Linklist& L, int i, int data) // ����
{
    if (i < 1 || i > CountList(L) + 1) // ���λ���Ƿ���Ч
    {
        cout << "Error! Position out of range." << endl;
        return NULL;
    }
    Linklist P = IDData_list(L, i - 1);
    if (!P) return NULL;
    Linklist E = new LNode;
    E->data = data;
    E->next = P->next;
    P->next = E;
    return L;
}

Linklist Delete_list(Linklist& L, int i) // ɾ��Ԫ��
{
    if (i < 1 || i > CountList(L)) // ���λ���Ƿ���Ч
    {
        cout << "Error! Position out of range." << endl;
        return NULL;
    }
    Linklist P = IDData_list(L, i - 1);
    if (!P || !P->next) return NULL;
    Linklist Q = P->next;
    P->next = Q->next;
    delete Q;
    return L;
}

Linklist ChangeData_list(Linklist& L, int i, int data) // ��������
{
    Linklist P = IDData_list(L, i);
    if (!P)
    {
        cout << "Error! Position out of range." << endl;
        return NULL;
    }
    P->data = data;
    return L;
}

void Destroy_list(Linklist& L) // ���������ͷ��ڴ�
{
    Linklist p = L;
    while (p)
    {
        Linklist temp = p->next;
        delete p;
        p = temp;
    }
    L = NULL; // ��ͷָ���ÿ�
}

void upsidedown_list(Linklist& L)//��ת
{
    Linklist p1 = L->next;
    Linklist prev = NULL;
    while (p1) {
        Linklist nextNode = p1->next;
        p1->next = prev;
        prev = p1;
        p1 = nextNode;
    }
    L->next = prev; // ���� L1 ��ͷ�ڵ�
    display_list(L);
}