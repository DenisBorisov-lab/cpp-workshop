#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>

// Структура входных данных
struct MapStruct {
    unsigned long long key;
    char value[65];
};

// Сортировка элементов кармана (алгоритм сортировки вставкой)
void insertionSort(std::vector<MapStruct> &bucket) {
    const size_t n = bucket.size();
    for (size_t i = 1; i < n; ++i) {
        MapStruct key = bucket[i];
        int j = i - 1;

        while (j >= 0 && bucket[j].key > key.key) {
            bucket[j + 1] = bucket[j];
            --j;
        }

        bucket[j + 1] = key;
    }
}

// Встраиваемая функция для определения индекса кармана
inline int getBucketIndex(unsigned long long key, int bucketCount) {
    return static_cast<int>((static_cast<double>(key) * (bucketCount - 1)) / 0xffffffffffffffffull);
}

//Алгоритм карманной сортировки
void bucketSort(std::vector<MapStruct> &pairs) {
    if (pairs.size() <= 1) return;

    const int bucketCount = 512;
    std::vector<std::vector<MapStruct>> buckets(bucketCount);

    const size_t avgBucketSize = pairs.size() / bucketCount + 1;
    for (auto &bucket: buckets) {
        bucket.reserve(avgBucketSize);
    }

    for (auto &pair: pairs) {
        int bucketIndex = getBucketIndex(pair.key, bucketCount);
        buckets[bucketIndex].push_back(std::move(pair));
    }

    pairs.clear();
    pairs.reserve(pairs.capacity());

    for (auto &bucket: buckets) {
        if (bucket.size() > 1) {
            insertionSort(bucket);
        }

        pairs.insert(pairs.end(),
                     std::make_move_iterator(bucket.begin()),
                     std::make_move_iterator(bucket.end()));
        std::vector<MapStruct>().swap(bucket);
    }
}


// Генератор данных для тестов
std::vector<MapStruct> generateRandomData(size_t size) {
    std::vector<MapStruct> data;
    data.reserve(size);

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long> dist(0, 0xffffffffffffffffull);

    for (size_t i = 0; i < size; ++i) {
        MapStruct item;
        item.key = dist(gen);
        sprintf(item.value, "val-%llu", item.key % 100000);
        data.push_back(item);
    }

    return data;
}

// Функция для измерения времени выполнения
template <typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<MapStruct> pairs;

    unsigned long long key;
    char valueBuffer[65];

    while (std::cin >> key) {
        char c;
        while ((c = std::cin.get()) == ' ' || c == '\t');

        std::cin.unget();
        std::cin.getline(valueBuffer, 65);

        pairs.push_back({key, {0}});
        std::strncpy(pairs.back().value, valueBuffer, 64);
        pairs.back().value[64] = '\0';
    }

    bucketSort(pairs);

    for (const auto &pair: pairs) {
        std::cout << pair.key << '\t' << pair.value << '\n';
    }

    return 0;
}


//int main() {
//    std::vector<size_t> sizes = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
//
//    std::ofstream resultFile("sort_benchmark.csv");
//    resultFile << "Data Size,Bucket Sort (ms),std::sort (ms)\n";
//
//    for (size_t size : sizes) {
//        std::cout << "Testing with data size: " << size << std::endl;
//
//        auto originalData = generateRandomData(size);
//
//        auto bucketSortData = originalData;
//        auto stdSortData = originalData;
//
//        double bucketSortTime = measureTime([&]() {
//            bucketSort(bucketSortData);
//        });
//
//        double stdSortTime = measureTime([&]() {
//            std::sort(stdSortData.begin(), stdSortData.end(),
//                      [](const MapStruct& a, const MapStruct& b) {
//                          return a.key < b.key;
//                      });
//        });
//
//        bool correctResult = true;
//        if (bucketSortData.size() != stdSortData.size()) {
//            correctResult = false;
//        } else {
//            for (size_t i = 0; i < bucketSortData.size(); ++i) {
//                if (bucketSortData[i].key != stdSortData[i].key) {
//                    correctResult = false;
//                    break;
//                }
//            }
//        }
//
//        std::cout << "Bucket Sort: " << bucketSortTime << " ms, "
//                  << "std::sort: " << stdSortTime << " ms, "
//                  << "Correct result: " << (correctResult ? "Yes" : "No") << std::endl;
//
//        resultFile << size << "," << bucketSortTime << "," << stdSortTime << "\n";
//    }
//
//    resultFile.close();
//    std::cout << "Results saved to sort_benchmark.csv" << std::endl;
//
//    return 0;
//}
