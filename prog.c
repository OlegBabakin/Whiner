#include <stdio.h>
#include <stdlib.h>

#define SIZE 7

int main(void)
{
    int arr[SIZE] = {0};  // Основной массив
    int buf[SIZE] = {0};  // Буфер для наибольшей суммы
    int sum = 0, max_sum = 0;  // Учитываем отрицательные числа
    int first_seven_found = 0; // Флаг первой семёрки
    
    FILE *f = fopen("data.txt", "r");
    FILE *out = fopen("output.txt", "w");

    if (!f || !out)
    {
        fprintf(stderr, "ERROR\n");
        return 1;
    }

    int i = 0, a, found = 0;
    while (fscanf(f, "%d", &a) == 1)
    {
        // Проверяем, есть ли a уже в массиве
        int exists = 0;
        for (int j = 0; j < i; j++)
        {
            if (arr[j] == a)
            {
                exists = 1;
                // Сдвигаем элементы влево, удаляя повторяющиеся
                for (int k = j; k < i - 1; k++)
                {
                    arr[k] = arr[k + 1];
                }
                i--;
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

            // Сохраняем первую семёрку и обновляем максимальную сумму только если новая сумма больше
            if (!first_seven_found || sum > max_sum)
            {
                max_sum = sum;
                for (int j = 0; j < SIZE; j++)
                {
                    buf[j] = arr[j];
                }
                found = 1;
                first_seven_found = 1; // Устанавливаем флаг
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
        // Сортируем найденную семёрку по возрастанию
        for (int j = 0; j < SIZE - 1; j++)
        {
            for (int k = j + 1; k < SIZE; k++)
            {
                if (buf[j] > buf[k])
                {
                    int temp = buf[j];
                    buf[j] = buf[k];
                    buf[k] = temp;
                }
            }
        }

        // Записываем результат в файл
        for (int j = 0; j < SIZE; j++)
        {
            fprintf(out, "%d ", buf[j]);
        }
        fprintf(out, "\n");
    }
    else
    {
        fprintf(out, "NO\n");
    }

    fclose(out);
    return 0;
}
