#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>

using namespace std;

const int THRESHOLD = 8;
template <typename T>
class ListaConHuecos
{
public:
    vector<vector<T>> list;

    void insert(T elem)
    {
        int inf = 0;
        int sup = list.size() - 1;
        int index;
        while (inf < sup)
        {

            int midIndex = (inf + sup) / 2;

            if (elem == list[midIndex][0])
            {
                break;
            }
            else if (elem < list[midIndex][0])
            {
                sup = midIndex - 1;
            }
            else
            {
                inf = midIndex + 1;
            }
        }

        if (list.size() == 0)
        {
            list.push_back({elem});
        }
        else
        {
            index = list[inf][0] >= elem && inf != 0 ? inf - 1 : inf;
            
            auto it = upper_bound(list[index].begin(), list[index].end(), elem);
            list[index].insert(it, elem);

            if (list[index].size() > THRESHOLD)
            {
                int mid = list[index].size() / 2;
                auto new_vec = vector<int>(list[index].begin() + mid, list[index].end());
                list[index].erase(list[index].begin() + mid, list[index].end());
                list.insert(list.begin() + index + 1, new_vec);
            }
        }
    }

    T remove()
    {
        int tam = list.size();
        T ret = list[tam - 1][list[tam - 1].size() - 1];
        list[tam - 1].erase(--list[tam - 1].end());
        if (list[tam - 1].size() == 0)
            list.erase(--list.end());

        return ret;
    }
};

int main()
{
    ListaConHuecos<int> LCH;

    for (int i = 0; i < 40; i++)
    {
        int num = rand() % 1000 + 1;
        LCH.insert(num);
    }

    for (size_t i = 0; i < 40; i++)
    {
        cout << LCH.remove() << endl;
    }

    return 0;
}