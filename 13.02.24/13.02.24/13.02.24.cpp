#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class SinglyLinkedList
{
public:
	struct Node
	{
		int data = 0;
		Node* next = nullptr;
	};

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	int count = 0;

public:

	void AddToHead(int data)
	{
		auto newElem = new Node;
		newElem->data = data;
		newElem->next = head;

		if (head == nullptr)
		{
			tail = newElem;
		}
		head = newElem;
		count++;
	}

	void AddToTail(int data)
	{
		auto newElem = new Node;
		newElem->data = data;
		if (tail == nullptr)
		{
			head = newElem;
		}
		else
		{
			tail->next = newElem;
		}
		tail = newElem;
		count++;
	}

	void InsertInto(int data, int position)
	{
		if (position >= count)
		{
			AddToTail(data);
			return;
		}
		else if (position <= 0)
		{
			AddToHead(data);
			return;
		}

		Node* newElem = new Node;
		newElem->data = data;
		int i = 1;
		Node* beforeNew = head;
		while (i++ != position)
		{
			beforeNew = beforeNew->next;
		}
		newElem->next = beforeNew->next;
		beforeNew->next = newElem;

		count++;
	}

	void DeleteFromHead()
	{
		if (count == 0)
		{
			return;
		}
		Node* temp = head;
		head = head->next;
		delete temp;
		count--;
		if (head == nullptr)
		{
			tail = nullptr;
		}
	}

	void DeleteFromTail()
	{
		if (count == 0) {
			return;
		}
		DeleteByIndex(count - 1);
	}

	void DeleteByIndex(int position)
	{
		if (position <= 0)
		{
			DeleteFromHead();
			return;
		}

		if (position >= count)
		{
			position = count - 1;
		}

		int i = 1;
		Node* beforeDel = head;
		while (i++ != position)
		{
			beforeDel = beforeDel->next;
		}
		Node* sacrifice = beforeDel->next;
		beforeDel->next = sacrifice->next;
		delete sacrifice;
		count--;
		if (beforeDel->next == nullptr)
		{
			tail = beforeDel;
		}
	}

	void Clear()
	{
		while (head != nullptr)
		{
			DeleteFromHead();
		}
	}

	void Print() const
	{
		if (count == 0)
		{
			cout << "Empty list!\n";
			return;
		}
		Node* current = head;
		while (current != nullptr)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << "\n";
	}

	int GetCount() const
	{
		return count;
	}

	int IndexOf(int data) const
	{
		if (count == 0)
		{
			return -1;
		}
		Node* current = head;
		int i = 0;
		while (i < count)
		{
			if (data == current->data)
			{
				return i;
			}
			i++;
			current = current->next;
		}
		return -1;
	}

	bool IsEmpty()
	{
		if (head == nullptr)
		{
			return true;
		}
		return false;
	}

	void SortAsc() {
		if (count == 0 || count == 1) return;
		vector<int> ar;
		Node* current = head;
		for (int i = 0; i < count; i++) {
			ar.push_back(current->data);
			current = current->next;
		}
		sort(ar.begin(), ar.end());

		current = head;
		for (int i = 0; i < count; i++) {
			current->data = ar[i];
			current = current->next;
		}
	}

	int LastIndexOf(int data)
	{
		int* ar = ToArray();
		Node* current = head;
		for (int i = 0; i < count; i++)
		{
			ar[i] = current->data;
			current = current->next;
		}

		for (int i = 0; i < count; i++)
		{
			cout << ar[i] << "\n";
			if (ar[i] == data)
			{
				return i;
			}
		}
		return -1;
	}

	void Shuffle()
	{
		int* ar = ToArray();
		Node* current = head;
		for (int i = 0; i < count; i++)
		{
			int x = rand() % count;
			int y = rand() % count;
			int temp;
			temp = ar[x];
			ar[x] = ar[y];
			ar[y] = temp;
		}

		current = head;
		for (int i = 0; i < count; i++) {
			current->data = ar[i];
			current = current->next;
		}
	}

	SinglyLinkedList* Clone(const SinglyLinkedList& original)
	{
		Node* current = original.head;
		while (current != nullptr)
		{
			this->AddToTail(current->data);
			current = current->next;
		}
		return this;
	}

	void SetAt(int index, int data)
	{
		Node* current = head;
		for (int i = 0; i < count; i++)
		{
			if (i == index)
			{
				current->data = data;
			}
			current = current->next;
		}
	}

	int* ToArray()
	{
		int* ar = new int[count];
		Node* current = head;
		for (int i = 0; i < count; i++)
		{
			ar[i] = current->data;
			current = current->next;
		}

		return ar;
	}

	void MergeWith(const SinglyLinkedList& sll2)
	{
		Node* newHead = sll2.head;
		tail->next = newHead;
		tail = nullptr;
		count += sll2.count;
	}

	~SinglyLinkedList() {
	}

	SinglyLinkedList() {}

	SinglyLinkedList(const SinglyLinkedList& original)
	{
		Node* current = original.head;
		while (current != nullptr)
		{
			this->AddToTail(current->data);
			current = current->next;
		}
	}

	SinglyLinkedList& operator = (const SinglyLinkedList& original)
	{
		if (this == &original) return *this;

		this->Clear();

		Node* current = original.head;
		while (current != nullptr)
		{
			this->AddToTail(current->data);
			current = current->next;
		}
		return *this;
	}

	bool operator == (SinglyLinkedList& sll2)
	{
		if (this->count != sll2.count)
		{
			return false;
		}

		Node* current1 = this->head;
		Node* current2 = sll2.head;

		for (int i = 0; i < count; i++)
		{
			if (current1->data != current2->data)
			{
				return false;
			}
			current1 = current1->next;
			current2 = current2->next;
		}
		return true;
	}

	bool operator != (SinglyLinkedList& sll2)
	{
		return !(*this == sll2);
	}
};

ostream& operator << (ostream& o, SinglyLinkedList& sll)
{
	sll.Print();
	return cout;
}

int main()
{
	srand(time(NULL));
	SinglyLinkedList sll;
	SinglyLinkedList sll2;
	int* ar;
	sll.AddToTail(10);
	sll.AddToTail(20);
	sll.AddToTail(30);
	sll.AddToTail(40);
	sll.AddToTail(50);
	sll.AddToTail(40);
	cout << sll;
	sll.Print();

	sll2.AddToTail(10);
	sll == sll2;
	sll != sll2;

	sll2.AddToTail(20);
	sll2.AddToTail(30);
	sll2.AddToTail(40);
	sll2.AddToTail(50);
	sll2.AddToTail(40);

	sll2.Clone(sll);
	sll.MergeWith(sll2);
	sll.Print();
	sll.SetAt(2, 5);
	ar = sll.ToArray();

	cout << sll.LastIndexOf(40) << "\n";
	sll.Shuffle();
	sll.Print();
}