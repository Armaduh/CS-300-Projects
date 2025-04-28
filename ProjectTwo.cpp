#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Define Course struct
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Node for Binary Search Tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course aCourse) : course(aCourse), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    Course* search(Node* node, string courseNumber);

public:
    BinarySearchTree();
    void Insert(Course course);
    void PrintCourseList();
    Course* SearchCourse(string courseNumber);
};

// BST Constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// Insert course into tree
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    } else {
        addNode(root, course);
    }
}

// Add Node helper (recursive)
void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        } else {
            addNode(node->left, course);
        }
    } else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        } else {
            addNode(node->right, course);
        }
    }
}

// In-order traversal (to print courses alphabetically)
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ": " << node->course.courseTitle << endl;
        inOrder(node->right);
    }
}

// Print course list (in-order)
void BinarySearchTree::PrintCourseList() {
    inOrder(root);
}

// Search for a course
Course* BinarySearchTree::SearchCourse(string courseNumber) {
    return search(root, courseNumber);
}

// Search helper
Course* BinarySearchTree::search(Node* node, string courseNumber) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->course.courseNumber == courseNumber) {
        return &(node->course);
    }
    if (courseNumber < node->course.courseNumber) {
        return search(node->left, courseNumber);
    } else {
        return search(node->right, courseNumber);
    }
}

// Load courses from file
void loadCourses(string filename, BinarySearchTree& bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string number, title, prereq;
        Course course;

        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseTitle, ',');

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        bst.Insert(course);
    }

    file.close();
}

// Print course information
void printCourseInfo(Course* course) {
    if (course == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    cout << course->courseNumber << ": " << course->courseTitle << endl;
    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            cout << course->prerequisites[i];
            if (i < course->prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Main Program
int main() {
    BinarySearchTree bst;
    string choice;
    string filename;

    while (choice != "9") {
        cout << "\nMenu:\n";
        cout << "  1. Load Data Structure\n";
        cout << "  2. Print Course List\n";
        cout << "  3. Print Course\n";
        cout << "  9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == "1") {
            cout << "Enter file name to load: ";
            cin >> filename;
            loadCourses(filename, bst);
        }
        else if (choice == "2") {
            bst.PrintCourseList();
        }
        else if (choice == "3") {
            cout << "Enter course number: ";
            string courseNum;
            cin >> courseNum;
            Course* found = bst.SearchCourse(courseNum);
            printCourseInfo(found);
        }
        else if (choice == "9") {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}