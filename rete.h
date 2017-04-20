#ifndef _RETE_H_
#define _RETE_H_
#include <windows.h>
#include <string>
#include <list>
#include <map>
#include <vector>
#include "fact.h"
#include "thread.h"

struct BetaNode;
struct AlphaNode{
    string checkAttriName;
    map<string,AlphaNode*> child;
    bool isAM;

    list<Fact*> alphaMemory;
    list<BetaNode*> betaNodes;
    AlphaNode(string name = "ELEMENT",bool last = false):checkAttriName(name),isAM(last){}
};
struct AlphaMatch{
    Fact* fact;
};
struct PartialMatch{
    vector<Fact*> facts;
};
struct EvaluationNode{
    string functionName;
    string argAttriName1;
    string argAttriName2;
};
struct BetaNode{
    string ruleToActive;
    bool isRunning;
    bool firstJoin;
    long long numOfInstance;
    CRITICAL_SECTION nodeSection;
    list<ActiveJoinNode*> instance;
	list<AlphaMatch*> rightMemory;
	list<PartialMatch*>leftMemory;
	vector<BetaNode*> childNode;
	int disToEnd;
	long long deadline;
	vector<EvaluationNode*> evaluations;
	BetaNode(bool fj = false):firstJoin(fj){}
};


void factToAM(Fact* fact,AlphaNode* root);
PartialMatch* mergePartialMatch(PartialMatch* lhsBinds,AlphaMatch* alphaMatch);
void networkLeft(PartialMatch* lhsBinds,BetaNode* curNode);
void networkRight(AlphaMatch* rhsBinds,BetaNode* curNode);
bool evaluateOnNode(PartialMatch* lhsBinds,AlphaMatch* alphaMatch,BetaNode* curNode);
#endif // _RETE_H_
