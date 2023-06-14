#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Node definition for linked list
struct Node {
    std::string data;
    Node* next;

    Node(const std::string& value) : data(value), next(nullptr) {}
};

// Cluster definition for storing linked lists
struct Cluster {
    std::vector<Node*> linkedLists;

    Cluster() : linkedLists() {}

    ~Cluster() {
        for (Node* node : linkedLists) {
            delete node;
        }
    }
};

// Ahmed data structure
class Ahmed {
private:
    std::vector<Cluster*> clusters;

public:
    Ahmed() : clusters() {}

    ~Ahmed() {
        for (Cluster* cluster : clusters) {
            delete cluster;
        }
    }

    void addCluster() {
        clusters.push_back(new Cluster());
    }

    void addLinkedList(int clusterIndex, const std::vector<std::string>& values) {
        Cluster* cluster = clusters[clusterIndex];
        Node* head = nullptr;
        Node* prevNode = nullptr;

        for (const std::string& value : values) {
            Node* newNode = new Node(value);

            if (prevNode) {
                prevNode->next = newNode;
            } else {
                head = newNode;
            }

            prevNode = newNode;
            cluster->linkedLists.push_back(newNode);
        }

        prevNode->next = nullptr;
    }

    Node* getRandomPointer() {
        int clusterCount = clusters.size();
        if (clusterCount == 0) {
            return nullptr;
        }

        // Generate random cluster index
        int clusterIndex = rand() % clusterCount;
        Cluster* cluster = clusters[clusterIndex];

        // Generate random linked list index within the cluster
        int linkedListIndex = rand() % cluster->linkedLists.size();

        return cluster->linkedLists[linkedListIndex];
    }
};

int main() {
    srand(time(0)); // Initialize random seed

    Ahmed ahmed;
    ahmed.addCluster();

    std::vector<std::string> linkedList1 = { "Cats", "are", "awesome" };
    ahmed.addLinkedList(0, linkedList1);

    std::vector<std::string> linkedList2 = { "Dogs", "are", "friendly"};
    ahmed.addLinkedList(0, linkedList2);
        
    // Get a random pointer from the "ahmed" data structure
    Node* randomPointer = ahmed.getRandomPointer();

    // Traverse and print the linked list starting from the random pointer
    while (randomPointer) {
        std::cout << randomPointer->data << " ";
        randomPointer = randomPointer->next;
    }
    std::cout << std::endl;

    return 0;
}
