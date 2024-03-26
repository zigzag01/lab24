// Белоушко Елизавета ПИ 1 курс
// В функцию DelNum добавлен try/catch блок  =>  ошибка
// В конструкторе проверка, является ли размер массива числом меньше 0, если да  =>  ошибка 

#include <iostream>  
#include <ctime>  
using namespace std;

template<typename Type>
class MyException {
    Type report;
public:
    MyException() {}
    MyException(Type report) {
        this->report = report;
    }
    Type what() const {
        return report;
    }
};

template<typename Type>
class Array {
    Type* arr;
    Type n;
public:
    ~Array() {
        delete[] arr;
    };
    Array();
    Array(Type size) {
        if (size <= 0) {
            throw MyException<string>("Ошибка: размер массива должен быть больше нуля.");
        }
        n = size;
        arr = new Type[n];
    }

    // ф-ия выводит составные числа массива
    friend void DelNum(Array<Type>& arr) {
        try {
            int m = 0; // считает кол-во делителей числа  
            for (int i = 0; i <= arr.n; i++) { // заменила i < arr.n на i <= arr.n  =>  выход за пределы массива
                if (i >= arr.n) {
                    throw MyException<string>("Ошибка: выход за пределы массива.");
                }
                for (int k = 2; k <= arr.arr[i] / 2; k++) {
                    if (arr.arr[i] % k == 0) {
                        m++;
                    }
                }
                if (m != 0) {
                    cout << arr.arr[i] << " ";
                    m = 0;
                }
            }
            cout << endl;
        }
        catch (exception& ex) {
            cerr << ex.what() << endl;
        }
    }


    template<typename Type>
    friend istream& operator>>(istream& in, Array<Type>& arr);

    template<typename Type>
    friend ostream& operator<<(ostream& out, Array<Type>& arr);

    template<typename Type>
    friend void DelNum(Array<Type>& arr);
};


template<typename Type>
istream& operator>>(istream& in, Array<Type>& arr) {
    srand(time(0));
    for (int i = 0; i < arr.n; i++) {
        arr.arr[i] = rand() % 100 + 1;
    }
    return in;
}

template<typename Type>
ostream& operator<<(ostream& out, Array<Type>& arr) {
    srand(time(0));
    cout << "Дан массив чисел: ";
    for (int i = 0; i < arr.n; i++) {
        cout << arr.arr[i] << " ";
    }
    cout << endl;
    return out;
}

int main() {
    setlocale(LC_ALL, "rus");
    int n;
    cout << "Введите длину массива: ";
    cin >> n;

    try {
        Array<int>arr(n);
        cin >> arr;
        cout << arr;
        DelNum(arr);
    }
    catch (MyException<string>& e) {
        cerr << e.what() << endl;
    }

    system("pause");
    return 0;
}
