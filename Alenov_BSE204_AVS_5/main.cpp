#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include "Client.cpp"
#include <random>

using std::cin;
using std::cout;
using std::string;
using std::thread;

// Константные границы времени симуляции и количества клиентов.
const int MAX_EXECUTION_TIME = 60001;
const int MAX_CLIENT_COUNT = 101;

// Имена для рандомной генерации клиентов.
string names[]{
        "Ivan", "Nikolay", "Petr", "Artyom", "Aleksandr", "Roman", "Yevgeny", "Maksim", "Denis", "Alexey",
        "Dmitry", "Danyl", "Sergay", "Konstantin", "Nikita", "Mikhail", "Boris", "Victor", "Gennady", "Vyacheslav",
        "Vladimir", "Andrey", "Anatoly", "Ilya", "Kirill", "Oleg", "Sofia", "Anastasia", "Victoria", "Xenia",
        "Arina", "Elizaveta", "Adelina", "Irina", "Yelena", "Polina", "Daria", "Natalia", "Svetlana", "Vera",
        "Nadezhda", "Galina", "Lyubov", "Aleksandra", "Maria", "Anna", "Angelina", "Marina", "Yekaterina", "Ludmila",
        "Stanley", "John", "Kaneki Ken", "Harrier Du Bouis", "Kim Kitsuragi", "Alice", "Mack", "Jules", "Chester",
        "Nix", "Trant", "Goracy", "Klaasje", "Lawrence", "Lena", "Sylvie", "Annette", "Gaston", "Gunter", "Neha",
        "Rene", "Ellis", "Tommy", "Angus", "Alain", "Leonard", "Eugene", "Evrart", "Glen", "Jean-Luc", "Ruby",
        "Theo", "Titus", "Cindy", "Ulixes", "Cuno", "Marielle", "Billie", "Steban", "Charles", "George",
        "Lillien", "Germaine", "Pete", "Karl", "Soona", "Tiago", "Iosef", "Dora", "Flacio", "Yvonne"
};
// Индекс имен.
size_t name_index;
// Массив клиентов.
Client *clients;
// Массив потоков, куда будут засунуты клиенты.
thread *threads;
// Количество клиентов.
int client_count;
// Парикмахер.
auto *hairdresser = new Hairdresser();

// Приветствует пользователя при старте программы.
void intro() {
    cout << " \n ###################################################\n"
            " ||              *%%                              ||\n"
            " ||             %%%,                              ||\n"
            " ||            %%%%                               ||\n"
            " ||            %%%/                               ||\n"
            " ||           %%%%                 Hairdresser    ||\n"
            " ||   (%%%    %%%#  .#%%%%%%%%%7                  ||\n"
            " || #%    %%%%%%%%%%%%%%%%%,        Simulator     ||\n"
            " || .%#  .%%  %%%                                 ||\n"
            " ||         %%%%%#                                ||\n"
            " ||        %/    %/                               ||\n"
            " ||         %%%%%#                                ||\n"
            " ###################################################\n\n"
            "Welcome to 'Hairdresser Simulator'!\n"
            "Here you will observe a simulation of a hairdresser's working day\n\n";
}

// Получение и парс времени из консоли в формате x:y:z.
long long getTimeViaConsole() {
    int hours, minutes, seconds;
    string first, second, third;
    // Крутим вайл до первого корректного ввода.
    while (true) {
        try {
            cout << "->";
            cin >> first >> second >> third;
            hours = stoi(first);
            minutes = stoi(second);
            seconds = stoi(third);
            if (hours > 19 || hours < 12 || minutes > 59 || minutes < 0 || seconds > 59 || seconds < 0) {
                cout << "Wrong input\n";
            } else {
                break;
            }
        }
        catch (...) {
            cout << "Cant parse input\n";
        }
    }
    // Перегоняем время из ЧЧ:ММ:СС в миллисекунды.
    return static_cast<long long>((1.0 * (hours - 12) * 3600 + minutes * 60 + seconds) / (8 * 3600) *
                                  (static_cast<long double>(execution_time)));
}

// Запуск потоков.
void simulate() {
    // Инициализируем переменную, которая указывает, когда именно была начата симуляция.
    start_work_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    // Создаем поток с парикмахером.
    thread hdthread = thread(&Hairdresser::simulateHairdresser, hairdresser);
    // Находим время конца симуляции.
    execution_time += duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    // Запускаем потоки с клиентами и отсоединяем их от мейна, чтобы работали параллельно.
    for (int i = 0; i < client_count; i++) {
        threads[i] = thread(&Client::simulateClient, &clients[i]);
        threads[i].detach();
    }
    // Присоединяем поток с парикмахером в мейн, чтобы программа закончила работать только под конец симуляции.
    hdthread.join();
}

// Рандомная генерация клиентов.
void generateClients(){
    cout << "Clients:\n";
    for (int i = 0; i < client_count; i++) {
        long long time = rand() % execution_time;
        cout << "Name = " << names[name_index] << ", Entry at = " << time << "\n";
        clients[i] = Client(names[name_index++], time, hairdresser);
    }
    cout << "\n";
}

// Получение всех необходимых правил через консоль.
void getRulesViaConsole() {
    string input;
    cout << "Enter number of clients [1 - 100]\n";
    // Крутим вайл до первого корректного ввода.
    while (true) {
        cout << "->";
        cin >> input;
        try {
            client_count = std::stoi(input);
            if (client_count > 0 && client_count < MAX_CLIENT_COUNT) {
                break;
            }
            cout << "Wrong input\n";
        } catch (...) {
            cout << "Cant parse to int\n";
        }
    }

    clients = new Client[client_count];
    threads = new thread[client_count];

    cout << "Enter execution time (milliseconds) [100 - 60000]\n";
    // Крутим вайл до первого корректного ввода.
    while (true) {
        cout << "->";
        cin >> input;
        try {
            execution_time = std::stoi(input);
            if (execution_time > 100 && execution_time < MAX_EXECUTION_TIME) {
                break;
            }
            cout << "Wrong input\n";
        } catch (...) {
            cout << "Cant parse to int\n";
        }
    }

    cout << "Do you want to input all client's data by hands? (y/n)\n";
    cin >> input;
    if (input == "y") {
        for (int i = 0; i < client_count; i++) {
            cout << "Enter client's number " << i + 1 << " name\n->";
            string name;
            cin >> name;

            cout << "Enter client's number " << i + 1
                 << " start time\n(numbers in format HH MM SS from 12:00:00 to 20:00:00)\n";
            long long start_time = getTimeViaConsole();

            clients[i] = Client(name, start_time, hairdresser);
            cout << "Client " << name << " will come to hairdresser at " << start_time << "\n\n";
        }
    } else{
        generateClients();
    }
}

// Получение всех необходимых правил через аргументы.
bool getRulesViaArgv(int argc, char *argv[]) {
    if (argc == 3) {
        try {
            client_count = std::stoi(argv[1]);
            execution_time = std::stoi(argv[2]);
            if (execution_time <= 100 || execution_time >= MAX_EXECUTION_TIME || client_count <= 0 ||
                client_count >= MAX_CLIENT_COUNT) {
                throw new std::exception;
            }
            clients = new Client[client_count];
            threads = new thread[client_count];
            cout << "Clients:\n";
            generateClients();
            return true;
        }
        catch (...) {
            cout << "Wrong argv arguments!\nEnter simulation rules in console\n\n";
            return false;
        }
    } else {
        if (argc != 1) {
            cout << "Incorrect argv length\nEnter simulation rules in console\n\n";
        }
        return false;
    }
}

// Точка входа в программу.
int main(int argc, char *argv[]) {
    // Показываем пользователю интро.
    intro();
    // Если приложение было запущено с некорректными аргументами,
    // то вводим правила симуляции через консоль.
    if (!getRulesViaArgv(argc, argv)) {
        getRulesViaConsole();
    }
    // Симулируем.
    simulate();
    // Чистим память.
    delete[] threads;
    delete[] clients;
    delete hairdresser;

    return 0;
}
