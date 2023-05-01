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
    cout << endl;
    // Test ArrayQueue
    ArrayQueue q(5);
    q.enq("apple");
    q.enq("banana");
    q.enq("cherry");
    q.print(cout);  // expected output: apple banana cherry
    cout << endl;   // print a newline character
    q.deq();
    q.print(cout);  // expected output: banana cherry
    q.enq("date");
    q.enq("elderberry");
    q.enq("fig");
    cout << q.is_full() << endl;  // expected output: 1
    q.print(cout);  // expected output: banana cherry date elderberry fig
    q.deq();
    q.deq();
    q.deq();
    q.print(cout);  // expected output: elderberry fig
    q.deq();
    q.deq();
    cout << q.is_empty() << endl;  // expected output: 1
}
