// AUTHOR       Jasmine Zeng
// INSTRUCTOR   Professor Terry Atkison
// COURSE       CS 300
// ASSIGNMENT   Project 2

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;



///
/// COURSE CLASS / CONSTRUCTOR / METHODS ==============================================================
/// 

/*
 * The Course class initializes variables and methods for managing one course at a time.
*/
class Course {
private:
    string courseId;
    string courseName;
    vector<string> coursePrerequisites;
public:
    Course() = default;
    Course(string& id, string& name, vector<string>& prerequisites);
    string getCourseId();
    string getCourseName();
    vector<string> getCoursePrerequisites();
    string courseToString();
};

/*
 * The Course constructor creates a Course object for each course in the file.
 * 
 * @param id                the id of the course
 * @param name              the name of the course
 * @param prerequisites     the prerequisites, if any, of the course
*/
Course::Course(string& id, string& name, vector<string>& prerequisites) {
    this->courseId = id;
    this->courseName = name;
    this->coursePrerequisites = prerequisites;
}

/*
 * Getter method for course ID.
 * 
 * @return courseId         the course name 
*/
string Course::getCourseId() {
    return this->courseId;
}

/*
 * Getter method for course name.
 * 
 * @return courseName
*/
string Course::getCourseName() {
    return this->courseName;
}

/*
 * Getter method for course prerequisites.
 * 
 * @return coursePrerequisites      the course prerequisites
*/
vector<string> Course::getCoursePrerequisites() {
    return this->coursePrerequisites;
}

/*
 * Method creating a concatenated string for a course's ID and name.
 * 
 * @return string containing courseId and courseName
*/
string Course::courseToString() {
    return this->courseId + ", " + this->courseName;
}



///
/// COURSES CLASS / CONSTRUCTOR / METHODS =============================================================
/// 

/*
 * The Courses class initializes variables and methods for managing several courses at a time.
*/
class Courses {
private:
    Node* root;
    void removeRecursive(Node* node);
    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseId);
public:
    Courses();
    virtual ~Courses();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseId);
    Course Search(string courseId);
};

/*
 * The Node structure initializes variables and methods for course nodes in a binary tree structure.
*/
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course newCourse) :
        Node() {
        course = newCourse;
    }
};

/*
 * The courses constructor creates a null root for the binary tree.
*/
Courses::Courses() {
    root = nullptr;
}

/*
 * The courses destructor removes a root from the binary tree.
*/
Courses::~Courses() {
    removeRecursive(root);
}

/*
 * The InOrder method traverses the binary tree in order.
*/
void Courses::InOrder() {
    inOrder(root);
}

/*
 * The PostOrder method traverses the binary tree in post-order.
*/
void Courses::PostOrder() {
    postOrder(root);
}

/*
 * The PreOrder method traverses the binary tree in pre-order.
*/
void Courses::PreOrder() {
    preOrder(root);
}

/*
 * The Insert method inserts a course into the binary tree.
*/
void Courses::Insert(Course course) {
    // If the root points to null
    if (root == nullptr) {
        // Set root to new node course
        root = new Node(course);
    }
    // Else
    else {
        // Add node root and course
        this->addNode(root, course);
    }
}

/*
 * The Remove method removes a course from the binary tree.
*/
void Courses::Remove(string courseId) {
    // Remove node root and courseId
    this->removeNode(root, courseId);
}

/*
 * The Search method searches for a course in the binary tree.
 * 
 * @param courseId      the course ID
 * @return course       an empty course if the course is not found
*/
Course Courses::Search(string courseId) {
    // Capitalize courseId to prevent search formatting errors
    transform(courseId.begin(), courseId.end(), courseId.begin(), toupper);
    // Set current node to root
    Node* cur = root;
    // Loop downwards until the bottom is reached, or courseId is found
    while (cur != nullptr) {
        // If courseId is found
        if (cur->course.getCourseId().compare(courseId) == 0) {
            // Return current course
            return cur->course;
        }
        // Else if course is smaller than the current node
        else if (courseId.compare(cur->course.getCourseId()) < 0) {
            // Traverse left
            cur = cur->left;
        }
        // Else course is larger than the current node
        else {
            // Traverse right
            cur = cur->right;
        }
    }
    // Course not found, return empty course
    Course course;
    return course;
}

/*
 * The addNode method recursively adds a course into the binary tree.
 * 
 * @param node      the current node in the tree
 * @param course    the course to be added
*/
void Courses::addNode(Node* node, Course course) {
    // If the node is smaller
    if (node != nullptr && (node->course.getCourseId().compare(course.getCourseId()) > 0)) {
        // If there is no left node
        if (node->left == nullptr) {
            // Assign course to left node
            node->left = new Node(course);
            return;
        }
        // Else there is a left node
        else {
            // Recurse down the left node
            this->addNode(node->left, course);
        }
    }
    // Else if node is larger
    else if (node != nullptr && (node->course.getCourseId().compare(course.getCourseId()) < 0)) {
        // If there is no right node
        if (node->right= nullptr) {
            // Assign course to right node
            node->right = new Node(course);
            return;
        }
        // Else the course is larger than the right node
        else {
            // Recurse down the right node
            this->addNode(node->right, course);
        }
    }
}

/*
 * The removeRecursive method removes a node from the binary tree.
 * 
 * @param node      the course node
*/
void Courses::removeRecursive(Node* node) {
    // If node does not point to null
    if (node != nullptr) {
        // Remove any children 
        removeRecursive(node->left);
        removeRecursive(node->right);
        // Remove current course node
        delete node;
        // Set node to nullpointer
        node = nullptr;
    }
}

/*
 * The inOrder method traverses the binary tree in order.
 * 
 * @param node      the course node
*/
void Courses::inOrder(Node* node) {
    // If the node does not point to null
    if (node != nullptr) {
        // Traverse left
        inOrder(node->left);
        // Print courseId and courseName
        cout << node->course.getCourseId() << ", "
            << node->course.getCourseName() << endl;
        // Traverse right
        inOrder(node->right);
    }
}

/*
 * The postOrder method traverses the binary tree in post-order.
 *
 * @param node      the course node
*/
void Courses::postOrder(Node* node) {
    // If the node does not point to null
    if (node != nullptr) {
        // Traverse left, postOrder
        postOrder(node->left);
        // Traverse right, postOrder
        postOrder(node->right);
        // Print courseId and courseName
        cout << node->course.getCourseId() << ", "
            << node->course.getCourseName() << endl;   
    }
}

/*
 * The preOrder method traverses the binary tree in pre-order.
 *
 * @param node      the course node
*/
void Courses::preOrder(Node* node) {
    // If the node does not point to null
    if (node != nullptr) {
        // Print courseId and courseName
        cout << node->course.getCourseId() << ", "
            << node->course.getCourseName() << endl;
        // Traverse left, preOrder
        preOrder(node->left);
        // Traverse right, preOrder
        preOrder(node->right);
    }
}

/*
 * The removeNode method removes a course from the binary tree.
 * 
 * @param node          the course node
 * @param courseId      the course ID
 * @return course       the empty course node
*/
Node* Courses::removeNode(Node* node, const string courseId) {
    // If the node points to null
    if (node == nullptr) {
        // Return the node
        return node;
    }
    // If the course is smaller than the current node
    else if (courseId.compare(node->course.getCourseId()) < 0) {
        // Traverse left
        node->left = removeNode(node->left, courseId);
    }
    // Else if course is larger than the current node 
    else if (courseId.compare(node->course.getCourseId()) > 0) {
        // Traverse right
        node->right = removeNode(node->right, courseId);
    }
    // Else match found
    else {
        // If it is a leaf node
        if (node->left == nullptr && node->right == nullptr) {
            // Delete node
            delete node;
            // Set node to nullpointer
            node = nullptr;
        }
        // Else if it is a left child
        else if (node->left != nullptr && node->right == nullptr) {
            // Initialize temp node variable
            Node* tmp = node;
            // Set node to left node
            node = node->left;
            // Delete temp node
            delete tmp;
            // Set temp node to nullpointer
            tmp = nullptr;
        }
        // Else if it is a right child
        else if (node->left == nullptr && node->right != nullptr) {
            // Initialize temp node variable
            Node* tmp = node;
            // Set node to right node
            node = node->right;
            // Delete temp node
            delete tmp;
            // Set temp node to nullpointer
            tmp = nullptr;
        }
        // Else it is both children
        else {
            // Initialize temp node variable and set to current node
            Node* tmp = node;
            // While the left node does not point to null
            while (tmp->left != nullptr) {
                // Traverse left
                tmp = tmp->left;
            }
            // Set course node as temp course node 
            node->course = tmp->course;
            // Traverse right and remove node
            node->right = removeNode(node->right, tmp->course.getCourseId());
        }
    }
    // Return course node if empty
    return node;
}



///
/// MAIN METHODS =======================================================================================
/// 

/**
 * The displayCourse method displays formatted course information to the advisor.
 *
 * @param course        constructor containing a course object's information
 */
void displayCourse(Course course) {
    // Get course prerequisites
    vector<string> coursePrerequisites = course.getCoursePrerequisites();
    // Initialize prerequisites string variable
    string prerequisites;
    // If one course prerequisite exists
    if (coursePrerequisites.size() == 1) {
        // Set prerequisites to obtained prerequisites
        prerequisites = course.getCoursePrerequisites()[0];
    }
    // Else if there are more than one prerequisite
    else if (coursePrerequisites.size() > 1) {
        // For each prerequisite
        for (int i = 0; i < coursePrerequisites.size() - 1; i++) {
            // Concatenate prerequisites into a single string
            prerequisites += coursePrerequisites[i] + ", ";
        }
        // Add last element in vector to the string
        prerequisites += coursePrerequisites.back();
    }
    // Else if there are no prerequisites
    else {
        // Notify advisor of no prerequisites
        prerequisites = "N/A";
    }

    // Print out course ID and name
    cout << course.getCourseId() << ", "
        << course.getCourseName() << endl;
    // Print out course prerequisites
    cout << "Prerequisites: " << prerequisites << endl;
}

/**
 * The loadCourses method imports an input file of courses into a container
 *
 * @param inputFile     the input file being imported
 * @param coursesBst    the binary search tree of courses
 * @return              a container of courses read from the imported file
 */
void loadCourses(const string& inputFile, Courses* coursesBst) {
    // Notify advisor that the file is being imported
    cout << "Loading input file..." << inputFile << endl;
    // Initialize import file variable
    ifstream file(inputFile);
    // Initialize line variable for file reading
    string currentLine;
    // Try
    try {
        // While file is being read
        while (getline(file, currentLine)) {
            // Initialize file reading variables
            stringstream ss(currentLine);       // Current course line
            string word, id, name;              // Course word, ID, and name
            vector<string> prerequisites;       // Course prerequisites
            int index = 0;                      // Index
            // While end of file is not met
            while (!ss.eof()) {
                // Get line, word, and delimit by comma
                getline(ss, word, ',');
                // Create a search pattern variable
                word = regex_replace(word, regex(R"(\r\n|\r|\n)"), "");
                // If index is 0
                if (index == 0) {
                    // Assign word as course ID
                    id = word;
                }
                // Else if index is 1
                else if (index == 1) {
                    // Assign word as course name 
                    name = word;
                }
                // Else if there are more indexes on the line
                else {
                    // Assign word to prerequisites string
                    prerequisites.push_back(word);
                }
                // Iterate index
                index++;
            }
            // Create a course data structure for each course and add to the course catalogue
            Course course = Course(id, name, prerequisites);
            // Add course object to the binary search tree
            coursesBst->Insert(course);
        }
    }
    // If file cannot be opened
    catch (ifstream::failure& e) {
        // Print error message
        cerr << e.what() << endl;
    }
    // Safely close file
    file.close();
}

/*
 * The main method runs the entire program. Upon startup, the program will display a menu
 * of choices to the advisor. The following choices are:
 *   1. Load Data Structure.
 *   2. Print Course List.
 *   3. Print Course.
 *   9. Exit
 * The program will execute valid commands until the advisor decides to exit the program.
 * An error message will display for invalid input.
 */
int main(int argc, char** argv) {
    // Initialize a binary search tree for the course catalogue
    Courses* coursesBst;                // Course binary search tree
    coursesBst = new Courses();         // New course in the binary search tree
    Course course;                      // Course object
    string inputFile, courseSearch;        // Course file and search
    // Welcome message
    cout << "Welcome to the course planner." << endl << endl;
    // Initialize advisor choice variable
    int choice;
    // Run the program
    do {
        // Print menu of choices
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl << endl;
        // Prompt advisor to enter choice
        cout << "What would you like to do? ";
        // Get advisor choice
        cin >> choice;
        // Based on the advisor choice
        switch (choice) {
            // Advisor enters 1
            case 1:
                // Set inputFile to text file
                inputFile = "ABCU_Advising_Program_Input.txt";
                // Call loadCourses method
                loadCourses(inputFile, coursesBst);
                break;
            // Advisor enters 2
            case 2:
                // Print header
                cout << "Here is a sample schedule:" << endl << endl;
                // Call InOrder method
                coursesBst->InOrder();
                break;
            // Advisor enters 3
            case 3:
                // Prompt advisor for course to search
                cout << "What course do you want to know about? ";
                // Get input
                cin >> courseSearch;
                // Set course as searched course
                course = coursesBst->Search(courseSearch);
                // If course exists
                if (!course.getCourseId().empty()) {
                    // Print course information
                    displayCourse(course);
                }
                // Else course does not exist
                else {
                    // Print error message
                    cout << "Course Id " << courseSearch << " not found." << endl;
                }
                break;
            // Advisor enters 9
            case 9:
                // Display thank you message
                cout << "Thank you for using the course planner!" << endl;
                break;
            // User enters none of the above
            default:
                // Print error message
                cout << choice << " is not a valid option." << endl;
                // Clear choice
                cin.clear();
                // Ignore
                cin.ignore(numeric_limits<streamsize>::max());
                break;
        }
    // While advisor choice is not 9
    } while (choice != 9);
    // Safely exit program
    return 0;
}
