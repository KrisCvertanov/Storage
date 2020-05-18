#include <iostream>
#include "Product.h"
#include "Log.h"
#include <cstring>
using namespace std;


int main()
{
    /*Product a;
    cin >> a;
    cout << a;*/

    Log a("2020-04-03", "Some message!");
    cout << a << endl;

    return 0;
}
