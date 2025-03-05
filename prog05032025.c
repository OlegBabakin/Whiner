/*

11. В файле data.dat задана последовательность целых чисел по одному целому числу в строке (допускаются пустые строки, в которых целые числа не заданы). Ограничения на длину последовательности нет.
За один проход последовательности определить, встречаются ли в полученной последовательности семь подряд идущих (т.е. с подряд идущими индексами) различных чисел.
Допускается использование массивов фиксированной размерности. Отводить память динамически не разрешается.
Результат работы программы вывести в файл data.res в следующем виде: в случае невозможности ввода данных из файла вывести в файл слово ERROR; в случае положительного ответа на вопрос задачи вывести в файл через пробел три семерки найденных чисел с максимальной суммой (среди всех семерок, удовлетворяющих условию задачи), отсортированных по возрастанию; если количество найденных семерок меньше трех, то вывести в файл только найденные отсортированные семерки; в случае отрицательного ответа записать в выходной файл слово NO.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 7


int main(void)
{
    int arr[SIZE] = {0};  // Основной массив
    int buf[SIZE][3] = {0};  // Буфер для наибольшей суммы
    int sum = 0, max_sum[3] = {0};  
    int seven_counter = 0; // Счётчик для семёрок
    int three_seven_found = 0; // Флаг первых трёх семёрок
    int i = 0, a = 0;
    int found = 0;



    FILE *f = fopen("data.dat", "r");
    FILE *out = fopen("data.res", "w");

    if (!f || !out)
    {
        fprintf(out, "ERROR\n");
        return -1;
    }

    while (fscanf(f, "%d", &a) == 1)
    {
        int exists = 0;
        // Проверяем, есть ли a уже в массиве
        for (int j = 0; j < i; j++)
        {
            if (arr[j] == a)
            {
                // Сдвигаем элементы влево, удаляя повторяющиеся
                for (int k = j; k < i; k++)
                {
                    arr[k-j] = arr[k + 1];
                }
                i-=(j+1);
                break;
            }
        }

        // Добавляем новый элемент, если он уникален
        if (!exists && i < SIZE)
        {
            arr[i++] = a;
        }

        // Если массив заполнился, считаем сумму
        if (i == SIZE)
        {
            sum = 0;
            for (int j = 0; j < SIZE; j++)
            {
                sum += arr[j];
            }
            int sum_flag = 0;
            int least_sum_index = 0;
            for(int j = 0; j < three_seven_found; j++)
            {
                if(sum > max_sum[j])
                {
                    sum_flag = 1;
                    least_sum_index = j;
                }
            }
            // Сохраняем первые три семёрки и обновляем максимальную сумму только если новая сумма больше, чем для любой из семёрок
            if(three_seven_found < 3)
            {
                // здесь надо переделать чуток
                max_sum[three_seven_found] = sum;
                for (int j = 0; j < SIZE; j++)
                {
                    buf[j][three_seven_found] = arr[j];
                }
                found = 1;
                three_seven_found++; // Устанавливаем флаг
            }
            else if(sum_flag)
            {
                max_sum[least_sum_index] = sum;
                for (int j = 0; j < SIZE; j++)
                {
                    buf[j][least_sum_index] = arr[j];
                }
                found = 1;
                sum_flag = 0;
                least_sum_index = 0;
            }

            // Сдвигаем массив влево, освобождая место
            for (int j = 0; j < SIZE - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            i--;
        }
    }
    fclose(f);

    if (found)
    {
        found = 0;
        // Сортируем все найденные семёрки по возрастанию
        for(int m = 0; m < three_seven_found; m++)
        {
            for(int j = 0; j < SIZE - 1; j++)
            {
                for (int k = j + 1; k < SIZE; k++)
                {
                    if (buf[j][m] > buf[k][m])
                    {
                        int temp = buf[j][m];
                        buf[j][m] = buf[k][m];
                        buf[k][m] = temp;
                    }
                }
            }
        }

        // Записываем результат в файл
        for(int m = 0; m < three_seven_found; m++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                fprintf(out, "%d ", buf[j][m]);
            }
            fprintf(out, "  ");
        }
    }
    else
    {
        fprintf(out, "NO");
    }
    fclose(f);
    fclose(out);

}