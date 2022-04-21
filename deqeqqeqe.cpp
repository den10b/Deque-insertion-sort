#include <locale.h>
#include <ctime>
#include "windows.h"
#include <iostream>
using namespace std;

struct TNode {
public:
	int data;
	TNode* next;
	TNode* prev;

	TNode(int newData, TNode* nextNode, TNode* prevNode, int tst) { //2
		data = newData;//1
		if (tst == 0) {//1
			next = nextNode; //1
			prev = NULL; //1
		}
		if (tst == 1) { //1
			next = NULL;//1
			prev = prevNode;//1
		}
	}                           //сумма 6
	void addnxt(TNode* nextNode) //2
	{
		next = nextNode;
	}
	void addprev(TNode* prevNode) //2
	{
		prev = prevNode;
	}
	void clrnxt() //2
	{
		next = NULL;
	}
	void clrprev() //2
	{
		prev = NULL;
	}
};

class stackInList {
public:
	int sizeOfStack;
	TNode* currentTop;
	TNode* currenttail;


	stackInList() { //3
		sizeOfStack = 0;
		currentTop = NULL;
		currenttail = NULL;
	}

	~stackInList() {   //sizeofstack раз 2 действия
		while (sizeOfStack != 0)
			pop();
	}

	void push(int element) { //~8
		TNode* node = new TNode(element, currentTop, currenttail, 0); //6
		if (currenttail == NULL)  currenttail = node;
		if ((currentTop != NULL)) currentTop->addprev(node);
		sizeOfStack++; //1
		currentTop = node;//1
	}
	void backpush(int element) { //~8
		TNode* node = new TNode(element, currentTop, currenttail, 1); //6
		if (currentTop == NULL) currentTop = node;
		if ((currenttail != NULL)) currenttail->addnxt(node);
		sizeOfStack++;
		currenttail = node;


	}

	void pop() {//~4
		sizeOfStack--;
		TNode* node = currentTop;
		currentTop = currentTop->next;

		delete node;
		if (currentTop != NULL) currentTop->clrprev();
	}
	void plug() { //~4
		sizeOfStack--;
		TNode* node = currenttail;
		currenttail = currenttail->prev;
		delete node;
		if (currenttail != NULL)currenttail->clrnxt();
	}


	int top() { //1
		return currentTop->data;
	}

	int tail() { //1
		return currenttail->data;
	}

	int size() { //1
		return sizeOfStack;
	}
	int spin(int val) {
		int res;
		for (int i = 1; i < val; i++) {  // Sum 1 to (n-1)
			backpush(top());       //9
			pop();                //4
		}

		res = top(); //2
		for (int i = 1; i < val; i++) { //Sum 1 to (n-1)
			push(tail());  //9
			plug();        //4

		}

		return res;
	}
	void insert(int val, int date) {
		if (val != 0) {        //1
			for (int i = 0; i < val; i++) {   //Sum 1 to (n-1)
				backpush(currentTop->data);       //9
				pop();                             //4
			}
			push(date);
			for (int i = 0; i < val; i++) {     //Sum 1 to (n-1)
				push(currenttail->data);           //9
				plug();                             //4
			}
		}
		else push(date);   //8

	}

	void InSort() {
		for (int i = 1; i < sizeOfStack; i++) {
			int srtd = i;
			int data = tail();
			plug();
			int sizeref = srtd;
			int midrst = (sizeref / 2) + (sizeref % 2);

			while (sizeref > 2) {
				if (spin(midrst) >= data) {
					sizeref = sizeref / 2 - 1 + (sizeref % 2);
					midrst = midrst - (sizeref / 2) - 1;
				}
				else {
					sizeref = sizeref / 2;
					midrst = midrst + (sizeref / 2) + (sizeref % 2);

				}
			}
			if (sizeref == 1) {
				if (spin(midrst) >= data) {
					insert(midrst - 1, data);
				}
				else {
					insert(midrst, data);
				}
			}
			else {
				if (spin(midrst) >= data) {
					insert(midrst - 1, data);
				}
				else {
					if (spin(midrst + 1) >= data) {
						insert(midrst, data);
					}
					else {
						insert(midrst + 1, data);
					}
				}
			}
		}




	}

};
int main()
{
	stackInList valer;
	int N = 0;
	for (int h = 0; h < 10; h++) {
		cout << endl << h+1 << " round" << endl << endl;
		N = N + 300; 
		cout << "Unsorted 300:" << endl;
		for (int i = 1; i <= N; i++) {
			int item = (rand() % 999);
			cout <<  item << endl;
			valer.push(item);

		}
		int size = valer.sizeOfStack;
		valer.InSort();
		cout << "Sorted 300:" << endl;
		for (int i = 1; i < N; i++) {
			cout <<  valer.top() << endl;
			valer.pop();
		}
	}


	int size = valer.sizeOfStack;
	for (int i = 1; i <= size; i++) {
		cout << valer.spin(i) << endl;
	}

	for (int i = 1; i <= size; i++) {
		if (valer.sizeOfStack != 0) {
			cout << (valer.top()) << endl;
			valer.pop();
		}
	}


	return 0;
}
