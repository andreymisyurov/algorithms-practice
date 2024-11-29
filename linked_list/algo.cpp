#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class LinkedList {
private:
    struct ListNode* m_head;
    
    size_t get_len() {
        size_t len = 0;
        ListNode* tmp = m_head;
        for(;tmp;++len)
            tmp = tmp->next;
        return len;
    }

public:
    LinkedList() : m_head(nullptr) {}

    ~LinkedList() {
        for(;m_head;) {
            struct ListNode* tmp = m_head;
            m_head = m_head->next;
            delete tmp;
        }
    }

    void add_node(int in_value) {
        if(!m_head) {
            m_head = new ListNode(in_value);
        } else {
            struct ListNode* tmp = m_head;
            for(;tmp->next;)
                tmp = tmp->next;
            tmp->next = new ListNode(in_value); 
        }
    }

    void print() {
        struct ListNode* tmp = m_head;
        for(;tmp;) {
            std::cout << tmp->val << " -> ";
            tmp = tmp->next;
        }
        std::cout << "NULL" << std::endl;
    }

    ListNode* removeNodeFromEnd(int in_n) {
        ListNode dummy(0);
        dummy.next = m_head;
        int len = get_len() - in_n;
        ListNode* tmp = &dummy;
        for( ; len ; --len )
            tmp = tmp->next;
        ListNode* rm_node = tmp->next;
        if (rm_node == m_head) {
            m_head = m_head->next;
        }
        tmp->next = tmp->next->next;
        delete rm_node;
        return dummy.next;
    }

    ListNode* removeNodeFromEnd(size_t in_n) {
        ListNode dummy(0);
        dummy.next = m_head;
        ListNode* fast = &dummy;
        
        for( ; in_n ; --in_n )
            fast = fast->next;

        ListNode* slow = &dummy;
        for (;fast->next;) {
            fast = fast->next;
            slow = slow->next;
        }

        ListNode* rm_node = slow->next;
        slow->next = slow->next->next;
        
        if (rm_node == m_head) {
            m_head = m_head->next;
        }

        delete rm_node;
        return dummy.next;
    }
};

int main() {
    LinkedList list;
    list.add_node(1);
    list.add_node(2);
    list.add_node(3);
    list.add_node(4);
    list.add_node(5);
    list.add_node(6);
    list.add_node(7);
    list.print();
    list.removeNodeFromEnd((size_t)7);
    list.print();
}
