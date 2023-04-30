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
}
