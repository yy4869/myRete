#include <iostream>
#include "fact.h"
#include "test.h"

using namespace std;



int main()
{
    AlphaNode* root = buildAlphaNetWork();
    string sf = "person name tom age 10";
    Fact* fact = readFact(sf);
    cout << "Hello world!" << endl;
    printFact(fact);

    factToAM(fact,root);

    return 0;
}
