#include <memory_resource>

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        Node(const T& value, Node* prev = nullptr, Node* next = nullptr)
            : value(value), prev(prev), next(next) {}
    };

    Node* head;
    Node* tail;
    std::pmr::polymorphic_allocator<Node> allocator;

    void clear() {
        Node* current = head;

        while (current) {

            Node* next = current->next;
            std::allocator_traits<decltype(allocator)>::destroy(allocator, current);
            allocator.deallocate(current, 1);
            current = next;

        }
        head = tail = nullptr;
    }


public:
    explicit List(std::pmr::memory_resource* resource = std::pmr::get_default_resource())
        : head(nullptr), tail(nullptr), allocator(resource) {}

    ~List() {
        clear();

    }

    void push_back(const T& value) {

        Node* new_node = allocator.allocate(1);
        allocator.construct(new_node, value, tail, nullptr);

        if (tail) {

            tail->next = new_node;

        } else {

            head = new_node;
        }

        tail = new_node;
    }

    void push_front(const T& value) {
        Node* new_node = allocator.allocate(1);
        allocator.construct(new_node, value, nullptr, head);

        if (head) {
            head->prev = new_node;
        } else {
            tail = new_node;
        }
        head = new_node;
    }
    
    void clear_list() {
        clear();
    }

    class Iterator {
    private:
        Node* current;

    public:
        explicit Iterator(Node* node) : current(node) {}

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        T& operator*() const {
            return current->value;
        }
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
    
};