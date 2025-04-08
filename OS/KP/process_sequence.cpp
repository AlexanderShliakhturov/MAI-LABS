#include <iostream>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <set>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

// bool is_single_component(const boost::property_tree::ptree &config_tree)
// {
//     std::unordered_map<std::string, std::vector<std::string>> graph;
//     std::set<std::string> checked;

//     // Сборка графа задач
//     for (const auto &entry : config_tree)
//     {
//         // извлекаем подстроку ключа до первого вхождения "_dependencies"
//         std::string task = entry.first.substr(0, entry.first.find("_dependencies"));
//         graph[task]; // Создание мапы с ключами - нодами и пустыми списками предшественников
//     }

//     // Построение списка предшественников
//     for (const auto &entry : config_tree)
//     {
//         // entry - пара "ключ-значение", ключ - enty.first, значение - entry.second
//         const std::string &task = entry.first.substr(0, entry.first.find("_dependencies"));
//         std::string deps = entry.second.data();
//         std::istringstream deps_stream(deps);
//         std::string dep;
//         // цикл, в котором мы добавляем предшественников в мапу graph
//         while (std::getline(deps_stream, dep, ','))
//         {
//             if (!dep.empty())
//             {
//                 dep.erase(std::remove_if(dep.begin(), dep.end(), ::isspace), dep.end());
//                 graph[task].push_back(dep);
//                 graph[dep];
//             }
//         }
//     }

//     int connected_components = 0;
//     for (const auto &entry : graph)
//     {
//         const std::string &task = entry.first;
//         if (checked.count(task) == 0)
//         {
//             std::queue<std::string> queue;

//             queue.push(task);
//             checked.insert(task);

//             while (!queue.empty())
//             {
//                 std::string current_task = queue.front();
//                 queue.pop();

//                 for (const auto &successor : graph[current_task])
//                 {
//                     if (checked.count(successor) == 0)
//                     {
//                         queue.push(successor);
//                         checked.insert(successor);
//                     }
//                 }
//             }
//             connected_components++;
//         }
//     }

//     return connected_components == 1;
// }

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <config_filename>" << std::endl;
        return 1;
    }

    std::string config_filename = argv[1];
    boost::property_tree::ptree workflow_config;

    try
    {
        boost::property_tree::ini_parser::read_ini(config_filename, workflow_config);
    }
    catch (const boost::property_tree::ini_parser_error &e)
    {
        std::cerr << "Failed to parse config: " << e.what() << std::endl;
        return 1;
    }

// НАЧАЛО ФУНКЦИИ ТУТ ДОЛЖНО БЫТЬ 
    std::unordered_map<std::string, std::vector<std::string>> dependencies_map;

    for (const auto &job : workflow_config.get_child("jobs"))
    {
        std::string jobName = job.first;
        if (jobName.find("_dependencies") != std::string::npos)
        {
            jobName = jobName.substr(0, jobName.find("_dependencies"));
        }
        std::string dependencies_str = job.second.data();
        std::vector<std::string> dependencies;
        std::istringstream iss(dependencies_str);
        std::string dependency;
        while (std::getline(iss, dependency, ','))
        {
            dependency.erase(std::remove_if(dependency.begin(), dependency.end(), ::isspace), dependency.end());
            if (!dependency.empty())
            {
                dependencies.push_back(dependency);
            }
        }
        dependencies_map[jobName] = dependencies;
    }

    std::unordered_set<std::string> visited;
    std::queue<std::string> queue;

    if (dependencies_map.empty()) // Проверяем, что граф не пустой
        return false;

    // Начинаем обход с первой вершины графа
    queue.push(dependencies_map.begin()->first);

    // Пока очередь не пуста
    while (!queue.empty())
    {
        // Извлекаем вершину из очереди
        std::string current = queue.front();
        queue.pop();

        // Если вершина уже посещена, пропускаем её
        if (visited.count(current) > 0)
            continue;

        // Помечаем текущую вершину как посещенную
        visited.insert(current);

        // Добавляем всех соседей текущей вершины в очередь
        const auto &neighbors = dependencies_map.at(current);
        for (const auto &neighbor : neighbors)
        {
            if (visited.count(neighbor) == 0)
                queue.push(neighbor);
        }
    }

    // Если все вершины были посещены, граф односвязный
    bool answer = visited.size() == dependencies_map.size();

    for (const auto &pair : dependencies_map)
    {
        std::cout << "Node: " << pair.first << " Dependencies: ";
        for (const auto &dep : pair.second)
        {
            std::cout << dep << " ";
        }
        std::cout << std::endl;
    }
    
    if (answer == 1)
    {
        std::cout << "Graph is fully connected" << std::endl;
    }
    else
    {
        std::cout << "Graph IS NOT fully connected" << std::endl;
    }
}
