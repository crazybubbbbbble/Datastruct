#pragma once
#include<iostream>
#include<cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

typedef char Element;

typedef struct Tree {
	int weight;
	Element data;
	struct Tree* left;
	struct Tree* right;
}Tree, * Tnode;

// �Զ���ȽϺ�����������С��
struct compare {
	bool operator()(Tnode a, Tnode b) {
		return a->weight > b->weight;
	}
};

Tnode Init_node(Element data, int weight)
{
	Tnode node = new Tree;
	node->data = data;
	node->weight = weight;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

void Destroy_tree(Tnode& T)
{
	if (T == nullptr)return;
	else {
		Destroy_tree(T->left);
		Destroy_tree(T->right);
		delete T;
		T = nullptr;
	}
}

Tnode HuffmanTree(vector<pair<Element, int>>& Element) {
	if (Element.empty()) {
		return nullptr; // ���û�����룬ֱ�ӷ��ؿ�ָ��
	}

	priority_queue<Tnode, vector<Tnode>, compare> minHeap;
	// ��ʼ����С��
	for (auto& elem : Element) {
		Tnode node = Init_node(elem.first, elem.second);
		minHeap.push(node);
	}

	while (minHeap.size() > 1)
	{
		Tnode left = minHeap.top();
		minHeap.pop();
		Tnode right = minHeap.top();
		minHeap.pop();
		Tnode parent = Init_node('\0', left->weight + right->weight);
		parent->left = left;
		parent->right = right;

		minHeap.push(parent);
	}
	return minHeap.top();
}

// ��ӡ����������
void PrintHuffmanCodes(Tnode root, string code = "") {
	if (!root) return;

	// Ҷ�ӽڵ㣬��ӡ����
	if (!root->left && !root->right) {
		cout << root->data << ": " << code << endl;
	}

	PrintHuffmanCodes(root->left, code + "0");
	PrintHuffmanCodes(root->right, code + "1");
}
