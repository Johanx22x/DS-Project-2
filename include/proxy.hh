#ifndef PROXY_HH
#define PROXY_HH

template <class T>
class Proxy {
public:
    T *link = nullptr;
    T *next = nullptr;

    Proxy(T *link) : link(link) {}
};

#endif
