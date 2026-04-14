#pragma once

#include <optional>
#include <cassert>

template<typename T>
class MinHeap
{
public:
    MinHeap() : data(nullptr), size(0), capacity(0), height(0) {}
    ~MinHeap()
    {
        delete[] this->data;
    }

    void push(T value)
    {
        if (this->size >= this->capacity)
        {
            resize();
        }

        int i = this->size++;
        int parent = (i - 1) / 2;

        while (i > 0 && value < data[parent] )
        {
            this->data[i] = this->data[parent];
            i = parent;
            parent = (i - 1) / 2;
        }

        data[i] = value;
    }

    void pop()
    {
        if (this->size == 0)
            return;

        T v = this->data[--(this->size)];

        int i = 0;
        int min_child = 1;

        while (min_child < this->size)
        {
            if ((min_child + 1 < this->size) &&
                (this->data[min_child + 1] < this->data[min_child]))
            {
                min_child = min_child + 1;
            }

            if (v <= this->data[min_child])
            {
                break;
            }

            this->data[i] = this->data[min_child];
            i = min_child;
            min_child = 2 * min_child + 1;
        }

        this->data[i] = v;
    }

    const T& top()
    {
        assert(!is_empty());
        return this->data[0];
    }

    bool is_empty()
    {
        return !(this->size > 0);
    }

    void clear()
    {
        this->size = 0;
    }

private:
    void resize()
    {
        int new_capacity = (1 << (this->height + 1)) - 1;
        T *new_data = new T[new_capacity];

        for (int i = 0; i < this->size; ++i)
        {
            new_data[i] = this->data[i];
        }

        delete[] this->data;
        this->data = new_data;
        this->capacity = new_capacity;
        ++(this->height);
    }

    T *data;
    int size;
    int capacity;
    int height;
};
