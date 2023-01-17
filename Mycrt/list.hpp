#ifndef MYCRT_LIST_HPP
#define MYCRT_LIST_HPP

typedef unsigned long long size_t;

namespace std {
    template <class T>
    struct __list_node {
        __list_node(const T d) : next(nullptr), prev(nullptr), data(d) {}
        __list_node() : next(nullptr), prev(nullptr) {}
        __list_node<T>* next;
        __list_node<T>* prev;
        T data;
    };
    template <class T, class Ref, class Ptr>
    struct __list_iterator {
        typedef T value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef size_t difference_type;
        typedef __list_node<T>* link_type;
        typedef __list_iterator<T, Ref, Ptr> self;
        link_type node;
        __list_iterator(const self& x) : node(x.node) {}
        reference operator*() const {return (*node).data;}
        pointer operator->() const {return &(operator*());}
        bool operator==(const self& i) {
            return i.node == node;
        }
        bool operator!=(const self& i) {
            return i.node != node;
        }
        self& operator++() {
            node = (link_type)((*node).next);
            return *this;
        }
        self operator++(int) {
            auto tmp = *this;
            ++*this;
            return tmp;
        }
        self& operator--() {
            node = (link_type)((*node).prev);
            return *this;
        }
        self operator--(int) {
            auto tmp = *this;
            --*this;
            return tmp;
        }
    };
    template <class T>
    class list {
    protected:
        typedef __list_node<T> list_node;
    public:
        typedef list_node* link_type;
        typedef __list_iterator<T, T&, T*> iterator;
        list() : start(new iterator), finish(new iterator) {
            start.node->next = finish;
            finish.node->prev = start;
        }
        void push_back(const T data) {
            iterator end = new iterator();
            finish.node->next = end;
            end.node->prev = finish;
            finish.node->data = data;
            finish = end;
            len++;
        }
        void pop_back() {
            finish = finish.node->prev;
            delete finish.node->next;
            finish.node->next = nullptr;
        }
        void push_front(const T data) {
            iterator begin = new iterator();
            start.node->prev = begin;
            begin.node->next = start;
            start.node->data = data;
            start = begin;
            len++;
        }
        void pop_front() {
            start = start.node->next;
            delete start.node->next;
            start.node->next = nullptr;
        }
        size_t size() {
            return len;
        }
        iterator begin() {
            return start.operator++();
        }
        iterator end() {
            return finish;
        }
    protected:
        size_t len = 0;
        iterator start;
        iterator finish;
    };
}

#endif //MYCRT_LIST_HPP
