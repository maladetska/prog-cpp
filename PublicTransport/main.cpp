#include "pugixml/src/pugixml.cpp"
#include "pugixml/src/pugixml.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

// ОСТАНОВКИ
class Transport_stations {

public:
    // конструктор
    explicit Transport_stations(int ind = 0, std::string type_of_vehicle = "", std::string name_stopping = "", std::string the_official_name = "", std::vector<std::string> location = {},
                                std::vector<std::string> routes = {}, std::pair<double, double> coordinates = {0, 0}) : _ind{ind},
                                                                                                                        _coordinates{std::move(coordinates)},
                                                                                                                        _location{std::move(location)},
                                                                                                                        _name_stopping{std::move(std::move(name_stopping))},
                                                                                                                        _routes{std::move(routes)},
                                                                                                                        _the_official_name{std::move(the_official_name)},
                                                                                                                        _type_of_vehicle{std::move(type_of_vehicle)} {}

    // индекс
    [[maybe_unused]] [[nodiscard]] int get_ind() const {
        return _ind;
    }

    // вид транспортного средства
    [[nodiscard]] std::string get_type_of_vehicle() const {
        return _type_of_vehicle;
    }

    // наименование остановки
    [[maybe_unused]] [[nodiscard]] std::string get_name_stopping() const {
        return _name_stopping;
    }

    // официальное наименование
    [[maybe_unused]] [[nodiscard]] std::string get_the_official_name() const {
        return _the_official_name;
    }

    // расположение
    [[maybe_unused]] [[nodiscard]] std::vector<std::string> get_location() const {
        return _location;
    }

    // маршруты
    [[maybe_unused]] [[nodiscard]] std::vector<std::string> get_routes() const {
        return _routes;
    }

    // координаты
    [[nodiscard]] double get_coordinates_x() const {
        return _coordinates.first;
    }
    [[nodiscard]] double get_coordinates_y() const {
        return _coordinates.second;
    }

    // строка машрута
    [[nodiscard]] std::string route_i(int i) const {
        return _routes[i];
    }

    // размер маршрута
    [[nodiscard]] int route_size() const {
        return _routes.size();
    }

private:
    int _ind;

    std::string _type_of_vehicle;
    std::string _name_stopping;
    std::string _the_official_name;

    std::vector<std::string> _location;
    std::vector<std::string> _routes;

    std::pair<double, double> _coordinates;
};

// МАРШРУТЫ ДЛЯ РАЗНОГО ТРАНСПОРТА
class Routes {
public:
    std::string route;

    std::vector<Transport_stations> Trolleybus;
    std::vector<Transport_stations> Bus;
    std::vector<Transport_stations> Tram;
};

// ФУНКЦИЯ ДЛЯ ПОДСЧЁТА РАСТОЯНИЙ МЕЖДУ ДВУМЯ КООРДИНАТАМИ
double distance_between_coordinates(const Transport_stations &first, const Transport_stations &second) {

    // перевод градусов в радианны

    // широта
    double latitude1 = first.get_coordinates_x() * M_PI / 180;
    double latitude2 = second.get_coordinates_x() * M_PI / 180;

    // долгота
    double longitude1 = first.get_coordinates_y() * M_PI / 180;
    double longitude2 = second.get_coordinates_y() * M_PI / 180;

    double delta_latitude = latitude2 - latitude1;
    double delta_longitude = longitude2 - longitude1;

    double res = 2 * asin(sqrt(pow(sin(delta_latitude / 2), 2) + cos(latitude1) * cos(latitude2) * pow(sin(delta_longitude / 2), 2))) * 6371;

    return res;
}

// ФУНКЦИЯ ДЛЯ СЧИТЫВАНИЯ ДАННЫХ БЕЗ ЗАПЯТОЙ
void separator(const std::string &str, std::string &str1, std::string &str2) {
    // знак, по которому разделяется строка (в данном случае это запятая)
    std::string separator = ",";

    // начало и конец строки
    int start = 0;
    int finish = str.find(separator);

    while (finish != -1) {
        // записываем первую чать строки (substr - подстрока)
        str1 = str.substr(start, finish - start);

        // перемещаем указатели старт и финиш на след. пункт
        start = finish + separator.length();
        finish = str.find(separator, start);
    }

    // запись второй части строки (substr - подстрока)
    str2 = str.substr(start, finish);
}

// ФУНКЦИЯ ДЛЯ ИЗМЕНЕНИЯ СТРОКИ
std::string correction_location(std::string &str) {

    // errors хранит всё, что можно обрезать
    std::vector<std::string> errors{"ул.", "УЛ.", " ш.", " Ш.", " шоссе", " ШОССЕ", " пер.", " ПЕР.", " переулок",
                                    " ПЕРЕУЛОК", " улица", "улица", " УЛИЦА", " бул.", " БУЛ.", " бульвар", " БУЛЬВАР", " пр.", " ПР.", " проспект", " ПРОСПЕКТ"};

    // удаляем все лишние слова, оставляем лишь наименования локаций
    for (auto &i: errors)
        if (str.find(i) != -1) {
            int first = str.find(i);
            int second = first + i.size();
            str.erase(first, second);
        }

    // удаляем лишние пробелы
    if (str[str.size() - 1] == ' ')
        str.erase(str.end() - 1);

    return str;
}

// ПАРСИНГ (- ЭТО ПРОЦЕСС АВТОМАТИЧЕСКОГО СБОРА ДАННЫХ И ИХ СТРУКТУРИРОВАНИЯ)
void parsing_file(std::vector<Transport_stations> &stop, std::map<std::string, Routes> &map_routes, std::set<std::string> &name_routes, std::map<std::string, int> &positions) {

    // используем pugi
    pugi::xml_document doc;                    // создаем обьект
    doc.load_file("data.xml");                 // используем файл
    pugi::xml_node data = doc.child("dataset");// находим первого ребёнка

    // идём по детям dataset считывая нужную информацию
    for (pugi::xml_node i = data.child("transport_station"); i; i = i.next_sibling("transport_station")) {

        // координаты
        std::string str1, str2;
        // разделяем строку на две подстроки
        separator(i.child_value("coordinates"), str1, str2);

        // преобразуем строку в float
        float coordinate1 = stof(str1);
        float coordinate2 = stof(str2);

        // получим координату
        std::pair<double, double> coordinates;
        coordinates.first = coordinate1;
        coordinates.second = coordinate2;

        // маршруты
        std::string str_routes = i.child_value("routes"), segment;// segment - пустая строка
        std::vector<std::string> routes;
        // поток строк
        std::stringstream temp_routes(str_routes);

        // заполняем вектор routes
        if (count(str_routes.begin(), str_routes.end(), ','))
            while (getline(temp_routes, segment, ','))
                routes.push_back(segment);
        else
            while (getline(temp_routes, segment, '.'))
                routes.push_back(segment);

        // расположения
        std::string str_location = i.child_value("location");
        std::vector<std::string> locations;
        // поток строк
        std::stringstream temp_locations(str_location);

        // корректируем и разделяем локации для дальнейшей работы
        if (count(str_location.begin(), str_location.end(), ',') && !str_location.empty())
            while (getline(temp_locations, segment, ',')) {
                if (segment[0] == ' ')
                    segment.erase(segment.begin());

                locations.push_back(correction_location(segment));
                positions[correction_location(segment)] += 1;
            }
        else if (!str_location.empty()) {
            locations.push_back(correction_location(str_location));
            positions[correction_location(str_location)] += 1;
        }

        // кладём данные в экземпляр класса
        int ind = std::stoi(i.child_value("number"));// преобразование строки в число
        std::string type_of_vehicle = i.child_value("type_of_vehicle");
        std::string name_stopping = i.child_value("name_stopping");
        std::string the_official_name = i.child_value("the_official_name");

        Transport_stations Transport_station(ind, type_of_vehicle, name_stopping, the_official_name, locations, routes, coordinates);
        stop.emplace_back(Transport_station);// добавляем остановку

        if (strcmp(i.child_value("type_of_vehicle"), "Трамвай") == false)
            for (auto &j: routes) {
                map_routes[j].route = j;
                map_routes[j].Tram.emplace_back(Transport_stations(ind, type_of_vehicle, name_stopping, the_official_name, locations, routes, coordinates));
                name_routes.insert(j);
            }
        if (strcmp(i.child_value("type_of_vehicle"), "Троллейбус") == false)
            for (auto &j: routes) {
                map_routes[j].route = j;
                map_routes[j].Trolleybus.emplace_back(Transport_stations(ind, type_of_vehicle, name_stopping, the_official_name, locations, routes, coordinates));
                name_routes.insert(j);
            }
        if (strcmp(i.child_value("type_of_vehicle"), "Автобус") == false)
            for (auto &j: routes) {
                map_routes[j].route = j;
                map_routes[j].Bus.emplace_back(Transport_stations(ind, type_of_vehicle, name_stopping, the_official_name, locations, routes, coordinates));
                name_routes.insert(j);
            }
    }
}

int main() {
    std::vector<Transport_stations> TransportStation;// остановки
    std::map<std::string, Routes> routes;            // маршруты
    std::set<std::string> name_routes;               // наименования маршрутов
    std::map<std::string, int> locations;            // расположение

    // парсинг
    parsing_file(TransportStation, routes, name_routes, locations);

    // создаём хеш-таблицу, которая будет хранить маршруты и кол-во остановок
    std::map<std::string, int> tram_routes;
    std::map<std::string, int> bus_routes;
    std::map<std::string, int> trolleybus_routes;

    // заполняем кол-во станций для каждого вида транспорта
    for (const auto &i: TransportStation) {
        if (i.get_type_of_vehicle() == "Трамвай")
            for (int j = 0; j < i.route_size(); j++)
                tram_routes[i.route_i(j)] += 1;

        else if (i.get_type_of_vehicle() == "Автобус")
            for (int j = 0; j < i.route_size(); j++)
                bus_routes[i.route_i(j)] += 1;

        else if (i.get_type_of_vehicle() == "Троллейбус")
            for (int j = 0; j < i.route_size(); j++)
                trolleybus_routes[i.route_i(j)] += 1;
    }


    /* Пункт 1. Маршрут с наибольшим количеством остановок по отдельными видам транспорта. */

    // номера маршрутов
    std::string max_tram_routes;
    std::string max_bus_routes;
    std::string max_trolleybus_routes;

    // кол-во остановок
    int k_tram_routes = 0;
    int k_bus_routes = 0;
    int k_trolleybus_routes = 0;

    // поиск маршрутов с наиболшим кол-вом остановок по отдельным видам транспорта
    for (const auto &i: tram_routes)
        if (i.second > k_tram_routes) {
            k_tram_routes = i.second;
            max_tram_routes = i.first;
        }
    for (const auto &i: trolleybus_routes)
        if (i.second > k_trolleybus_routes) {
            k_trolleybus_routes = i.second;
            max_trolleybus_routes = i.first;
        }
    for (const auto &i: bus_routes)
        if (i.second > k_bus_routes) {
            k_bus_routes = i.second;
            max_bus_routes = i.first;
        }

    // вывод
    std::cout << "Пункт 1. Маршруты с наибольшим количеством остановок по отдельными видам транспорта:" << std::endl;
    std::cout << "- трамвай №" << max_tram_routes << " (" << k_tram_routes << " остановок);" << std::endl;
    std::cout << "- тролейбус №" << max_trolleybus_routes << " (" << k_trolleybus_routes << " остановок);" << std::endl;
    std::cout << "- автобус №" << max_bus_routes << " (" << k_bus_routes << " остановок)." << std::endl;
    std::cout << std::endl;


    /* Пункт 2. Наиболее длинный маршрут (основывая на координатах) по отдельным видам транспорта. */

    // номера маршрутов
    max_tram_routes = "";
    max_trolleybus_routes = "";
    max_bus_routes = "";

    // кол-во остановок
    k_tram_routes = 0;
    k_trolleybus_routes = 0;
    k_bus_routes = 0;

    // размеры маршрутов
    std::map<std::string, double> size_tram_routes;
    std::map<std::string, double> size_trolleybus_routes;
    std::map<std::string, double> size_bus_routes;

    // поиск маршрутов с наиболшим кол-вом остановок по отдельным видам транспорта
    for (const auto &i: name_routes) {
        if (routes[i].Tram.size() > 1)
            for (int j = 0; j < routes[i].Tram.size() - 1; j++)
                size_tram_routes[routes[i].route] += distance_between_coordinates(routes[i].Tram[j], routes[i].Tram[j + 1]);
        if (routes[i].Trolleybus.size() > 1)
            for (int j = 0; j < routes[i].Trolleybus.size() - 1; j++)
                size_trolleybus_routes[routes[i].route] += distance_between_coordinates(routes[i].Trolleybus[j], routes[i].Trolleybus[j + 1]);
        if (routes[i].Bus.size() > 1)
            for (int j = 0; j < routes[i].Bus.size() - 1; j++)
                size_bus_routes[routes[i].route] += distance_between_coordinates(routes[i].Bus[j], routes[i].Bus[j + 1]);
    }

    // поиск самых длинных маршрутов по отдельным видам транспорта
    for (const auto &i: size_tram_routes)
        if (i.second > k_tram_routes) {
            k_tram_routes = i.second;
            max_tram_routes = i.first;
        }
    for (const auto &i: size_trolleybus_routes)
        if (i.second > k_trolleybus_routes) {
            k_trolleybus_routes = i.second;
            max_trolleybus_routes = i.first;
        }
    for (const auto &i: size_bus_routes)
        if (i.second > k_bus_routes) {
            k_bus_routes = i.second;
            max_bus_routes = i.first;
        }

    // вывод
    std::cout << "Пункт 2. Самые длинные маршруты (основываясь на координатах) по отдельным видам транспорта." << std::endl;
    std::cout << "Наидлинейший маршрут трамвая: " << max_tram_routes << std::endl;
    std::cout << "Наидлинейший маршрут троллейбуса: " << max_trolleybus_routes << std::endl;
    std::cout << "Наидлинейший маршрут автобуса: " << max_bus_routes << std::endl;
    std::cout << std::endl;


    /* Пункт 3. Улица с наибольшим числом остановок. */

    // максимальное кол-во остановок на улице
    int k_max_street = 0;

    // название искомой улицы
    std::string max_street;

    for (const auto &i: locations)
        if (i.second > k_max_street) {
            k_max_street = i.second;
            max_street = i.first;
        }

    // вывод
    std::cout << "Пункт 3. Улица с наибольшим числом остановок." << std::endl;
    std::cout << "Улица "
              << "\"" << max_street << "\""
              << " имеет наибольшее количество остановок, целых  " << k_max_street << " штук." << std::endl;

    return 0;
}
