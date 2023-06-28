#include <vector>
#include <algorithm>

template <typename T>
class HollowList
{
public:
    int threshold = 256;
    std::vector<std::vector<T>> data;
    int tam = 0;

    void insert(T elem)
    {
        tam++;
        std::size_t inf = 0;
        std::size_t sup = data.size() - 1;
        std::size_t index;
        if (data.size() == 0)
        {
            data.push_back({elem});
            return;
        }
        while (inf < sup && sup != -1)
        {

            int midIndex = (inf + sup) / 2;

            if (elem == data[midIndex][0])
            {
                inf = midIndex + 1;
                break;
            }
            else if (elem < data[midIndex][0])
            {
                sup = midIndex - 1;
            }
            else
            {
                inf = midIndex + 1;
            }
        }

        index = data[inf][0] >= elem && inf != 0 ? inf - 1 : inf;

        auto it = upper_bound(data[index].begin(), data[index].end(), elem);
        data[index].insert(it, elem);

        if (data[index].size() > threshold)
        {
            std::size_t mid = data[index].size() / 2;
            auto new_vec = std::vector<T>(data[index].begin() + mid, data[index].end());
            data[index].erase(data[index].begin() + mid, data[index].end());
            data.insert(data.begin() + index + 1, new_vec);
        }
    }

    T remove()
    {
        tam--;
        int tam = data.size();
        T ret = data[tam - 1][data[tam - 1].size() - 1];
        data[tam - 1].erase(--data[tam - 1].end());
        if (data[tam - 1].size() == 0)
            data.erase(--data.end());

        return ret;
    }
    T peek()
    {
        return data.back().back();
    }
    bool isEmpty()
    {
        return data.size() == 0;
    }
    int size()
    {

        return tam;
    }
};
