#if !defined(MAP_H_PA3)
#define MAP_H_PA3

#include <cstddef>
#include <iterator>
#include <utility>

template <typename K, typename V>
class Map
{

private:
    class Pair
    {
    private:
        K key_;
        V value_;

    public:
        Pair(const K &key, const V &value) : key_(key), value_(value) {}
        const K &Key() const { return key_; }
        V &Value() { return value_; }
    };

    class Node
    {
    private:
        Pair pair_;
        Node *next_;

    public:
        Node(const K &key, const V &value) : pair_(key, value), next_(nullptr) {}
        Pair *Pair() { return &pair_; }
        const K &Key() const { return pair_.Key(); }
        V &Value() { return pair_.Value(); }
        Node *Next() const { return next_; }
        void SetNext(Node *next) { next_ = next; }
    };

    Node **data_;
    size_t capacity_;
    size_t size_;

    size_t Index(const K &key) const
    {
        return std::hash<K>()(key) % capacity_;
    }

    void Rehash()
    {
        auto existing_data = data_;
        size_t existing_capacity = capacity_;

        capacity_ *= 2;
        data_ = new Node *[capacity_];
        for (size_t i = 0; i < capacity_; i++)
            data_[i] = nullptr;
        
        size_ = 0;

        for (size_t i = 0; i < existing_capacity; i++)
        {
            Node *current = existing_data[i];
            while (current != nullptr)
            {
                Insert(current->Key(), current->Value());
                Node *temp = current;
                current = current->Next();
                delete temp;
            }
        }
        delete[] existing_data;
    }

    static constexpr double LOAD_FACTOR_THRESHOLD = 0.7;
    static constexpr size_t INITIAL_CAPACITY = 16;

public:
    Map(size_t capacity = INITIAL_CAPACITY) : capacity_(capacity), size_(0)
    {
        data_ = new Node *[capacity_];
        for (size_t i = 0; i < capacity_; i++)
            data_[i] = nullptr;
    }

    Map(const std::initializer_list<std::pair<K, V>> &init_list) : Map(init_list.size() * 2)
    {
        for (const auto &pair : init_list)
            Insert(pair.first, pair.second);
    }

    Map(const Map &other) : Map(other.capacity_)
    {
        for (auto it = other.begin(); it != other.end(); ++it)
            Insert(it->Key(), it->Value());
    }

    Map &operator=(const Map &other)
    {
        if (this != &other)
        {
            this->~Map();
            new (this) Map(other);
        }

        return *this;
    }

    ~Map()
    {
        for (size_t i = 0; i < capacity_; i++)
        {
            Node *current = data_[i];
            while (current != nullptr)
            {
                Node *temp = current;
                current = current->Next();
                delete temp;
            }
        }
        delete[] data_;
    }

    size_t Size() const
    {
        return size_;
    }

    void Insert(const K &key, const V &value)
    {
        if (size_ >= capacity_ * LOAD_FACTOR_THRESHOLD)
            Rehash();

        size_t index = Index(key);
        Node *curr = data_[index];

        while (curr != nullptr)
        {
            if (curr->Key() == key)
            {
                curr->Value() = value;
                return;
            }
            curr = curr->Next();
        }

        Node *new_node = new Node(key, value);
        new_node->SetNext(data_[index]);
        data_[index] = new_node;
        size_++;
    }

    V *Find(const K &key) const
    {
        size_t index = Index(key);
        Node *curr = data_[index];
        while (curr != nullptr)
        {
            if (curr->Key() == key)
                return &(curr->Value());
            curr = curr->Next();
        }
        return nullptr;
    }

    void Delete(const K &key)
    {
        size_t index = Index(key);
        Node *curr = data_[index];
        Node *prev = nullptr;
        while (curr != nullptr)
        {
            if (curr->Key() == key)
            {
                if (prev == nullptr)
                {
                    data_[index] = curr->Next();
                }
                else
                {
                    prev->SetNext(curr->Next());
                }
                delete curr;
                size_--;
                return;
            }
            prev = curr;
            curr = curr->Next();
        }
    }

    size_t Capacity() const
    {
        return capacity_;
    }

    V *operator[](const K &key)
    {
        return Find(key);
    }

    const V *operator[](const K &key) const
    {
        return Find(key);
    }

    class Iterator
    {
    private:
        const Map *map_;
        size_t bucket_;
        Node *current_;

        void Next()
        {
            if (current_ != nullptr)
                current_ = current_->Next();

            while (current_ == nullptr && bucket_ < map_->Capacity())
                current_ = map_->data_[bucket_++];
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Pair;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

        Iterator(const Map *map, size_t bucket, Node *current = nullptr) : map_(map), bucket_(bucket), current_(current)
        {
            Next();
        }

        reference operator*() const
        {
            return *(current_->Pair());
        }

        pointer operator->() const
        {
            return current_->Pair();
        }

        Iterator &operator++()
        {
            Next();
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
            return current_ == other.current_;
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
        return Iterator(this, capacity_, nullptr);
    }
};

#endif // MAP_H_PA3
