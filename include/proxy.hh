#ifndef PROXY_HH
#define PROXY_HH

template <class T>
class Proxy {
public:
    T *link = nullptr;
    Proxy<T> *next = nullptr;

    Proxy(T *link) : link(link) {}

    void add(T *link);
};

template <class T>
void Proxy<T>::add(T *newLink) {
    if (next == nullptr) {
        next = new Proxy<T>(newLink);
    } else {
        next->add(newLink);
    }
}

#endif
