# receiver::datetime
## What?
Класс для работы с датой и временем в соответствии со стандартом Internet. Класс предназначен для работы с Windows и работает с ее API. Найти их можно по следующему пути: `Computer\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Time Zones`. Класс не работает с миллисекундными смещениями зон. Метод `date_time::current` принимает время UTC без указания часового пояса, зону можно задать самостоятельно с помощью `date_time::set_timezone`.

## Why?
Вызов `std::chrono::current_zone()` приводит к аварийному завершению работы на большинстве сборок Windows из-за наличия в системе устаревшего файла `icu.dll`. Microsoft не собирается обновлять его в `C++ Redistributable`, поэтому появилась эта библиотека. Данная библиотека зависит от реализации Windows. Она не использует подключение к Интернету для получения часовых поясов, так как получает их непосредственно из системы. И поддерживается во всех сборках Windows. Использует только 1 импорт - advapi32.dll

## How to use?
Очень короткий пример всей функциональности: парсинг и форматирование в соответствии со стандартом ISO_8601, а также указание начального часового пояса
```cpp
using namespace receiver;
std::cout << date_time{"2023-09-07T00:00:00Z", date_format::ISO_8601,
                    time_zone{"Russia TZ 2 Standard Time"}}.format(date_format::ISO_8601) << std::endl;
// Output: 2023-09-07T00:00:00+03:00
```
Добавлять/вычитать секунды/минуты/часы/дни можно через std::chrono:
```cpp
using namespace receiver;
using namespace std::chrono_literals;
std::cout << (date_time{"2023-09-07T00:00:00Z"} + 15min)
                 .format(date_format::ISO_8601)
          << std::endl;
// Output: 2023-09-07T00:15:00+00:00
```
Получить текущее время в текущем часовом поясе:
```cpp
using namespace receiver;
std::cout << date_time::current()
                 .set_time_zone(time_zone::current())
                 .format(date_format::ISO_8601)
          << std::endl;
// Output: 2023-09-12T12:01:17+04:00
```

Все функции документированы в коде, вы можете разобраться с ними самостоятельно, заглянув в файл .h.
