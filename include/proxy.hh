#ifndef PROXY_HH
#define PROXY_HH

template <class T> class Proxy {
  static int next_id;

public:
  int id = next_id++;
  T *link = nullptr;
  Proxy<T> *next = nullptr;

  Proxy(T *link) : link(link) {}
};

template <class T> int Proxy<T>::next_id = 0;
#endif
