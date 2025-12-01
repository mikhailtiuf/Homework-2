#include <iostream>
#include <cstdlib>

using namespace std;

class DynamicIntVector {
private:
    int* storage;
    int capacity;

public:
    DynamicIntVector(int initialCapacity) {
        if (initialCapacity <= 0) {
            capacity = 1;
        }
        else {
            capacity = initialCapacity;
        }

        storage = new int[capacity];
        for (int j = 0; j < capacity; j++) {
            storage[j] = 0;
        }
        cout << "Инициализирован вектор емкостью " << capacity << endl;
    }

    DynamicIntVector(const DynamicIntVector& source) {
        capacity = source.capacity;
        storage = new int[capacity];

        for (int j = 0; j < capacity; j++) {
            storage[j] = source.storage[j];
        }
        cout << "Создан дубликат вектора емкостью " << capacity << endl;
    }

    ~DynamicIntVector() {
        delete[] storage;
        cout << "Вектор емкостью " << capacity << " уничтожен" << endl;
    }

    void display() const {
        cout << "Вектор [емкость: " << capacity << "]: ";
        for (int j = 0; j < capacity; j++) {
            cout << storage[j];
            if (j < capacity - 1) {
                cout << " | ";
            }
        }
        cout << endl;
    }

    bool assignElement(int position, int elementValue) {
        if (position < 0 || position >= capacity) {
            cout << "Недопустимая позиция: " << position << "! Допустимый диапазон: 0-" << capacity - 1 << "!" << endl;
            return false;
        }

        if (elementValue < -100 || elementValue > 100) {
            cout << "Недопустимое значение: " << elementValue << "! Требуется диапазон [-100, 100]!" << endl;
            return false;
        }

        storage[position] = elementValue;
        cout << "Элемент " << elementValue << " размещен в позиции " << position << endl;
        return true;
    }

    bool retrieveElement(int position, int& outputValue) const {
        if (position < 0 || position >= capacity) {
            cout << "Недопустимая позиция: " << position << "! Допустимый диапазон: 0-" << capacity - 1 << "!" << endl;
            return false;
        }

        outputValue = storage[position];
        return true;
    }

    void insertAtEnd(int elementValue) {
        if (elementValue < -100 || elementValue > 100) {
            cout << "Недопустимое значение для добавления: " << elementValue << "! Требуется диапазон [-100, 100]!" << endl;
            return;
        }

        int newCapacity = capacity + 1;
        int* newStorage = new int[newCapacity];

        for (int j = 0; j < capacity; j++) {
            newStorage[j] = storage[j];
        }

        newStorage[capacity] = elementValue;

        delete[] storage;
        storage = newStorage;
        capacity = newCapacity;

        cout << "Добавлен элемент " << elementValue << ". Новая емкость: " << capacity << endl;
    }

    DynamicIntVector combine(const DynamicIntVector& secondVector) const {
        int maximumCapacity = (capacity > secondVector.capacity) ? capacity : secondVector.capacity;
        DynamicIntVector outputVector(maximumCapacity);

        for (int j = 0; j < maximumCapacity; j++) {
            int total = 0;

            if (j < capacity) {
                total += storage[j];
            }

            if (j < secondVector.capacity) {
                total += secondVector.storage[j];
            }

            if (total < -100) total = -100;
            if (total > 100) total = 100;

            outputVector.storage[j] = total;
        }

        cout << "Выполнена операция объединения векторов" << endl;
        return outputVector;
    }

    DynamicIntVector subtract(const DynamicIntVector& secondVector) const {
        int maximumCapacity = (capacity > secondVector.capacity) ? capacity : secondVector.capacity;
        DynamicIntVector outputVector(maximumCapacity);

        for (int j = 0; j < maximumCapacity; j++) {
            int difference = 0;

            if (j < capacity) {
                difference += storage[j];
            }

            if (j < secondVector.capacity) {
                difference -= secondVector.storage[j];
            }

            if (difference < -100) difference = -100;
            if (difference > 100) difference = 100;

            outputVector.storage[j] = difference;
        }

        cout << "Выполнена операция вычитания векторов" << endl;
        return outputVector;
    }

    int getCapacity() const { return capacity; }
};

int main() {
    setlocale(LC_ALL, "RU");
    cout << "=== Демонстрация работы класса DynamicIntVector ===" << endl;

    cout << "\n1. Создание вектора емкостью 3:" << endl;
    DynamicIntVector vec1(3);
    vec1.display();

    cout << "\n2. Заполнение вектора значениями:" << endl;
    vec1.assignElement(0, 10);
    vec1.assignElement(1, 50);
    vec1.assignElement(2, -30);
    vec1.display();

    cout << "\n3. Проверка обработки ошибочных ситуаций:" << endl;
    vec1.assignElement(5, 20);
    vec1.assignElement(1, 150);

    cout << "\n4. Проверка извлечения элементов:" << endl;
    int extractedValue;
    if (vec1.retrieveElement(1, extractedValue)) {
        cout << "Извлеченный элемент из позиции 1: " << extractedValue << endl;
    }

    cout << "\n5. Проверка копирования вектора:" << endl;
    DynamicIntVector vec2 = vec1;
    cout << "Исходный вектор: ";
    vec1.display();
    cout << "Скопированный вектор: ";
    vec2.display();

    cout << "\n6. Добавление элементов в конец:" << endl;
    vec1.insertAtEnd(80);
    vec1.insertAtEnd(-90);
    vec1.display();
    vec1.insertAtEnd(150);

    cout << "\n7. Арифметические операции над векторами:" << endl;

    DynamicIntVector vectorA(3);
    vectorA.assignElement(0, 10);
    vectorA.assignElement(1, 20);
    vectorA.assignElement(2, 30);

    DynamicIntVector vectorB(2);
    vectorB.assignElement(0, 5);
    vectorB.assignElement(1, 15);

    cout << "Вектор A: ";
    vectorA.display();
    cout << "Вектор B: ";
    vectorB.display();

    DynamicIntVector sumResult = vectorA.combine(vectorB);
    cout << "A + B: ";
    sumResult.display();

    DynamicIntVector diffResult = vectorA.subtract(vectorB);
    cout << "A - B: ";
    diffResult.display();

    cout << "\n8. Работа с векторами разной длины:" << endl;

    DynamicIntVector shortVector(2);
    shortVector.assignElement(0, 40);
    shortVector.assignElement(1, 60);

    DynamicIntVector longVector(4);
    longVector.assignElement(0, 1);
    longVector.assignElement(1, 2);
    longVector.assignElement(2, 3);
    longVector.assignElement(3, 4);

    cout << "Короткий вектор: ";
    shortVector.display();
    cout << "Длинный вектор: ";
    longVector.display();

    DynamicIntVector combinedResult = shortVector.combine(longVector);
    cout << "Короткий + Длинный: ";
    combinedResult.display();

    cout << "\n=== Работа программы завершена ===" << endl;

    return 0;
}
