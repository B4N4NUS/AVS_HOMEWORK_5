# AVS_HOMEWORK_5
* Пятое дз по архитектуре вычислительных систем 
* Выполнил Аленов Михаил БПИ204 
* Вариант 1 (Задача о парикмахере)

# Основные характеристики программы:
* Число интерфессных модулей = 0
* Число модулей реализации = 4
* Общий вес исполняемых файлов = 14.0 кб

Наименование | Функционал
-----------------|--------------------------------------------------------
main.cpp | точка входа в программу. Считывает данные для симуляции, затем создает и оперирует потоки.
client.cpp | описывает класс посетителя.
Hairdresser.cpp | описывает класс парикмахера.
Time.cpp | содержит глобальные переменные для корректной работы вывода времени в консоль.


# Особенности реализации:
* Время симуляции всегда находится в границах от 100 до 60000 миллисекунд т.е от 0.1 секунд до 1 минуты
* Количество посетителей всегда находится в границах от 1 до 100
* При ручной задаче времени записи для посетителя требуется вводить время в формате ЧЧ:ММ:СС, что потом переведется в миллисекунды относительно времени симуляции по формуле (ЧЧ * 3600 + ММ * 60 + СС) / (8 * 3600) * (время симуляции) 
* Парихмахер работает с 12:00:00 до 20:00:00, поэтому если кого-то из посетителей не успели подстричь до этого времени, то он уйдет без новой стрижки
* К каждому действию посетителя в консоли выводится время этого действия в миллисекундах. Оно является лишь приблизительным и нужно только, чтобы показать кто и когда что делал

# В двух словах об алгоритме работы программы
После ввода корректных правил симуляции запускаются потоки парихмахера и посетителей.
Посетители делают .detach для получения независимости в исполнении, а парихмахер делает .join к мейну, чтобы не завершить симуляцию раньше времени.
Далее, когда посетитель решает, что время его записи подошло, начинает смотреть в сторону парихмахера. Если тот занят, то посетитель терпеливо ждет. Если же парихмахер свободен, то он приказывает ему стричь себя, после чего завершает свой поток. Если же посетитель не успевает подстричься к концу рабочего дня, то он просто уходит из парикмахерской.

# Как запускать?
В аргументах нужно указать 2 числа: 
* Первое - количество посетителей
* Второе - время выполнения симуляции

# Пример аргументов при запуске:
./AVS_5 15 3000
* 15 - число посетителей.
* 3000 - время симуляции т.е 3 секунды.
* Далее к каждому из 15 посетителей привяжется уникальное имя в время записи (от 0 до 3000 мс), после чего начнется симуляция

# При отсутствии/некорректных аргументах при запуске программа попросит ввести правила симуляции в консоль:
* Количество посетителей
* Время выполнения
* Желает ли пользователь вбить имена посетителей и время их прихода ручками или сгенерить автоматически.

# Программу тестировал на
* Ubuntu 20.04.3: Intel Core I7 GTX 960m 16GB RAM 

