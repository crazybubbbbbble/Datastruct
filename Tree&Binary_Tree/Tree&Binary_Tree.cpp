//#include"Binary_Tree.h"
//#include "Breadth_BFS.h"
//#include "Depth_DFS.h"
#include"Huffman_Tree.h"
//以上头文件有重复声明的部分，不能同时引用

int main() {
    vector<pair<Element, int>> elements = {
        {'A', 5}, {'B', 9}, {'C', 12}, {'D', 13}, {'E', 16}, {'F', 45}
    };

    // 构造哈夫曼树
    Tnode root = HuffmanTree(elements);

    // 打印哈夫曼编码
    cout << "Huffman Codes:" << endl;
    PrintHuffmanCodes(root);

    // 销毁哈夫曼树
    Destroy_tree(root);
    return 0;
}
