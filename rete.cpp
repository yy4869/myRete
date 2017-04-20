#include <string>
#include <iostream>
#include <cstdio>
#include "rete.h"

void factToAM(Fact* fact,AlphaNode* root){

    root = root->child[fact->elementName];
    while(!root->isAM)
    {
        string check = root->checkAttriName;
        cout<<"alpha check: "<<check<<endl;
        if(root->child.find(fact->attr_val[check]->value) != root->child.end())
            root = root->child[fact->attr_val[check]->value];
        else
            root = root->child["ALL"];

    }
    root->alphaMemory.push_back(fact);
    //cout<<root->alphaMemory.size()<<endl;
}

PartialMatch* mergePartialMatch(PartialMatch* lhsBinds,AlphaMatch* alphaMatch)
{
     PartialMatch* links = new PartialMatch();
     if(lhsBinds != NULL){
        for(size_t i = 0; i < lhsBinds->facts.size();i++){
            links->facts.push_back(lhsBinds->facts[i]);
        }
        //links->realiseTime = min(lhsBinds->realiseTime,alphaMatch->realiseTime);
    }
    if(alphaMatch != NULL){
        links->facts.push_back(alphaMatch->fact);
    }
     return links;
}
bool evaluateOnNode(PartialMatch* lhsBinds,AlphaMatch* alphaMatch,BetaNode* curNode)
{
    return true;
}
void networkRight(AlphaMatch* rhsBinds,BetaNode* curNode)
{
    curNode->rightMemory.push_back(rhsBinds);
	list<PartialMatch*> &leftMemory = curNode->leftMemory;
    //cout<<"networkRight"<<endl;

    if(curNode->firstJoin){
        PartialMatch* links = mergePartialMatch(NULL,rhsBinds);
        for(size_t k = 0; k < curNode->childNode.size();k++)
		{
            networkLeft(links,curNode->childNode[k]);
        }
        return ;
    }

	for (list<PartialMatch*>::iterator it = leftMemory.begin(); it != leftMemory.end();it++)
	{
        if(evaluateOnNode(*it,rhsBinds,curNode))
        {
            PartialMatch* links = mergePartialMatch(*it,rhsBinds);
            for(size_t k = 0; k < curNode->childNode.size();k++)
			{
                networkLeft(links,curNode->childNode[k]);

            }
        }
    }
    return ;
}
void networkLeft(PartialMatch* lhsBinds,BetaNode* curNode)
{
    curNode->leftMemory.push_back(lhsBinds);
    if(curNode->ruleToActive.size()){
        LARGE_INTEGER curTime;
        QueryPerformanceCounter(&curTime);
        printf("rule %lld\n",curTime.QuadPart);
        return ;
    }

	list<AlphaMatch*> &rightMemory = curNode->rightMemory;

	for (list<AlphaMatch*>::iterator it = rightMemory.begin(); it != rightMemory.end();it++)
    {

        if(evaluateOnNode(lhsBinds,*it,curNode))
		{
			PartialMatch* links = mergePartialMatch(lhsBinds, *it);
            for(size_t k = 0; k < curNode->childNode.size();k++)
			{
                networkLeft(links,curNode->childNode[k]);
            }
        }
    }
    return ;
}
