// PL homework: hw2
// regexp_matcher.h

#ifndef _PL_HOMEWORK_REGEXP_MATCHER_H_
#define _PL_HOMEWORK_REGEXP_MATCHER_H_

#include <vector>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include "fsa.h"

using namespace std;

struct RegExpMatcher {
  FiniteStateAutomaton fsa;
};


// Homework 1.3
bool BuildRegExpMatcher(const char* regexp, RegExpMatcher* regexp_matcher);

// Homework 1.3
bool RunRegExpMatcher(const RegExpMatcher& regexp_matcher, const char* str);


vector<int> adding(const char* regexp, vector<FSATableElement>& fsa_elements, int start_state, int front, int back, int &maxN);


#endif

//_PL_HOMEWORK_REGEXP_MATCHER_H_
