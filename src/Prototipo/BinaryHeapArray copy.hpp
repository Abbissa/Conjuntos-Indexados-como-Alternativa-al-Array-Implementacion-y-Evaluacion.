#include <vector>
#include <algorithm>

template <typename T>
class BinaryHeap
{
private:
    std::vector<T> data;

    void bubbleUp(int index)
    {
        if (index == 0)
            return;
        int parent = (index - 1) / 2;
        if (data[parent] > data[index])
        {
            std::swap(data[parent], data[index]);
            bubbleUp(parent);
        }
    }
    void bubbleDown(int index)
    {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int min = index;

        if (left < data.size() && data[min] > data[left])
            min = left;
        if (right < data.size() && data[min] > data[right])
            min = right;
        if (min != index)
        {
            std::swap(data[min], data[index]);
            bubbleDown(min);
        }
    }

public:
    void insert(T elem)
    {
        data.push_back(elem);
        bubbleUp(data.size() - 1);
    }
    T getMin()
    {
        return data[0];
    }
    T extractMin()
    {
        T min = data[0];
        data[0] = data[data.size() - 1];
        data.pop_back();
        bubbleDown(0);
        return min;
    }
    bool empty()
    {
        return data.empty();
    }
    int size()
    {
        return data.size();
    }
};
