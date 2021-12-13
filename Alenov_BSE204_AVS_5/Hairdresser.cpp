#ifndef __Hairdresser__
#define __Hairdresser__

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <utility>
#include "Time.cpp"
#include <mutex>

using std::cin;
using std::cout;
using std::string;
using namespace std::chrono;
using std::this_thread::sleep_for;
using std::mutex;
using std::lock_guard;

class Hairdresser {
public:
    mutex hairdresserLock;

    // Дефолтный конструктор.
    Hairdresser()= default;

    // Метод для потока.
    void simulateHairdresser() {
        cout << "Hairdresser started his work day\n";
        auto current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        // Крутим вайл до конца рабочего дня.
        while (true) {
            current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
            if (current_time.count() > execution_time + 1000) {
                break;
            }
        }
        // Выводим инфу о смерти потока.
        cout << "Hairdresser ended work day\n";
    }

    // Метод с мьютексом для работы с клиентом.
    void workWithClient(const string& client_name) {
        // Блочим доступ другим потокам.
        lock_guard<mutex> lock(hairdresserLock);
        // Инициализируем рандом.
        srand(static_cast<unsigned int>(time(0)));
        // Находим, сколько будем стричь клиента.
        milliseconds sleep_time = milliseconds(rand() % ((execution_time-start_work_time)/20));
        sleep_for(sleep_time);
        cout << "[" << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - start_work_time - 1
             << " ms] " << "client " << client_name << " was being cut for " << sleep_time.count()
             << " milliseconds\n";
    }
};

#endif
