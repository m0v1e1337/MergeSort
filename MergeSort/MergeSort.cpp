#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

class MergeSort {
public:
    void Sort(std::vector<int>& arr) {
        if (arr.size() <= 1)
            return;

        int mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());

        std::thread leftThread(&MergeSort::Sort, this, std::ref(left));
        Sort(right);

        leftThread.join();

        Merge(left, right, arr);
    }

private:
    void Merge(const std::vector<int>& left, const std::vector<int>& right, std::vector<int>& result) {
        int i = 0, j = 0, k = 0;

        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                result[k++] = left[i++];
            }
            else {
                result[k++] = right[j++];
            }
        }

        while (i < left.size()) {
            result[k++] = left[i++];
        }

        while (j < right.size()) {
            result[k++] = right[j++];
        }
    }
};

int main() {
    std::vector<int> arr(10);
    std::cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; i++) {
        std::cin >> arr[i];
    }

    MergeSort mergeSort;

    std::thread mergeSortThread([&]() {
        mergeSort.Sort(arr);
        });

    mergeSortThread.join();

    std::cout << "Sorted array:\n";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
