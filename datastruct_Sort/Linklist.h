#pragma once
#include <iostream>
using namespace std;

#define linklist_maxsize 100

typedef struct LNode {
    int data;
    struct LNode* next;
} LNode, * Linklist;

Linklist Init_list(Linklist& L) // 初始化
{
    L = new LNode;
    L->next = NULL;
    return L;
}

void display_list(Linklist L) // 遍历
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

Linklist HeadSet_list(Linklist& L) // 头插法
{
    Init_list(L);
    cout << "Please input the data. Enter 9999 to quit." << endl;
    int input;
    cin >> input;
    while (input != 9999) // 判断结束
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

Linklist TailSet_list(Linklist& L) // 尾插法
{
    Init_list(L);
    LNode* A, * B = L;
    cout << "Please input the data. Enter 9999 to quit." << endl;
    int input;
    cin >> input;
    while (input != 9999) // 判断结束
    {
        A = new LNode;
        A->data = input;
        B->next = A;
        B = A;
        cin >> input;
    }
    B->next = NULL; // 尾指针置空
    display_list(L);
    return L;
}

int CountList(Linklist L) // 计算长度
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

Linklist SearchData_list(Linklist L, int x) // 按值查找
{
    Linklist p = L->next;
    while (p && p->data != x)
    {
        p = p->next;
    }
    return p; // 找到时返回指向该节点的指针，未找到则返回 NULL
}

Linklist IDData_list(Linklist L, int x) // 按位查找
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

Linklist Insert_list(Linklist& L, int i, int data) // 插入
{
    if (i < 1 || i > CountList(L) + 1) // 检查位置是否有效
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

Linklist Delete_list(Linklist& L, int i) // 删除元素
{
    if (i < 1 || i > CountList(L)) // 检查位置是否有效
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

Linklist ChangeData_list(Linklist& L, int i, int data) // 更改数据
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

void Destroy_list(Linklist& L) // 销毁链表，释放内存
{
    Linklist p = L;
    while (p)
    {
        Linklist temp = p->next;
        delete p;
        p = temp;
    }
    L = NULL; // 将头指针置空
}

void upsidedown_list(Linklist& L)//反转
{
    Linklist p1 = L->next;
    Linklist prev = NULL;
    while (p1) {
        Linklist nextNode = p1->next;
        p1->next = prev;
        prev = p1;
        p1 = nextNode;
    }
    L->next = prev; // 更新 L1 的头节点
    display_list(L);
}