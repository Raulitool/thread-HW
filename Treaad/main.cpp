#include <iostream>
#include <vector>
#include <thread>
#include <numeric>

// ������� ��� �������� ����� ��������� � ����������
int calculateSum(const std::vector<int>& array, int start, int end) {
    int sum = 0;
    for (int i = start; i < end; ++i) {
        sum += array[i];
    }
    return sum;
}

int main() {
    const int N = 20; // ������ �������
    const int M = 4;  // ���������� ������

    std::vector<int> numbers = { 5, 3, 2, 4, 8, 9, 6, 1, 1, 7, 9, 3, 8, 2, 6, 3, 5, 5, 4, 7 };

    std::vector<std::thread> threads;
    std::vector<int> partialSums(M, 0);

    // �������� ������� ��� �������� ����� � ������ ����� �������
    for (int i = 0; i < M; ++i) {
        int start = i * (N / M);
        int end = (i == M - 1) ? N : (i + 1) * (N / M);
        threads.emplace_back([&, start, end, i]() {
            partialSums[i] = calculateSum(numbers, start, end);
            });
    }

    // �������� ���������� ���������� ���� �������
    for (auto& thread : threads) {
        thread.join();
    }

    // ���������� ����� �����
    int totalSum = std::accumulate(partialSums.begin(), partialSums.end(), 0);

    std::cout << "Total sum: " << totalSum << std::endl;

    return 0;
}
