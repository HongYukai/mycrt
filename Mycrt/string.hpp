#ifndef MYCRT_STRING_HPP
#define MYCRT_STRING_HPP

#include "mycrt.h"
#include "iostream.hpp"
namespace std {
    class string {
        unsigned len;
        char* buf;
    public:
        string(const char* str);
        string(const string&);
        ~string();
        string& operator=(const string&);
        string& operator=(const char* s);
        const char& operator[](unsigned index) const;
        char& operator[](unsigned index);
        const char* c_str() const;
        unsigned length() const;
        unsigned size() const;
    };
    string::string(const char *str) : len(0), buf(0){
        *this = str;
    }
    string::string(const string &s) {
        *this = s;
    }
    string::~string() {
        if (buf != 0) {
            delete[] buf;
            buf = 0;
        }
    }
    string& string::operator=(const string &s) {
        if (&s == this) {
            return *this;
        }
        this->~string();
        len = s.len;
        buf = strcpy(new char[len + 1], s.buf);
        return *this;
    }
    string& string::operator=(const char *s) {
        this->~string();
        len = strlen(s);
        buf = strcpy(new char[len + 1], s);
        return *this;
    }
    const char& string::operator[](unsigned int index) const {
        return buf[index];
    }
    char &string::operator[](unsigned int index) {
        return buf[index];
    }
    const char *string::c_str() const {
        return buf;
    }
    unsigned int string::length() const {
        return len;
    }
    unsigned int string::size() const {
        return len;
    }
    ofstream& operator<<(ofstream& o, const string& s) {
        return o << s.c_str();
    }
}

#endif //MYCRT_STRING_HPP