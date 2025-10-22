#if !defined(LIST_H_PA3)
#define LIST_H_PA3

#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <initializer_list>

template <typename T>
class List
{

private:
    T *data_;
    size_t size_;
    size_t capacity_;

    static constexpr size_t INITIAL_CAPACITY = 4;
    static constexpr size_t CAPACITY_MULTIPLIER = 2;

public:
    List() : data_(new T[INITIAL_CAPACITY]), size_(0), capacity_(INITIAL_CAPACITY) {}

    List(const std::initializer_list<T> &init_list) : data_(new T[init_list.size()]), size_(init_list.size()), capacity_(init_list.size())
    {
        std::copy(init_list.begin(), init_list.end(), data_);
    }

    List(const List &other) : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_)
    {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    List &operator=(const List &other)
    {
        if (this != &other)
        {
            delete[] data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            data_ = new T[capacity_];
            std::copy(other.data_, other.data_ + other.size_, data_);
        }
        return *this;
    }

    ~List()
    {
        delete[] data_;
    }

    size_t Size() const
    {
        return size_;
    }

    size_t Capacity() const
    {
        return capacity_;
    }

    void Delete(size_t index)
    {
        if (index >= size_)
            throw std::out_of_range("Index out of range");

        for (size_t i = index; i < size_ - 1; i++)
            data_[i] = data_[i + 1];

        size_--;
    }

    void Resize(size_t capacity)
    {
        auto new_data = new T[capacity];
        size_t copy_size = std::min(size_, capacity);
        std::copy(data_, data_ + copy_size, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = capacity;
    }

    void Insert(const T &value)
    {
        if (size_ >= capacity_)
            Resize(capacity_ * CAPACITY_MULTIPLIER);
        data_[size_++] = value;
    }

    T &operator[](size_t index)
    {
        if (index >= size_)
            throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const T &operator[](size_t index) const
    {
        if (index >= size_)
            throw std::out_of_range("Index out of range");
        return data_[index];
    }

    size_t size() const
    {
        return size_;
    }

    class Iterator
    {
    private:
        const List *list_;
        size_t index_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type *;
        using reference = const value_type &;

        Iterator(const List *list, size_t index) : list_(list), index_(index)
        {
            if (index_ > list_->Size())
            {
                throw std::out_of_range("Iterator index out of range");
            }
        }

        reference operator*() const
        {
            return (*list_)[index_];
        }

        pointer operator->() const
        {
            return &((*list_)[index_]);
        }

        Iterator &operator++()
        {
            ++index_;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator &other) const
        {
            return index_ == other.index_ && list_ == other.list_;
        }

        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }
    };

    Iterator begin() const
    {
        return Iterator(this, 0);
    }

    Iterator end() const
    {
        return Iterator(this, size_);
    }

    Iterator Find(const T &value) const
    {
        for (size_t i = 0; i < size_; i++)
        {
            if (data_[i] == value)
            {
                return Iterator(this, i);
            }
        }
        return end();
    }
};

#endif // LIST_H_PA3
