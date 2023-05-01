#include "holder.h"




int main()
{
    ArrayStack A(5);
    A.push("5");
    A.push("6");
    A.pop();
    A.top();
    cout << A;
    //measure_holders("src/words.txt");

    LinkedStack stack;

    // Test push and top
    stack.push("hello");
    stack.push("world");
    cout << "Top element: " << stack.top() << endl;

    // Test pop and is_empty
    while (!stack.is_empty()) {
        cout << "Popped element: " << stack.top() << endl;
        stack.pop();
    }
    cout << "Is stack empty? " << (stack.is_empty() ? "Yes" : "No") << endl;

    // Test print
    stack.push("foo");
    stack.push("bar");
    stack.push("baz");
    cout << "Stack contents: ";
    stack.print(cout);
    cout << endl;
}
