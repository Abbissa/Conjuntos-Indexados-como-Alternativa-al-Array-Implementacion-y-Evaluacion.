#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class BinaryHeap
{
private:
    std::vector<T> heap;
    void heapify_up(int index)
    {
        if (index == 0)
        {
            return;
        }
        int parent_index = (index - 1) / 2;
        if (heap[index] < heap[parent_index])
        {
            std::swap(heap[index], heap[parent_index]);
            heapify_up(parent_index);
        }
    }
    void heapify_down(int index)
    {
        int left_child_index = 2 * index + 1;
        int right_child_index = 2 * index + 2;
        int smallest = index;
        if (left_child_index < heap.size() && heap[left_child_index] < heap[smallest])
        {
            smallest = left_child_index;
        }
        if (right_child_index < heap.size() && heap[right_child_index] < heap[smallest])
        {
            smallest = right_child_index;
        }
        if (smallest != index)
        {
            std::swap(heap[index], heap[smallest]);
            heapify_down(smallest);
        }
    }

public:
    BinaryHeap() {}
    BinaryHeap(std::vector<T> vec)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            heap.push_back(vec[i]);
            heapify_up(i);
        }
    }
    void insert(T val)
    {
        heap.push_back(val);
        heapify_up(heap.size() - 1);
    }
    T get_min()
    {

        return heap[0];
    }
    T delete_min()
    {
        T ret = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
        return ret;
    }
    bool is_empty()
    {
        return heap.empty();
    }
    int size()
    {
        return heap.size();
    }
};