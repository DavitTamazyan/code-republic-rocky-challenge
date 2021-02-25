 
struct LinkedList
{
	int value;
	LinkedList* next;
	LinkedList* prev;
};

LinkedList* FillLinkedList(int size)
{
	LinkedList* tmp = new LinkedList;
	LinkedList* head = tmp;
	tmp->value = rand() % 10;
	///
	for (int i = 0; i < size - 1; ++i)
	{
		tmp->next = new LinkedList;
		tmp = tmp->next;
		tmp->value = rand() % 10;
	}
	tmp->next = nullptr;
	return head;
}

void PrintLinkedList(LinkedList* head)
{
	int size = 0;
	while (head != nullptr)
	{
		++size;
		std::cout << head << " ->" << head->value << std::endl;
		head = head->next;
	}
	std::cout << std::endl;
}

void LLSwap(LinkedList* ll1, LinkedList* ll2)
{
	ll1->value = ll1->value + ll2->value;
	ll2->value = ll1->value - ll2->value;
	ll2->value = ll1->value - ll2->value;
}

void RemoveDups(LinkedList* node)
{
	std::vector<int> intset;
	while (node != nullptr)
	{
		if (std::find(intset.begin(), intset.end(), node->value) < intset.end())
		{
			node->prev = node->next;
			node->next->prev = node->prev;
		}
		else
		{
			intset.push_back(node->value);
		}
		node = node->prev;
	}
}

LinkedList* KthfromLast_(LinkedList* node, int& k)
{
	LinkedList* tmp = (node->next != nullptr) ? KthfromLast_(node->next, k) : nullptr;
	k--;
	return (k == -1)? node : tmp;
}

LinkedList* KthfromLast(LinkedList* node, int k)
{
	return KthfromLast_(node, k);
}

LinkedList* DeleteMiddleNode_(LinkedList*& node, int& size, int& currElem)
{
	LinkedList* tmp = (node->next != nullptr) ? DeleteMiddleNode_(node->next, ++size, ++currElem) : nullptr; /// achived last element
	--currElem;
	if (currElem == size / 2)
	{
		delete node;
		return tmp;
	}
	else if (currElem == (size / 2) - 1)
	{
		node->next = tmp;
	}
	return node;
}

void DeleteMiddleNode(LinkedList*& node)
{
	int size = 0;
	int curElem = 0;
	DeleteMiddleNode_(node, size, curElem);
}

LinkedList* DeleteMidleNode(LinkedList* node)
{
	return nullptr;
}

LinkedList* Partition(LinkedList* head, int PartValue)
{
	return nullptr;
}

LinkedList* SumLinkedList(LinkedList* ll1, LinkedList* ll2)
{ /// not optimal
	LinkedList* sum = new LinkedList;
	LinkedList* tmp = sum;
	int sum_ = 0;
	int module_ = 0;
	while (ll1 != nullptr || ll2 != nullptr)
	{
		if (ll1 != nullptr && ll2 != nullptr)
		{
			sum_ = ll1->value + ll2->value;
			ll1 = ll1->next;
			ll2 = ll2->next;
		}
		else if (ll1 != nullptr)
		{
			sum_ = ll1->value;
			ll1 = ll1->next;
		}
		else
		{
			sum_ = ll2->value;
			ll2 = ll2->next;
		}
		sum_ += module_;
		tmp->value = sum_ % 10;
		module_ = sum_ / 10;
		if (ll1 != nullptr || ll2 != nullptr)
		{
			tmp->next = new LinkedList;
		}
		else
		{
			tmp->next = nullptr;
		}
		tmp = tmp->next;
	}
	return sum;
}

bool IsLinkedListPalindrome(LinkedList* node)
{
	std::stack<int> nodeSet;
	LinkedList* head = node;
	while (node != nullptr)
	{
		nodeSet.push(node->value);
		node = node->next;
	}
	while (head != nullptr) /// maybe not need to chack
	{
		if (head->value != nodeSet.top())
		{
			return false;
		}
		nodeSet.pop();
		head = head->next;
	}
	return true;
}

LinkedList* LinkedListIntersection(LinkedList* ll1, LinkedList* ll2)
{
	LinkedList* ll1_ = ll1;
	LinkedList* ll2_ = ll2;
	size_t ll1Size = 0;
	size_t ll2Size = 0;
	while (ll1->next != nullptr) { /// detect if thay have same end node
		ll1 = ll1->next;
		++ll1Size;
	}
	while (ll2->next != nullptr) {
		ll2 = ll2->next;
		++ll2Size;
	}
	if (ll1 != ll2)
	{
		return nullptr;
	}
	if (ll1Size > ll2Size) /// cut corresponding start
	{
		for (size_t i = 0; i < (ll1Size - ll2Size); ++i)
		{
			ll1_ = ll1->next;
		}
	}
	else
	{
		for (size_t i = 0; i < (ll2Size - ll1Size); ++i)
		{
			ll2_ = ll2->next;
		}
	}
	while (ll1_ != ll2_)
	{
		ll1_ = ll1_->next;
		ll2_ = ll2_->next;
	}
	return ll1_;

}

LinkedList* LoopDetection(LinkedList* ll1)
{
	LinkedList* fastPtr = ll1;
	LinkedList* slowPtr = ll1;
	while (fastPtr != nullptr && fastPtr->next != nullptr)
	{
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next->next;
		if (fastPtr == slowPtr)
		{
			fastPtr = ll1;
			while (fastPtr != slowPtr)
			{
				fastPtr = fastPtr->next;
				slowPtr = slowPtr->next;
			}
			return fastPtr;
		}
	}
	return nullptr;
}
