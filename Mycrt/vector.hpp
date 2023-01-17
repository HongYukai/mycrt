#ifndef MYCRT_VECTOR_HPP
#define MYCRT_VECTOR_HPP

namespace std {
    template <class T>
    class vector {
    public:
        typedef T value_type;
        typedef value_type* iterator;
        typedef value_type& reference;
        typedef unsigned long long size_type;
    protected:
        iterator start;
        iterator finish;
        iterator end_of_storage;
    public:
        iterator begin() {
            return start;
        }
        iterator end() {
            return finish;
        }
        size_type size() {
            return size_type(end() - begin());
        }
        size_type size() const {
            return size_type(end() - begin());
        }
        size_type capacity() {
            return size_type(end_of_storage - begin());
        }
        size_type capacity() const {
            return size_type(end_of_storage - begin());
        }
        bool empty() const {
            return begin() == end();
        }
        reference operator[](size_type n) {
            return *(begin() + n);
        }
        reference front() {
            return *begin();
        }
        reference back() {
            return *(end() - 1);
        }
        void pop_back() {
            if (begin() == end()) {
                throw "array index error";
            }
            else {
                delete finish;
                --finish;
            }
        }
        void push_back(const value_type x) {
            if (finish != end_of_storage) {
                *finish = x;
                ++finish;
            }
            else {
                const size_type old_size = size();
                const size_type len = old_size == 0 ? 1 : 2 * old_size;
                iterator new_start = new value_type[len];
                iterator new_finish = new_start;
                auto ite = begin();
                while (ite != end()) {
                    *new_finish++ = *ite++;
                }
                ite = begin();
                while (ite != end()) {
                    delete ite;
                    ++ite;
                }
                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + len;
            }
        }
    };
}

#endif // MYCRT_VECTOR_HPP