#pragma once

#include "Library.h"

struct Node {
	Library data;
	Node* next;
};

class LinkedLink
{
public:
	LinkedLink();
	~LinkedLink();
	void AddNode(Library* data);
	Node* GetHead();

private:
	Node* head;
	Node* tail;
};
