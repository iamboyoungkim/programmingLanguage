// PL homework: hw2
// lr_parser.h

#ifndef _PL_HOMEWORK_LR_PARSER_H_
#define _PL_HOMEWORK_LR_PARSER_H_

#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

enum LRAction {
    INVALID = 0,
    SHIFT = 1,
    REDUCE = 2,
    ACCEPT = 3,
    GOTO = 4
};

struct LRTableElement {
    int state;
    int symbol;
    LRAction action;
    int next_state;
};

struct LRRule {
    int id;
    int lhs_symbol;
    int num_rhs;
};

struct LRParser {
    map<pair<int, int>, pair<LRAction, int> > LRTable;
    map<int, pair<int, int> > LRrule;
};

// Homework 1.2
bool BuildLRParser(const std::vector<LRTableElement>& elements, const std::vector<LRRule>& rules, LRParser* lr_parser);

// Homework 1.2
bool RunLRParser(LRParser& lr_parser, const std::string& str);

#endif //_PL_HOMEWORK_LR_PARSER_H_
