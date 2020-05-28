#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#include<iostream>
#include<exception>

template <typename T>
class Vector {
private:
    T* arr;
    int storage;
    int count;

    void copyVectors(const Vector&);
public:
    Vector();
    Vector(int);
    Vector(const Vector&);
    Vector& operator=(const Vector&);
    ~Vector();

    //friend std::istream& operator>>(std::istream&, Vector<T>);


    void add(const T&);
    int getStorage() const;
    int size() const;
    void print() const;
    void pushAtIndex(const T&, int);
    void removeAtIndex(int);
    void clear();
    void deleteVector();
    void allocateMemory(int);
    void addToCount();

    bool operator==(const Vector<T>&) const;
    T& operator[](int) const;
};

template <typename T>
void Vector<T>::copyVectors(const Vector& other) {
    arr = new(std::nothrow) T[other.storage];
    if (arr == nullptr) {
        throw ("No memory for vector!(Vector<T>::copyVectors())");
        return;
    }
    for (int i = 0; i < other.storage; i++) {
        arr[i] = other.arr[i];
    }
    storage = other.storage;
    count = other.count;
}

template <typename T>
void Vector<T>::deleteVector() {
    delete[] arr;
}
//----------------------------------------------------------------

template <typename T>
Vector<T>::Vector() {
    arr = new(std::nothrow) T[1];
    if (arr == nullptr) {
        throw ("No memory for vector!(default constructor)");
    }
    storage = 1;
    count = 0;
}

template <typename T>
Vector<T>::Vector(int index) {
    arr = new(std::nothrow) T[index + 1];
    if (arr == nullptr) {
        throw ("No memory for vector!(constructor(int)");
    }
    storage = index + 1;
    count = 0;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
    copyVectors(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other) return *this;
    deleteVector();
    copyVectors(other);
    return *this;
}

template <typename T>
Vector<T>::~Vector() {
    deleteVector();
}
//----------------------------------------------------------------

template <typename T>
void Vector<T>::add(const T& element) {
    if (storage == count) {
        T* temp = new(std::nothrow) T[2 * storage];
        if (temp == nullptr) {
            throw ("No memory for vector!(Vector<T>::add())");
            return;
        }
        for (int i = 0; i < storage; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        storage *= 2;
        arr = temp;
    }
    arr[count] = element;
    count++;
}

template <typename T>
void Vector<T>::pushAtIndex(const T& element, int index) {
    arr[index] = element;
}

template <typename T>
void Vector<T>::removeAtIndex(int i) {
    if (i<0 || i>count) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    
    Vector<T> tempVector(count - 1);
    int br = 0;
    for (int j = 0; j < i; j++) {
        tempVector[br] = arr[j];
        br++;
        tempVector.addToCount();
    }
    for (int j = i + 1; j < count; j++) {
        tempVector[br] = arr[j];
        br++;
        tempVector.addToCount();
    }
    
    *this = tempVector;
}

template <typename T>
int Vector<T>::getStorage() const {
    return storage;
}

template <typename T>
int Vector<T>::size() const {
    return count;
}

template <typename T>
void Vector<T>::print() const {
    for (int i = 0; i < count; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
    if (count != other.count) return false;
    for (int i = 0; i < count; i++) {
        if (arr[i] != other.arr[i]) return false;
    }
    return true;
}

template <typename T>
T& Vector<T>::operator[](int i) const {
    return arr[i];
}

template <typename T>
void Vector<T>::clear() {
    delete[] arr;
    arr = new(std::nothrow) T[1];
    if (arr == nullptr) {
        throw ("No memory for vector!(Vector<T>::clear())");
        return;
    }
    storage = 1;
    count = 0;
}

template <typename T>
void Vector<T>::allocateMemory(int index) {
    arr = new(std::nothrow) T[index + 1];
    if (arr == nullptr) {
        throw ("No memory for vector!(Vector<T>::allocateMemory())");
        return;
    }
    storage = index + 1;
    count = 0;
}

template <typename T>
void Vector<T>::addToCount() {
    count++;
}

/*template <typename T>
std::istream& operator>>(std::istream& in, Vector<T> vector) {

}*/

#endif // VECTOR_HPP_




