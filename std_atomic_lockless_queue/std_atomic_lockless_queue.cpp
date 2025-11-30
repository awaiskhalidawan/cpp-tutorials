#include <iostream>
#include <optional>
#include <cassert>

template<typename T>
struct queue_node 
{
    T el;
    std::atomic<queue_node<T> *> next {nullptr};
    std::atomic<queue_node<T> *> previous {nullptr};

    queue_node(T el) {
        this->el = el;
    }
};

template <typename T>
class lockless_queue 
{
public:
    void push(T el) {
        auto queue_el = new queue_node<T>(el);
        auto current_head = head.load();

        while (!head.compare_exchange_strong(current_head, queue_el));
        queue_el->next.store(current_head);
        
        if (!current_head) {
            auto current_tail = tail.load();
            assert(!current_tail && "Tail pointer is not null. ");
            tail.compare_exchange_strong(current_tail, queue_el);
        }
        else {
            current_head->previous.store(queue_el);
        }
        ++size;
    }

    std::optional<T> pop() {
        auto current_tail = tail.load();
        if (!current_tail) {
            return std::nullopt;
        }

        if (current_tail->previous.load()) {
            tail.store(current_tail->previous);
        }
        else {
            auto current_head = head.load();
            if (current_tail != current_head) {
                // A push operation is in progress. Return and try the pop again later.
                return std::nullopt;
            }
            else {
                tail.compare_exchange_strong(current_tail, nullptr);
                head.compare_exchange_strong(current_head, nullptr);
            }
        }

        --size;
        const T val = current_tail->el;
        delete current_tail;
        return val;
    }

    size_t estimated_size() const {
        return size.load();
    }

private:
    std::atomic<queue_node<T> *> head {nullptr};
    std::atomic<queue_node<T> *> tail {nullptr};
    std::atomic<size_t> size {0};
};

int main()
{
    std::cout << "Introduction to atomic lockless queue in C++ ...\n";

    lockless_queue<int> queue;

    queue.push(1);

    return 0;
}

