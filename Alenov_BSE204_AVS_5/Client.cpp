#ifndef __Clients__
#define __Clients__

#include <iostream>
#include <string>
#include <chrono>
#include <utility>
#include "Hairdresser.cpp"

using std::cin;
using std::cout;
using std::string;

class Client {
public:
    // Имя клиента.
    string name;
    // Время записи в миллисекундах.
    long long start_time;
    Hairdresser *hd;

    // Конструктор.
    Client(string new_name, long long new_start_time, Hairdresser *hd) {
        name = std::move(new_name);
        start_time = new_start_time;
        this->hd = hd;
    }

    // Конструктор без параметров для корректной инициализации динамического массива.
    Client(){
        name = "";
        start_time = 0;
        hd = nullptr;
    }

    // Метод для потока.
    void simulateClient() {
        auto current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        // Переопределяем время начала относительно старта потока.
        start_time =
                start_time + duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        // Крутим, пока рабочий день не закончится.
        while (true) {
            current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
            // Если уже не успевает подстричься.
            if (current_time.count() > execution_time) {
                cout << "["
                     << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - start_work_time -
                        1
                     << " ms] " << "client " << name << " was not cut today\n";
                break;
            }
            // Если пришло время стрижки.
            if (start_time < current_time.count()) {
                string output =
                        "[" + std::to_string(current_time.count() - start_work_time - 1) + " ms] Client " +
                        name +
                        " came to hairdresser\n";
                cout << output;
                hd->workWithClient(name);
                break;
            }
        }
        // Выводим инфу о смерти потока.
        current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        cout << "[" + std::to_string(current_time.count() - start_work_time - 1) + " ms] client "
             << name << " gone home\n";
    }
};

#endif