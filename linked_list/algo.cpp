#include <iostream>
#include <vector>

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
        // for(;m_head;) {
        //     struct ListNode* tmp = m_head;
        //     m_head = m_head->next;
        //     delete tmp;
        // }
    }

    ListNode* get_head() {
        return m_head;
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

    static void print(ListNode* tmp) {
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

    ListNode* reverse() {
        ListNode* curr = m_head;
        ListNode* prev = nullptr;
        for(;curr;) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        m_head = prev;
        return prev;
    }

    ListNode* reverse(ListNode* curr) {
        ListNode* prev = nullptr;
        for(;curr;) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    ListNode* middle_node() {
        ListNode* fast = m_head;
        ListNode* slow = m_head;
        for(;fast->next;) {
            slow = slow->next;
            fast = fast->next;
            if (fast->next)
                fast = fast->next;
            else
                break;
        }

        return slow;
    }

    bool palindrom() {
        ListNode* head = m_head;
        ListNode* tail = reverse(middle_node());
        ListNode* tail_copy = tail;
        for(;head && tail;) {
            if (head->val != tail->val)
                return false;
            head = head->next;
            tail = tail->next;
        }
        reverse(tail_copy);
        return true;
    }

    void reorder() {
        ListNode* middle = middle_node();
        ListNode* tail = reverse(middle->next);
        ListNode* head = m_head;
        middle->next = nullptr;
        for(;tail;) {
            ListNode* temp1 = head->next;
            ListNode* temp2 = tail->next;

            head->next = tail;
            tail->next = temp1;

            head = temp1;
            tail = temp2;
        }
    }

    static ListNode* merge_two_lists(ListNode* first, ListNode* second) {
        ListNode dummy(0);
        ListNode* tmp = &dummy;
        for(;first && second;) {
            if(first->val <= second->val) {
                tmp->next = first;
                first = first->next;
            } else {
                tmp->next = second;
                second = second->next;
            }
            tmp = tmp->next;
        }
        tmp->next = first ? first : second;
        return dummy.next;
    }

    static ListNode* merge_k_lists(std::vector<ListNode*> data) {
    
        auto get_min = [&data](){
            int min_i = -1;
            int min = INT32_MAX;
            for (int i = 0, len = data.size(); i < len; ++i) {
                if (data[i] != nullptr && data[i]->val <= min) {
                    min = data[i]->val;
                    min_i = i;
                }
            }
            return min_i < 0 ? -1 : min_i;   
        };

        ListNode dummy(0);
        ListNode* cur = &dummy;
        
        for(;;) {
            int min_i = get_min();
            if(min_i == -1)
                break;

            cur->next = data[min_i];
            cur = cur->next;
            data[min_i] = data[min_i]->next;
        }
        return dummy.next;
    }

};

int main() {
    LinkedList list1;
    list1.add_node(1);
    list1.add_node(1);
    list1.add_node(3);
    list1.add_node(6);
    list1.add_node(6);
    list1.add_node(7);
    list1.add_node(10);

    LinkedList list2;
    list2.add_node(5);
    list2.add_node(5);
    list2.add_node(8);
    list2.add_node(99);


    LinkedList list3;
    list3.add_node(1);
    list3.add_node(2);
    list3.add_node(4);
    list3.add_node(9);

    std::vector<ListNode*> vec;
    vec.push_back(list1.get_head());
    vec.push_back(list2.get_head());
    vec.push_back(list3.get_head());

    LinkedList::print(LinkedList::merge_k_lists(vec));
}
