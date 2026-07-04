// best practice of queue with dummy node
#include <exception>
#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        struct Node *next;
        Node(T val) : data(val), next(nullptr) {};
    };

    Node *front;
    Node *rear;

public:
    Queue()
    {
        front = new Node(T());
        rear = front;
    }

    ~Queue()
    {
        while (front->next != nullptr) {
            struct Node *temp = front->next;
            front->next = temp->next;
            delete temp;
        }
    }

    bool IsEmpty()
    {
        if (front->next == nullptr) {
            return true;
        }
        return false;
    }

    T Dequeue()
    {
        if (IsEmpty()) {
            throw std::runtime_error("Queue is empty.");
        }
        struct Node *temp = front->next;
        T data = temp->data;

        front->next = temp->next;
        delete temp;

        // important: dont forget handle the border conditon
        if (front->next == nullptr) {
            rear = front;
        }
        return data;
    }

    void Enqueue(T val)
    {
        struct Node *newNode = new Node(val);
        rear->next = newNode;
        rear = newNode;
    }
};

// test

int main()
{
    Queue<int> q;
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);

    std::cout << q.Dequeue() << std::endl;
    std::cout << q.Dequeue() << std::endl;
    std::cout << q.Dequeue() << std::endl;

    try {
        q.Dequeue();
    } catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}