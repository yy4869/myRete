#include <iostream>
#include "test.h"
using namespace std;

void printFact(Fact* f){
    cout<<"fact:"<<endl;

    cout<<f->elementName<<endl;
    map<string,DATA_OBJECT*>::iterator it = f->attr_val.begin();
    for(;it != f->attr_val.end();it++){
        cout<<it->first<<":"<<it->second->value<<":"<<it->second->type<<endl;
    }

}
AlphaNode* buildAlphaNetWork()
{
    AlphaNode* root = new AlphaNode();
    AlphaNode* alpha1_1 = new AlphaNode("name");
    AlphaNode* alpha1_2 = new AlphaNode("age");

    root->child["person"] = alpha1_1;
    root->child["shop"] = alpha1_2;


    AlphaNode* alpha2_1 = new AlphaNode("NULL",true);
    AlphaNode* alpha2_2 = new AlphaNode("NULL",true);
    alpha1_1->child["ALL"] = alpha2_1;
    alpha1_2->child["ALL"] = alpha2_2;

    BetaNode* beta1_1 = new BetaNode();
    BetaNode* beta2_1 = new BetaNode();
    BetaNode* beta3_1 = new BetaNode(true);
    alpha2_1->betaNodes.push_back(beta1_1);
    alpha2_2->betaNodes.push_back(beta2_1);
    beta1_1->childNode.push_back(beta2_1);
    beta2_1->childNode.push_back(beta3_1);


    return root;

}
