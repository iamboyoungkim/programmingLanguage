// PL homework: hw2
// lr_parser.cc

#include <assert.h>

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include "lr_parser.h"

#define DISABLE_LOG false
#define LOG \
if (DISABLE_LOG) {} else std::cerr


using namespace std;

bool BuildLRParser(const std::vector<LRTableElement>& elements,
                   const std::vector<LRRule>& rules,
                   LRParser* lr_parser) {

    for(int i = 0; i < elements.size(); i++){
        lr_parser->LRTable[make_pair(elements[i].state, elements[i].symbol)] = make_pair(elements[i].action, elements[i].next_state);
    }

    for (int i = 0; i < rules.size(); i++){
        lr_parser->LRrule[rules[i].id] = make_pair(rules[i].lhs_symbol, rules[i].num_rhs);
    }

    return true;
}

bool RunLRParser(LRParser& lr_parser, const std::string& str){
    vector<int> stack;
    int idx = 0;
    int tmp;

    stack.push_back(0);

    while(true){
        map<pair<int, int>, pair<LRAction, int> >::iterator IT = lr_parser.LRTable.find(make_pair(stack.back(), str[idx]));

        //if( IT != lr_parser.LRTable.find(stack[idx])->second.end() ){
        switch(IT->second.first){
        case INVALID:{
            return false;
        }
        case SHIFT:{
            stack.push_back(str[idx]);
            idx++;
            stack.push_back(IT->second.second);
            break;
        }
        case REDUCE:{
            map<int, pair<int, int> >::iterator IT2 = lr_parser.LRrule.find(IT->second.second);
            int ss = stack.size();
            tmp = ss / 2 - IT2->second.second;

            map<pair<int, int>, pair<LRAction, int> >::iterator IT3 = lr_parser.LRTable.find(make_pair(stack[tmp*2], IT2->second.first));

            for(int i=0; i < (IT2->second.second*2); i++){
                stack.pop_back();
            }
            stack.push_back(IT2->second.first);
            stack.push_back(IT3->second.second);
            break;
        }
        case ACCEPT:{
            return true;
        }
        default:{
            cout<<"error"<<endl;
            break;
        }
    }
  }
//}


    return false;
}
