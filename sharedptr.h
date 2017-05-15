#ifndef SHAREDPTR_H_
#define SHAREDPTR_H_


template<class T>
class SharedPtr {
public:
    explicit SharedPtr(T *p);
    SharedPtr(const SharedPtr& p);
    SharedPtr();
    ~SharedPtr();

    bool isOwner() const {return (getCounter() == 1);}
    bool isEmpty() const {return (raw() == 0);}

    bool operator==(const SharedPtr& p);
    SharedPtr& operator=(const SharedPtr& p);
    T* operator->() const;
    T& operator*() const;
    const T* raw() const;
    unsigned int getCounter() const;
    void release();

private:
    struct Pair {
        unsigned int  counter;
        T            *pointer;

        Pair(unsigned int counter, T* pointer) {this->counter = counter; this->pointer = pointer;}
    };
    Pair *meta;
};

template<class T>
SharedPtr<T>::SharedPtr(T *p) {
    meta = new Pair(1, p);
}

template<class T>
SharedPtr<T>::SharedPtr():meta(0) {}

template<class T>
bool SharedPtr<T>::operator==(const SharedPtr& p) {return (meta == p.meta);}

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& p) {
    meta = p.meta;
    if (meta != 0)
        meta->counter++;
}

template<class T>
SharedPtr<T>& SharedPtr<T>::operator= (const SharedPtr& p) {
    if (meta != p.meta) {
        if (meta != 0)
            release();

        meta = p.meta;
        if (meta != 0)
            meta->counter++;
    }
    return *this;
}

template<class T>
T* SharedPtr<T>::operator->() const {return meta ? meta->pointer : 0;}

template<class T>
T& SharedPtr<T>::operator*() const {return *(meta->pointer);}

template<class T>
const T* SharedPtr<T>::raw() const {return meta ? meta->pointer : 0;}

template<class T>
unsigned int SharedPtr<T>::getCounter() const {return (meta ? meta->counter : 0);}

template<class T>
SharedPtr<T>::~SharedPtr() {release();}

template<class T>
void SharedPtr<T>::release() {
    if (meta != 0) {
        meta->counter--;
        if (meta->counter == 0) {
            delete meta->pointer;
            meta->pointer = 0;
            delete meta;
        }
        meta = 0;
    }
}


#endif /* SHAREDPTR_H_ */
