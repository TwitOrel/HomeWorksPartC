//
// Created by Orel on 31/01/2024.
//

#ifndef HW1_RCPTR_H
#define HW1_RCPTR_H
#include <iostream>

template <typename T>
class RCPtr{
private:
    T* data;
    unsigned int *count;
public:
    RCPtr(T *val):data(val),count(new unsigned int (1)){
    }

    RCPtr(const RCPtr<T> &rhs):data(rhs.data),count(rhs.count){
        (*count)++;

    }

    ~RCPtr(){
        if ((--(*count)) == 0) {
            delete data;
            delete count;
        }
    }

    RCPtr& operator=(const RCPtr<T> &rhs){
        if (this == &rhs){
            return *this;
        }
        if ((--(*count)) == 0){
            delete data;
            delete count;
        }
        data = rhs.data;
        count = rhs.count;
        ++(*count);

        return *this;
    }

    bool operator==(const RCPtr<T> &rhs){
        return data == rhs.data;
    }

    unsigned int use_count() const{
        return *count;
    }

    T& operator*(){
        return *(data);
    }

    const T& operator*() const{
        return *(data);
    }

    T* operator->(){
        return data;
    }
    const T* operator->()const{
        return data;
    }
};
#endif //HW1_RCPTR_H