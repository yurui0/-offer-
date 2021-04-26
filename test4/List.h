
struct ListNode  //单向链表，包括当前节点的值+指向下一个节点的指针
{
	int m_nValue;
	ListNode* m_pNext;
};

ListNode* CreateListNode(int value);
void ConnectListNodes(ListNode* pCurrent, ListNode* pNext);
void PrintListNode(ListNode* pNode);
void PrintList(ListNode* pHead);
void DestroyList(ListNode* pHead);
void AddToTail(ListNode** pHead, int value);
void RemoveNode(ListNode** pHead, int value);

/*
__declspec(dllexport) ListNode* CreateListNode(int value);
__declspec(dllexport) void ConnectListNodes(ListNode* pCurrent, ListNode* pNext);
__declspec(dllexport) void PrintListNode(ListNode* pNode);
__declspec(dllexport) void PrintList(ListNode* pHead);
__declspec(dllexport) void DestroyList(ListNode* pHead);
__declspec(dllexport) void AddToTail(ListNode** pHead, int value);
__declspec(dllexport) void RemoveNode(ListNode** pHead, int value);


*/


