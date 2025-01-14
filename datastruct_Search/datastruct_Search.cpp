#include"Search_Sqlist.h"
#include"Search_Binary_Tree.h"
int main()
{
	//Sqlist L;
	//set_Sqlist(&L,10000000);
	//Sequential_Search(&L);
	//Half_Search(&L);
	//Half_Search_Recursive_Wrapper(&L);


	Tnode T=nullptr;
	create(T);
	cout << "Mid display: ";
	Mid_display(T);
	Insert(T, 35);
	cout << "Mid display: ";
	Mid_display(T);
	Delete(T, 12);
	cout << "Mid display: ";
	Mid_display(T);
}