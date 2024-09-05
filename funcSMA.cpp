#include <iostream>
#include <fstream>
#include <chrono>
#include <queue>


//таймер выполнения
class Timer {
public:
    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        std::cout << duration.count() << " s\n";
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> start, end;
};

class SimpleMovingAverage {
    std::queue<double> Dataset;
    int period = 0;
    double sum = 0;

public:
    SimpleMovingAverage(int per) { period = per; }
    //функция добавления в очередь значений до размера окна усреднения и подсчёт суммы
    void addData(double num)
    {
        sum += num;
        Dataset.push(num);
        //поддерживание размера очереди, равной окну усреднения
        if (Dataset.size() > period) {
            sum -= Dataset.front();
            Dataset.pop();
        }
    }
    // возвращает среднее значение
    double getAverage() { return sum / period; }
};


int main() {

    int DATA_SIZE = 1000000;
    double MIN_DATA = 1.0;
    double MAX_DATA = 49.0;

    double* arrInput = new double[DATA_SIZE];
    double* arrOutput = new double[DATA_SIZE];

    //заполение входными данными
    for (int i = 0; i < DATA_SIZE; i++) {
        *(arrInput + i) = MIN_DATA + MAX_DATA * rand() / (double)RAND_MAX;
    }
    Timer timer;//начало работы таймера
    int interval = 4; // окно усреднения
    SimpleMovingAverage object (interval);

    //заполнение массива выходных данных
    for (int i = 0; i < DATA_SIZE; i++) {
        object.addData(*(arrInput + i));
        *(arrOutput + i) = object.getAverage();
    }
    /*
    * проверка работы в екселе
    std::ofstream outputFile;
    outputFile.open("ExcelTestinig.csv");
    for (int i = 0; i < 1000000; i++)
    {
        obj.addData(*(arrInput + i));
        outputFile << *(arrInput + i) << ";" << obj.getMean() << std::endl;
    }
    outputFile.close();
    */

    return 0;
}