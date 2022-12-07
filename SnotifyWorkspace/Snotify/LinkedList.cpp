#include "LinkedList.h"

LinkedLink::LinkedLink() : 
	head(nullptr), 
	tail(nullptr)
{
}

LinkedLink::~LinkedLink()
{
}

void LinkedLink::AddNode(Library* data)
{
	Node* temp = new Node();
	temp->data = *data;
	temp->next = nullptr;

	if (head == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		tail = tail->next;
	}

}

Node* LinkedLink::GetHead()
{
	return head;
}
