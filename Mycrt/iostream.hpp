#ifndef MYCRT_IOSTREAM_HPP
#define MYCRT_IOSTREAM_HPP



#include "mycrt.h"

namespace std {
    class ofstream {
    protected:
        int fp;
        ofstream(const ofstream&);
    public:
        enum openmode {IN=1, OUT=2, BINARY=4, TRUNC=8};
        ofstream();
        explicit ofstream(const char* filename, ofstream::openmode md = ofstream::OUT);
        ~ofstream();
        ofstream& operator<<(char c);
        ofstream& operator<<(int n);
        ofstream& operator<<(const char* str);
        ofstream& operator<<(ofstream& (*)(ofstream&));
        void fopen(const char* filename, ofstream::openmode md = ofstream::OUT);
        void fclose();
        ofstream& fwrite(const char* buf, unsigned size);
    };
    ofstream::ofstream() : fp(0) {
    }
    ofstream::ofstream(const char *filename, ofstream::openmode md) : fp(0) {
        fopen(filename, md);
    }
    ofstream::~ofstream() {
        fclose();
    }
    ofstream& ofstream::operator<<(char c) {
        fputc(c, fp);
        return *this;
    }
    ofstream& ofstream::operator<<(int n) {
        fprintf(fp, "%d", n);
        return *this;
    }
    ofstream& ofstream::operator<<(const char *str) {
        fprintf(fp, "%s", str);
        return *this;
    }
    ofstream &ofstream::operator<<(ofstream &(*manip)(ofstream &)) {
        return manip(*this);
    }
    void ofstream::fopen(const char *filename, ofstream::openmode md) {
        char mode[4];
        fclose();
        switch (md) {
            case OUT | TRUNC : {
                strcpy(mode, "w");
                break;
            }
            case OUT | IN | TRUNC: {
                strcpy(mode, "w+");
                break;
            }
            case OUT | BINARY | TRUNC: {
                strcpy(mode, "wb");
                break;
            }
            case OUT | IN | TRUNC | BINARY: {
                strcpy(mode, "wb+");
                break;
            }
        }
        fp = open(filename, mode);
    }
    void ofstream::fclose() {
        if (fp) {
            close(fp);
            fp = 0;
        }
    }
    ofstream &ofstream::fwrite(const char *buf, unsigned int size) {
        write(fp, (void *) buf, size);
        return *this;
    }
    inline ofstream& endl(ofstream& o) {
        return o << '\n';
    }
    class stdout_stream : public ofstream {
    public:
        stdout_stream();
    };
    stdout_stream::stdout_stream() : ofstream(){
        fp = stdout;
    }
    stdout_stream cout;
}

#endif //MYCRT_IOSTREAM_HPP