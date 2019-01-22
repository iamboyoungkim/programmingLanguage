// PL homework: hw1
// fsa.cc

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <iterator>

#include "fsa.h"

#define DISABLE_LOG true
#define LOG \
if (DISABLE_LOG) {} else std::cerr

using namespace std;

bool nfaCheck(const vector<FSATableElement>& elements) {
    for(int i = 0; i < elements.size(); i++){
        if(elements[i].str == "") return true;

        for(int j = i + 1; j < elements.size(); j++){
            if((elements[i].state == elements[j].state) && (elements[i].str == elements[j].str))
                return true;
        }
    }
    return false;
}
void checkEpsilon(const vector<FSATableElement>& elements, set<int>* state, int start){

    int j;
    for(j=0; j<elements.size(); j++){
        if(elements[j].state == start && elements[j].str == "") {
            set<int>::iterator t = state->find(elements[j].next_state);
            if(t == state->end()) {
                state->insert(elements[j].next_state);
                checkEpsilon(elements, state, elements[j].next_state);
            }
        }
    }
}
void moveToNext(const vector<FSATableElement>& elements, FiniteStateAutomaton* fsa, set<int> cur){
    set<int> next;

    /*
    printf("cur : <");
    for(set<int>::iterator IT2=cur.begin(); IT2!=cur.end(); IT2++) {
        printf("%d ", *IT2);
    }
    printf(">\n");
    */
    for(set< char >::iterator IT1=fsa->inputs.begin(); IT1!=fsa->inputs.end(); IT1++){
        char c = *IT1;
        next.clear();

        for(set<int>::iterator IT2=cur.begin(); IT2!=cur.end(); IT2++){
            for(int i=0; i<elements.size(); i++){
                for(int j=0;j<elements[i].str.size();j++){
                    if(elements[i].state == *IT2 && elements[i].str[j] == c){
                        next.insert(elements[i].next_state);
                        checkEpsilon(elements, &next, elements[i].next_state);
                    }
                }
            }
        }

        pair< set<int>, char > temp(cur,c);

        fsa->Tmp[temp] = next;
        /*
        printf("make load : <");
        for(set<int>::iterator IT2=cur.begin(); IT2!=cur.end(); IT2++) {
            printf("%d ", *IT2);
        }
        printf("> (%c) ", c);

        printf("<");
        for(set<int>::iterator IT2=next.begin(); IT2!=next.end(); IT2++) {
            printf("%d ", *IT2);
        }
        printf(">\n");
        */
        set< set<int> >::iterator t = fsa->states.find(next);
        if(t == fsa->states.end()) {
            fsa->states.insert(next);
            if(!next.empty()) moveToNext(elements, fsa, next);
        }
    }
}

bool BuildDFA(const vector<FSATableElement>& elements, const vector<int>& accept_states, FiniteStateAutomaton* fsa){
    set<int> current_state, next;
    if(elements.size() <= 0) return false;

    for(int i = 0; i < accept_states.size(); i++){
        fsa->accept_state.insert(accept_states[i]);
    }
    for(int i = 0; i < elements.size(); i++){
        if(i == 0) fsa->first_state.insert(elements[i].state);
        for(int j=0; j<elements[i].str.size(); j++){

            current_state.insert(elements[i].state);
            next.insert(elements[i].next_state);
            pair< set<int>, char > temp(current_state, elements[i].str[j]);
            fsa->Tmp[temp] = next;
            current_state.clear();
            next.clear();
        }
    }
    return true;
}

bool BuildNFA(const vector<FSATableElement>& elements, const vector<int>& accept_states, FiniteStateAutomaton* fsa){
    set<int> first_state;
    for(int i = 0; i < accept_states.size(); i++){
        fsa->accept_state.insert(accept_states[i]);
    }
    for(int i = 0; i < elements.size(); i++){
        for(int j = 0; j < elements[i].str.size(); j++){
            if(elements[i].str != "")
                fsa->inputs.insert(elements[i].str[j]);
        }
    }
    first_state.insert(elements[0].state);
    checkEpsilon(elements, &first_state, elements[0].state);

    fsa->first_state = first_state;
    fsa->states.insert(first_state);

    moveToNext(elements, fsa, first_state);

    return true;
}
bool RunFSA(const FiniteStateAutomaton& fsa, const std::string& str){
    set<int> current_state;
    current_state = fsa.first_state;

    for(int i=0; i<str.size(); i++){
        char ch = str[i];
        pair< set< int >, char > temp(current_state, ch);

        map< pair< set< int >, char >, set< int > >::const_iterator IT1 = fsa.Tmp.find(temp);
        if( IT1 != fsa.Tmp.end() ) current_state = fsa.Tmp.at(temp);
        else return false;
    }
    for(set<int>::iterator IT2=fsa.accept_state.begin(); IT2!=fsa.accept_state.end(); IT2++){
        for(set<int>::iterator IT3=current_state.begin(); IT3!=current_state.end(); IT3++){
            if(*IT3 == *IT2) return true;
            else if(*IT3 > *IT2) break;
        }
    }
    return false;
}

bool BuildFSA(const vector<FSATableElement>& elements, const vector<int>& accept_states, FiniteStateAutomaton* fsa) {

    if(nfaCheck(elements)) return BuildNFA(elements, accept_states, fsa);
    else return BuildDFA(elements, accept_states, fsa);

    LOG << "num_elements: " << elements.size()
    << ", accept_states: " << accept_states.size() << endl;
    return false;
}
