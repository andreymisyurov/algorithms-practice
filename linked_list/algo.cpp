#include <iostream>

typedef struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
} ListNode;
// D -> 1 -> 2 -> 3 -> 4 -> 5 -> NULL
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;

    ListNode* tmp = &dummy;
    int len = 0;
    for(;tmp != nullptr;) {
        ++len;
        tmp = tmp->next;
    }

    len = len - n - 1;
    tmp = &dummy;
    for(;len; --len)
        tmp = tmp->next;
    ListNode* remove_node = tmp->next;
    tmp->next = tmp->next->next;
    delete remove_node;
    return dummy.next;
}

void printList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "NULL" << std::endl;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    std::cout << "before: ";
    printList(head);
    head = removeNthFromEnd(head, 5);

    std::cout << "after: ";
    printList(head);

    // Освобождение оставшихся узлов
    while (head != nullptr) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}