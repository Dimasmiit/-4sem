#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <errno.h>
#include <limits.h>

/*
* @brief Заменить минимальный по модулю положительный элемент массива нулем.
* @param array - массив, в котором нужно заменить элемент.
* @param size - размер массива.
* @return Возвращает новый массив с нулем.
*/
int* array_min(const int* const array, const size_t size);

/*
* @brief Создать копию исходного массива.
* @param array - массив, у которого нужно создать копию.
* @param size - размер массива.
* @return Возвращает копию исходного массива.
*/
int* copy_array(const int* array, const size_t size);

/*
* @brief Формирует новый массив без чисел, у которых первая и последняя цифра четные.
* @param array - исходный массив.
* @param size - размер исходного массива.
* @param size1 - размер нового массива без отрешенных чисел.
* @return Возвращает новый массив по условию.
*/
int* array_first_last_number(const int* array, const size_t size, size_t size1);

/*
* @brief Формирует новый массив A того же размера из исходного по правилам.
* @param array - исходный массив.
* @param A - новый массив.
* @param size - размер массива.
*/
void creat_array_a_from_d(const int* array, int* A, const size_t size);

/*
* @brief Проверяет количество элементов в массиве.
* @param size - количество элементов в массиве.
*/
void check_array_elements(const size_t size);

/**
* @brief Создать массив с заданным диапазоном при вводе с клавиатуры.
* @return Возвращает массив.
*/
void manual_fill(int* array, const size_t size);

/**
* @brief Создать массив с заданным диапазоном случайными числами.
* @return Возвращает массив.
*/
void random_fill(int* array, const size_t size);

/**
* @brief Проверяет введенный элемент на диск .
* @return Возвращает число, введенное пользователем.
*/
int input(void);

/*
* @brief Создать массив.
* @param size - переменная, отвечающая за размер массива.
* @return Возвращает созданный массив.
*/
int* creat_array(const size_t size);

/*
* @brief Проверяет адрес.
* @return Если адрес нулевой, программа завершается.
*/
void check_array(const int* array);

/*
* @brief Проверяет, что количество элементов в массиве строго больше нуля.
* @return Возвращает введенное число.
* @remarks Запрашивает программу, в случае отрицательного числа.
*/
size_t input_size(void);

/*
* @brief Учитывает количество элементов, у которых первая и последняя цифра четные.
* @param array - исходный массив
* @param size - размер исходного массива.
* @remarks Возвращает количество элементов.
*/
size_t even_number(const int* array, const size_t size);

/*
* @brief Учитывает размер нового массива.
* @param array - исходный массив
* @param size - размер исходного массива.
* @remarks Возвращает значение нового массива.
*/
size_t new_size(const int* array, const size_t size);

/*
* @brief Выводит массив.
* @param array - массив, который требуется вывести.
* @param size - длина массива array.
*/
void print_array(const int* array, const size_t size);

/**
* @brief Перечисляемый тип.
* @param manual - ручной ввод.
* @param random - случайный ввод.
*/
enum fill
{
    manual = 0,
    random_mode = 1  
};

/**
* @brief Вход в программу.
* @return 0 в случае правильного выхода.
*/
int main(void)
{
    setlocale(LC_ALL, "");

    srand((unsigned int)time(NULL));

    printf("Введите размер массива: ");
    size_t size = input_size();

    int* array = creat_array(size);

    printf("Как вы хотите заполнить массив?\n");
    printf("%d - Ручной ввод\n", manual);
    printf("%d - Заполнение массива случайными числами\n", random_mode);

    int choice = input();
    switch (choice)
    {
    case manual:
    {
        manual_fill(array, size);
        break;
    }
    case random_mode: // Было random
    {
        random_fill(array, size);
        break;
    }
    default:
    {
        perror("Введено некоректное значение\n");
        free(array);
        exit(EXIT_FAILURE);
    }
    }
    printf("Исходный массив: \n");
    print_array(array, size);

    printf("1) Массив, котором минимальный положительный элемент заменен нулем:\n");
    int* new_array = array_min(array, size);
    print_array(new_array, size);
    free(new_array);

    printf("2) Массив без тех элементов, у которых первая и последняя цифра четные: \n");
    size_t size1 = new_size(array, size);
    if (size1 > 0)
    {
        int* new_array2 = array_first_last_number(array, size, size1);
        print_array(new_array2, size1);
        free(new_array2);
    }
    else
    {
        printf("[]\n");
    }

    printf("3) Массив A, сформированный из исходного по правилам:\n");
    int* A = copy_array(array, size);
    creat_array_a_from_d(array, A, size);
    print_array(A, size);
    free(A);

    free(array);
    return 0;
}

int input(void)
{
    int value = 0;
    if (scanf("%d", &value) != 1)
    {
        errno = EIO;
        perror("Введено не число");
        exit(EXIT_FAILURE);
    }
    return value;
}

size_t input_size(void)
{
    int value = input();
    if (value <= 0)
    {
        errno = EIO;
        perror("Размер массива должен быть строго больше нуля");
        exit(EXIT_FAILURE);
    }
    return (size_t)value;
}

void check_array(const int* array)
{
    if (array == NULL)
    {
        errno = EIO;
        perror("Память не выделена");
        exit(EXIT_FAILURE);
    }
}

int* creat_array(const size_t size)
{
    int* array = (int*)malloc(sizeof(int) * size);
    check_array(array);
    return array;
}

void print_array(const int* array, const size_t size)
{
    check_array(array);
    if (size == 0)
    {
        printf("[]\n");
        return;
    }
    printf("[");
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d%s", array[i], (i < size - 1) ? ", " : "]\n");
    }
}

void check_array_elements(const size_t size)
{
    if (size < 12)
    {
        printf("Желательно иметь не менее 12 элементов.\n");
    }
}

void manual_fill(int* array, const size_t size)
{
    check_array(array);
    for (size_t i = 0; i < size; ++i)
    {
        printf("Введите %zu - й элемент:\n", i + 1);
        array[i] = input();
    }
}

void random_fill(int* const array, const size_t size)
{
    check_array(array);
    printf("Введите минимальное и максимальное значение:\n");
    printf("min=");
    int min = input();
    printf("max=");
    int max = input();
    if (min > max)
    {
        printf("Неправильный диапазон");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < size; ++i)
    {
        array[i] = rand() % (max - min + 1) + min;
    }
}

int* copy_array(const int* array, const size_t size)
{
    check_array(array);
    int* new_array = creat_array(size);
    for (size_t i = 0; i < size; ++i)
    {
        new_array[i] = array[i];
    }
    return new_array;
}

int* array_min(const int* const array, const size_t size)
{
    check_array(array);
    int* array2 = copy_array(array, size);
    int min_element = INT_MAX;
    int index = -1;
    for (size_t i = 0; i < size; ++i)
    {
        if ((array2[i] > 0) && (array2[i] < min_element))
        {
            min_element = array2[i];
            index = i;
        }
    }
    if (index != -1)
    {
        array2[index] = 0;
    }
    return array2;
}

size_t even_number(const int* array, const size_t size)
{
    check_array(array);
    size_t elements = 0;
    for (size_t i = 0; i < size; ++i)
    {
        int first_number = abs(array[i]);
        while (first_number >= 10)
        {
            first_number /= 10;
        }
        int last_number = abs(array[i]) % 10;
        if (first_number % 2 == 0 && last_number % 2 == 0)
        {
            elements++;
        }
    }
    return (size_t)elements;
}

size_t new_size(const int* array, const size_t size)
{
    check_array(array);
    return size - even_number(array, size);
}

int* array_first_last_number(const int* array, const size_t size, const size_t size1)
{
    check_array(array);
    int* new_array2 = creat_array(size1);
    size_t index = 0;

    for (size_t i = 0; i < size; ++i)
    {
        int first_number = abs(array[i]);
        while (first_number >= 10)
        {
            first_number /= 10;
        }
        int last_number = abs(array[i]) % 10;

        if (!(first_number % 2 == 0 && last_number % 2 == 0))
        {
            new_array2[index++] = array[i];
        }
    }
    return new_array2;
}

void creat_array_a_from_d(const int* array, int* A, const size_t size)
{
    check_array_elements(size);
    check_array(array);
    check_array(A);
    for (size_t i = 0; i < size; ++i)
    {
        if (i >= 2 && i <= 11)
        {
            A[i] = (-1) * (array[i] * array[i]);
        }
        else
        {
            A[i] = array[i] - 1;
        }
    }
}