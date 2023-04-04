#include <algorithm>
#include <vector>

const int THRESHOLD = 8;
template <typename T>
class GappedList
{
public:
    std::vector<std::vector<T>> data;

    void insert(T elem)
    {
        size_t inf = 0;
        size_t sup = data.size() - 1;
        size_t index;
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

        if (data[index].size() > THRESHOLD)
        {
            size_t mid = data[index].size() / 2;
            auto new_vec = std::vector<int>(data[index].begin() + mid, data[index].end());
            data[index].erase(data[index].begin() + mid, data[index].end());
            data.insert(data.begin() + index + 1, new_vec);
        }
    }

    T remove()
    {
        int tam = data.size();
        T ret = data[tam - 1][data[tam - 1].size() - 1];
        data[tam - 1].erase(--data[tam - 1].end());
        if (data[tam - 1].size() == 0)
            data.erase(--data.end());

        return ret;
    }
};