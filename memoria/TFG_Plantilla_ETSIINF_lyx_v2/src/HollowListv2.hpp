#include <algorithm>
#include <vector>
#include <iostream>
#include "../InsercionEnListas/puntuacionSmall.hpp"
#include "../InsercionEnListas/puntuacionMedium.hpp"
template <typename T>
struct Node
{
    std::vector<T> data;
    T element;

    Node<T>()
    {
        data = std::vector<T>();
    }
};

template <typename T>

class HollowListv2
{

public:
    int THRESHOLD = 256;
    std::vector<Node<T>> data;
    int tam = 0;

    void insert(T elem)
    {
        size_t inf = 0;
        size_t sup = data.size() - 1;
        size_t index;
        tam++;
        if (data.size() == 0)
        {
            Node<T> node = {};
            node.element = elem;
            data.push_back(node);
            return;
        }
        while (inf < sup && sup != -1)
        {

            int midIndex = (inf + sup) / 2;

            if (elem == data[midIndex].element)
            {
                inf = midIndex + 1;
                break;
            }
            else if (elem < data[midIndex].element)
            {
                sup = midIndex - 1;
            }
            else
            {
                inf = midIndex + 1;
            }
        }
        if (inf == 0 && data[inf].element > elem)

            std::swap(data[inf].element, elem);

        index = data[inf].element >= elem && inf != 0 ? inf - 1 : inf;

        std::vector<T> *vec = &data[index].data;

        auto it = std::upper_bound(vec->begin(), vec->end(), elem);
        vec->insert(it, elem);

        if (vec->size() > THRESHOLD - 1)
        {
            size_t mid = vec->size() / 2;
            auto new_vec = std::vector<T>(vec->begin() + mid, vec->end());
            vec->erase(vec->begin() + mid, vec->end());
            Node<T> node;
            node.element = new_vec[0];
            new_vec.erase(new_vec.begin());
            node.data = new_vec;
            data.insert(data.begin() + index + 1, node);
        }
    }

    T remove()
    {
        tam--;

        if (data.back().data.size() == 0)
        {
            T ret = data[data.size() - 1].element;
            data.pop_back();
            return ret;
        }
        T ret = data.back().data.back();
        data.back().data.pop_back();
        return ret;
    }
    T peek()
    {
        Node<T> node = data.back();
        if (node.data.size() == 0)
            return node.element;
        else
            return node.data.back();
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
