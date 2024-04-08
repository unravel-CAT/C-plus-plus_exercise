#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <cassert>

template<class T>
class Array {
public:
    Array(int sz = 50);                       // 构造函数
    Array(const Array<T>& a);                 // 复制构造函数
    ~Array();                                 // 析构函数
    Array<T>& operator=(const Array<T>& rhs); // 重载=
    T& operator[](int i);                     // 重载[]
    const T& operator[](int i) const;         // []针对const的重载
    operator T*();                            // 重载到T*类型的转换
    operator const T*() const;                // 到T*类型的转换针对const的重载
    int getSize() const;                      // 数组大小
    void resize(int sz);                      // 修改数组大小
private:
    T* list;  // T类型指针，用于存放动态分配的数组内存首地址
    int size; // 数组大小
};

// 构造函数
template<class T>
Array<T>::Array(int sz) {
    assert(sz >= 0);
    size = sz;
    list = new T[size];
}

// 析构函数
template<class T>
Array<T>::~Array() {
    delete[] list;
}

// 复制构造函数
template<class T>
Array<T>::Array(const Array<T>& a) {
    size = a.size;
    list = new T[size];
    for (int i = 0; i < size; ++i)
        list[i] = a.list[i];
}

// 重载=运算符，将rhs赋值给本对象
template<class T>
Array<T>& Array<T>::operator=(const Array<T>& rhs) {
    if (&rhs != this) {
        if (size != rhs.size) {
            delete[] list;
            size = rhs.size;
            list = new T[size];
        }
        for (int i = 0; i < size; ++i)
            list[i] = rhs.list[i];
    }
    return *this;
}

// 重载[]运算符，并且具有越界检查功能
template<class T>
T& Array<T>::operator[](int n) {
    assert(n >= 0 && n < size);
    return list[n];
}

// 重载指针转换运算符，将Array类的对象名转换为T类型的指针
template<class T>
Array<T>::operator T*() {
    return list;
}

template<class T>
Array<T>::operator const T*() const {
    return list;
}

// 取当前数组的大小
template<class T>
int Array<T>::getSize() const {
    return size;
}

// 修改数组大小
template<class T>
void Array<T>::resize(int sz) {
    assert(sz >= 0);
    if (sz == size) return;
    T* newList = new T[sz];
    int n = (sz < size) ? sz : size;
    for (int i = 0; i < n; ++i)
        newList[i] = list[i];
    delete[] list;
    list = newList;
    size = sz;
}

#endif // __ARRAY_H__