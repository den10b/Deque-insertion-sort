#include <locale.h>
#include <ctime>
#include "windows.h"
#include <iostream>
using namespace std;
long int N_op;

struct TNode {
public:
	int data;
	
	TNode* next;
	TNode* prev;

	TNode(int newData, TNode* nextNode, TNode* prevNode, int tst) { //2
		data = newData; N_op++;
		if (tst == 0) {N_op++;
			next = nextNode; N_op++;
			prev = NULL; N_op++;
		}
		if (tst == 1) {
			N_op++;
			next = NULL; N_op++;
			prev = prevNode; N_op++;
		}
	}                           //сумма 6
	void addnxt(TNode* nextNode) //2
	{
		next = nextNode; N_op++;
	}
	void addprev(TNode* prevNode) 
	{
		prev = prevNode; N_op++;
	}
	void clrnxt() //2
	{
		next = NULL; N_op++;
	}
	void clrprev() //2
	{
		prev = NULL; N_op++;
	}
};

class stackInList {
public:
	int sizeOfStack;
	TNode* currentTop;
	TNode* currenttail;


	stackInList() { //3
		sizeOfStack = 0; N_op++;
		currentTop = NULL; N_op++;
		currenttail = NULL; N_op++;
	}

	~stackInList() {   //sizeofstack раз 2 действия
		while (sizeOfStack != 0)
			pop(); N_op++; N_op++;
	}

	void push(int element) { //~8
		TNode* node = new TNode(element, currentTop, currenttail, 0); N_op++; N_op++;
		if (currenttail == NULL)  currenttail = node; N_op++; N_op++;
		if ((currentTop != NULL)) currentTop->addprev(node); N_op++; N_op++;
		sizeOfStack++; N_op++;
		currentTop = node; N_op++;
	}
	void backpush(int element) { //~8
		TNode* node = new TNode(element, currentTop, currenttail, 1); N_op++; N_op++;
		if (currentTop == NULL) currentTop = node; N_op++; N_op++;
		if ((currenttail != NULL)) currenttail->addnxt(node); N_op++; N_op++;
		sizeOfStack++; N_op++;
		currenttail = node; N_op++;


	}

	void pop() {//~4
		sizeOfStack--; N_op++;
		TNode* node = currentTop; N_op++;
		currentTop = currentTop->next; N_op++;

		delete node; N_op++;
		if (currentTop != NULL) currentTop->clrprev(); N_op++; N_op++;
	}
	void plug() { //~4
		sizeOfStack--; N_op++;
		TNode* node = currenttail; N_op++;
		currenttail = currenttail->prev; N_op++;
		delete node; N_op++;
		if (currenttail != NULL)currenttail->clrnxt(); N_op++; N_op++;
	}


	int top() { //1
		return currentTop->data; N_op++;
	}

	int tail() { //1
		return currenttail->data; N_op++;
	}

	int size() { //1
		return sizeOfStack; N_op++;
	}
	int spin(int val) {
		int res; N_op++; N_op++;
		for (int i = 1; i < val; i++) {
			N_op++; N_op++;
			backpush(top());       //9
			pop();                //4
		}

		res = top(); N_op++; N_op++; N_op++;
		for (int i = 1; i < val; i++) {
			N_op++; N_op++;
			push(tail());  //9
			plug();        //4

		}

		return res;
	}
	void insert(int val, int date) {
		if (val != 0) {
			N_op++; N_op++; N_op++;
			for (int i = 0; i < val; i++) {
				N_op++; N_op++;
				backpush(currentTop->data);       //9
				pop();                             //4
			}
			push(date); N_op++; N_op++; N_op++;
			for (int i = 0; i < val; i++) {
				N_op++; N_op++;
				push(currenttail->data);           //9
				plug();                             //4
			}
		}
		else push(date);  N_op++;

	}

	void InSort(){
		N_op++; N_op++;
		for (int i = 1; i < sizeOfStack; i++) {
			N_op++; N_op++;
			int srtd = i; N_op++;
			int data = tail(); N_op++;
			plug();
			int sizeref = srtd; N_op++;
			int midrst = (sizeref / 2) + (sizeref % 2); N_op++; N_op++; N_op++; N_op++;

			while (sizeref > 2) {
				N_op++; N_op++;
				if (spin(midrst) >= data) {
					sizeref = sizeref / 2 - 1 + (sizeref % 2); N_op++; N_op++; N_op++; N_op++; N_op++;
					midrst = midrst - (sizeref / 2) - 1; N_op++; N_op++; N_op++; N_op++;
				}
				else {
					sizeref = sizeref / 2; N_op++; N_op++;
					midrst = midrst + (sizeref / 2) + (sizeref % 2); N_op++; N_op++; N_op++; N_op++; N_op++;

				}
			}
			if (sizeref == 1) {
				N_op++; N_op++;
				if (spin(midrst) >= data) {
					insert(midrst - 1, data); N_op++;
				}
				else {
					insert(midrst, data); 
				}
			}
			else {
				N_op++;
				if (spin(midrst) >= data) {
					N_op++;
					insert(midrst - 1, data); N_op++;
				}
				else {
					N_op++;
					if (spin(midrst + 1) >= data) {
						N_op++;
						insert(midrst, data);
					}
					else {
						insert(midrst + 1, data); N_op++;
					}
				}
			}
		}




	}

};
int main()
{
	N_op = 0;
	stackInList valer;
	int N = 0;
	for (int h = 0; h < 10; h++) {
		N =N +300;
		for (int i = 1; i <= N; i++) {
			valer.push((rand() % 999));
		}
		int size = valer.sizeOfStack;
		long int nownop = N_op;
		int t_s = GetTickCount();
		valer.InSort();
		int t_f = GetTickCount();
		long int lstnop = N_op;
		cout << endl<<"Time is " << t_f - t_s <<"  ms"<< endl;
		cout << endl <<"Nop time -   "<< lstnop - nownop << endl;
		for (int i = 1; i < N; i++) {
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
