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
    int i = 0; // Число элементов в массиве
    int a = 0; // Считываемое из файла число 
    int sum_flag = 0; // Флаг, если сумма новой семёрки больше суммы какой-либо из уже имеющихся
    int least_sum_index = 0; // Индекс с семёркой с наименьшей суммой из трёх семёрок
    int exists = 0; // Флаг чтобы понимать, есть ли в массиве считываемое число 



    FILE *f = fopen("data.dat", "r");
    FILE *out = fopen("data.res", "w");

    if (!f || !out)
    {
        fprintf(out, "ERROR\n");
        return -1;
    }

    while (fscanf(f, "%d", &a) == 1)
    {
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
                three_seven_found++; // Устанавливаем флаг
            }
            else if(sum_flag)
            {
                max_sum[least_sum_index] = sum;
                for (int j = 0; j < SIZE; j++)
                {
                    buf[j][least_sum_index] = arr[j];
                }
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

    if (three_seven_found)
    {
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