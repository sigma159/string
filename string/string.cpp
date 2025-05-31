#include <iostream>
#include <string>

template <typename T>
class Array {
private:
    T* data;
    int size; 
    int count; 
    int grow;

public:
    Array(int size = 0, int grow = 1) : size(size), count(0), grow(grow) {
        data = (size > 0) ? new T[size] : nullptr;
    }

    ~Array() {
        delete[] data;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int newGrow = 1) {
        grow = newGrow;
        if (newSize == size)
            return;

        T* newData = (newSize > 0) ? new T[newSize] : nullptr;
        int copyCount = (newSize < count) ? newSize : count;

        for (int i = 0; i < copyCount; ++i)
            newData[i] = data[i];

        delete[] data;
        data = newData;
        size = newSize;
        if (count > size) count = size;
    }

    int GetUpperBound() const {
        return (count > 0) ? count - 1 : -1;
    }

    bool IsEmpty() const {
        return count == 0;
    }

    void FreeExtra() {
        if (count < size) {
            SetSize(count, grow);
        }
    }

    void RemoveAll() {
        delete[] data;
        data = nullptr;
        size = 0;
        count = 0;
    }

    T GetAt(int index) const {
        if (index >= 0 && index < count)
            return data[index];
        std::cerr << "Помилка: індекс виходить за межі.\n";
        return T();
    }

    void SetAt(int index, const T& value) {
        if (index >= 0 && index < size)
            data[index] = value;
        else
            std::cerr << "Помилка: індекс виходить за межі.\n";
    }

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    void Add(const T& value) {
        if (count >= size) {
            SetSize(size + grow, grow);
        }
        data[count++] = value;
    }

    void Append(const Array<T>& other) {
        int total = count + other.count;
        if (total > size)
            SetSize(total + grow, grow);
        for (int i = 0; i < other.count; ++i)
            data[count++] = other.data[i];
    }

    Array<T>& operator=(const Array<T>& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            count = other.count;
            grow = other.grow;
            data = (size > 0) ? new T[size] : nullptr;
            for (int i = 0; i < count; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    T* GetData() {
        return data;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > count) {
            std::cerr << "Помилка: індекс виходить за межі.\n";
            return;
        }

        if (count >= size)
            SetSize(size + grow, grow);

        for (int i = count; i > index; --i)
            data[i] = data[i - 1];

        data[index] = value;
        ++count;
    }

    void RemoveAt(int index, int removeCount = 1) {
        if (index < 0 || index >= count || removeCount <= 0 || index + removeCount > count) {
            std::cerr << "Помилка: індекс виходить за межі або неправильна кількість.\n";
            return;
        }

        for (int i = index; i < count - removeCount; ++i)
            data[i] = data[i + removeCount];

        count -= removeCount;
    }
};

int main() {
    Array<std::string> arr(2, 2);
    arr.Add("Привіт");
    arr.Add("Сігма");
    arr.Add("хз");

    for (int i = 0; i <= arr.GetUpperBound(); ++i)
        std::cout << arr[i] << "\n";

    arr.InsertAt(1, "Шаблон");
    std::cout << "\nПісля вставки:\n";
    for (int i = 0; i <= arr.GetUpperBound(); ++i)
        std::cout << arr[i] << "\n";

    arr.RemoveAt(2);
    std::cout << "\nПісля видалення:\n";
    for (int i = 0; i <= arr.GetUpperBound(); ++i)
        std::cout << arr[i] << "\n";

    return 0;
}

