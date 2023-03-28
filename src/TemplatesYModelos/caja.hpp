#include <memory>
#include <iostream>
#include <concepts>
#include <typeinfo>

template <typename T>
concept Item = requires(T a) { a.size > 0; };

template <Item T>
class Caja
{
public:

    std::shared_ptr<T> item;
    size_t capacity;
    Caja(size_t tam) : item(nullptr), capacity(tam) {}
    
    void addItem(T addItem)
    {
        if (addItem.size < capacity)
            item = std::make_shared<T>(addItem);
        else
            std::cout << "El objeto es demasiado grande" << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &co, Caja c)
    {

        if (c.item == nullptr)
        {
            co << "La caja esta vacia, puede contener un " <<typeid(T).name()<<" con un tamanio maximo de " << c.capacity;
        }
        else
            co << "La caja contiene un "<< typeid(T).name()
               << " de tamanio: " << c.item.get()->size << std::endl;
        return co;
    }
};
