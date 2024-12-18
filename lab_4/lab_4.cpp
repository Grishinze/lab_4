#include <iostream> // Подключение библиотеки для работы с вводом-выводом
#include <limits>   // Подключение библиотеки для работы с пределами чисел

using namespace std; // Использование стандартного пространства имен

// Функция для ввода матрицы
void inputMatrix(double** matrix, int rows, int cols)
{
    for (int i = 0; i < rows; ++i) // Перебор строк
    {
        for (int j = 0; j < cols; ++j) // Перебор столбцов
        {
            cin >> matrix[i][j]; // Считывание элемента матрицы
        }
    }
}

// Функция для вывода матрицы
void printMatrix(double** matrix, int rows, int cols)
{
    for (int i = 0; i < rows; ++i) // Перебор строк
    {
        for (int j = 0; j < cols; ++j) // Перебор столбцов
        {
            // Вывод элемента матрицы с пробелом, если это не последний столбец
            cout << matrix[i][j] << (j < cols - 1 ? " " : "");
        }
        cout << endl; // Переход на новую строку после вывода строки матрицы
    }
}

// Функция для освобождения памяти матрицы
void clearMem(double** matrix, int rows) {
    for (int i = 0; i < rows; ++i) { // Перебор строк
        delete[] matrix[i]; // Удаление каждой строки
    }
    delete[] matrix; // Удаление массива указателей
}

// Безопасный ввод числа
int safeInput() {
    int x; // Переменная для хранения ввода
    while (!(cin >> x)) { // Проверка корректности ввода
        cin.clear(); // Очистка потока ввода
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшегося ввода
        cout << "Некорректный ввод. Попробуйте снова: "; // Сообщение об ошибке
    }
    return x; // Возврат корректного числа
}

// Функция для умножения матриц
bool multiplyMatrices(double** A, int A_rows, int A_cols,
    double** B, int B_rows, int B_cols,
    double**& result, int& result_rows, int& result_cols) {
    if (A_cols != B_rows) { // Проверка совместимости матриц
        return false; // Возврат ошибки
    }
    result = new double* [A_rows]; // Создание результата
    for (int i = 0; i < A_rows; ++i) { // Перебор строк первой матрицы
        result[i] = new double[B_cols]; // Создание строки результата
        for (int j = 0; j < B_cols; ++j) { // Перебор столбцов второй матрицы
            result[i][j] = 0; // Инициализация элемента результата
            for (int k = 0; k < A_cols; ++k) { // Перебор элементов строки и столбца
                result[i][j] += A[i][k] * B[k][j]; // Суммирование произведений
            }
        }
    }
    result_rows = A_rows; // Установка числа строк результата
    result_cols = B_cols; // Установка числа столбцов результата
    return true; // Успешное выполнение
}

// Функция для возведения квадратной матрицы в степень
bool powerMatrix(double** A, int N, int exp, double**& result) {
    if (N <= 0 || exp < 1) { // Проверка корректности входных данных
        return false; // Возврат ошибки
    }
    result = new double* [N]; // Создание результата
    for (int i = 0; i < N; ++i) { // Перебор строк
        result[i] = new double[N]; // Создание строки
    }
    // Инициализация результата как исходной матрицы
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = A[i][j]; // Копирование элементов
        }
    }

    // Повторное умножение для возведения в степень
    double** temp; // Временная матрица
    for (int i = 1; i < exp; ++i) { // Цикл для возведения в степень
        if (!multiplyMatrices(result, N, N, A, N, N, temp, N, N)) { // Умножение матриц
            return false; // Возврат ошибки
        }
        for (int i = 0; i < N; ++i) { // Копирование результата
            for (int j = 0; j < N; ++j) {
                result[i][j] = temp[i][j];
            }
        }
        clearMem(temp, N); // Очистка временной матрицы
    }
    return true; // Успешное выполнение
}

// Основная функция
int main(int argc, char* argv[])
{
    bool isHuman = false;
    if (argc <= 1 || strcmp(argv[1], "false") != 0)
    {
        isHuman = true;
    }

    setlocale(LC_CTYPE, "rus"); // Установка локали для поддержки кириллицы

    // Ввод размеров матрицы
    if (isHuman)
        cout << "Введите размер матрицы N x M:" << endl; // Запрос размеров матрицы
    int N = safeInput(); // Ввод числа строк
    int M = safeInput(); // Ввод числа столбцов

    // Создание и ввод матрицы
    double** A1 = new double* [N]; // Создание указателя на строки
    for (int i = 0; i < N; ++i) { // Перебор строк
        A1[i] = new double[M]; // Создание строки
    }
    inputMatrix(A1, N, M); // Ввод матрицы

    while (true) { // Бесконечный цикл
        if (isHuman)
            cout << "Введите команду (0 - выход, 1 - вывод матрицы, 2 - умножение, 3 - возведение в степень): "; // Меню
        int command = safeInput(); // Ввод команды
        if (command == 0) { // Выход из программы
            break;
        }
        else if (command == 1) { // Вывод текущей матрицы
            printMatrix(A1, N, M);
        }
        else if (command == 2) { // Умножение матриц
            if (isHuman)
                cout << "Введите количество столбцов второй матрицы: ";
            int K = safeInput(); // Ввод количества столбцов второй матрицы
            double** A2 = new double* [M]; // Создание второй матрицы
            for (int i = 0; i < M; ++i) {
                A2[i] = new double[K];
            }
            inputMatrix(A2, M, K); // Ввод второй матрицы

            double** result; // Результат умножения
            int result_rows, result_cols;
            if (!multiplyMatrices(A1, N, M, A2, M, K, result, result_rows, result_cols)) { // Проверка возможности умножения
                cout << "Матрицы нельзя перемножить!" << endl;
            }
            else {
                clearMem(A1, N); // Очистка старой матрицы
                A1 = result; // Переназначение результата
                N = result_rows;
                M = result_cols;
            }
            clearMem(A2, M); // Очистка второй матрицы
        }
        else if (command == 3) { // Возведение в степень
            if (N != M) { // Проверка, что матрица квадратная
                if (isHuman)
                {
                    cout << "Матрицу нельзя возвести в степень (она не квадратная)!" << endl;
                }
                else
                    cout << "NO";

                continue;
            }
            if (isHuman)
                cout << "Введите степень: ";
            int exp = safeInput(); // Ввод степени
            double** result;
            if (!powerMatrix(A1, N, exp, result)) { // Проверка корректности возведения в степень
                if (isHuman)
                    cout << "Ошибка при возведении в степень!" << endl;
            }
            else {
                clearMem(A1, N); // Очистка старой матрицы
                A1 = result; // Переназначение результата
            }
        }
        else { // Некорректная команда
            if (isHuman)
                cout << "Некорректная команда. Попробуйте снова." << endl;
        }
    }

    clearMem(A1, N); // Очистка памяти перед выходом
    return 0; // Успешное завершение программы
}
