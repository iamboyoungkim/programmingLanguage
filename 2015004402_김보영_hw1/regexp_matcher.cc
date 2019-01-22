#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <cstring>
#include "regexp_matcher.h"

const char ANYCHAR = '.';
const char OPEN_GROUP = '(';
const char CLOSE_GROUP = ')';
const char OPEN_SET = '[';
const char CLOSE_SET = ']';
const char STAR = '*';
const char OR = '|';

using namespace std;


vector<int> adding(const char* regexp, vector<FSATableElement>& fsa_table_elem, int start_state, int front, int back, int& maxN){
    int cursor = front;
    vector<int> current_state;
    vector<int> next_state;
    vector<int> prev_state;
    FSATableElement newElem;
    current_state.push_back(start_state);

    while(cursor<back) {
        for(int i=0; i<current_state.size(); i++) {
            newElem.state = current_state[i];

            if(regexp[cursor] >= 'a' && regexp[cursor] <= 'z') {
                newElem.str = string(1, regexp[cursor]);
                newElem.next_state = ++maxN;
                next_state.push_back(maxN);
                fsa_table_elem.push_back(newElem);
            }

            else if(regexp[cursor] == ANYCHAR){
                maxN++;
                char ch;
                for(ch='a'; ch<='z'; ch++){
                    newElem.str = string(1, ch);
                    newElem.next_state = maxN;
                    fsa_table_elem.push_back(newElem);
                }
                next_state.push_back(maxN);
            }

            else if(regexp[cursor] == OR){
                next_state = adding(regexp, fsa_table_elem, start_state, cursor+1, back, maxN);
                cursor = back;
                next_state.insert( next_state.end(), current_state.begin(), current_state.end() );
            }

            else if(regexp[cursor] == OPEN_SET){
                int bStart = cursor + 1;
                int bEnd = cursor;
                int cnt = 0;

                while(true){
                    if(regexp[bEnd] == OPEN_SET) cnt++;
                    else if(regexp[bEnd] == CLOSE_SET) cnt--;
                    if(cnt == 0) break;
                    bEnd++;
                    if(bEnd >= back){
                        cout<<"error"<<endl;
                        exit(EXIT_FAILURE);
                    }
                }
                maxN++;
                for(int i=bStart; i<bEnd; i++){
                    if(regexp[i]<='z' && regexp[i] >= 'a'){
                        newElem.str = string(1, regexp[i]);
                        newElem.next_state = maxN;
                        fsa_table_elem.push_back(newElem);
                    }
                    else{
                        cout<<"error"<<endl;
                        exit(EXIT_FAILURE);
                    }
                }
                next_state.push_back(maxN);
                cursor = bEnd;
            }
            else if(regexp[cursor] == STAR){
                for(int i=0; i<prev_state.size(); i++ ){
                    for(int j=0; j<current_state.size(); j++){
                        newElem.state = current_state[j];
                        newElem.str = "";
                        newElem.next_state = prev_state[i];
                        fsa_table_elem.push_back(newElem);

                        newElem.state = prev_state[i];
                        newElem.str = "";
                        newElem.next_state = current_state[j];
                        fsa_table_elem.push_back(newElem);
                    }
                }
                next_state = current_state;
            }
            else if(regexp[cursor] == OPEN_GROUP){
                int cnt = 0;
                int bStart = cursor+1;
                int bEnd = cursor;
                vector<int> tmp_states;

                while(true){
                    if(regexp[bEnd] == OPEN_GROUP) cnt++;
                    else if(regexp[bEnd] == CLOSE_GROUP) cnt--;
                    if(cnt == 0) break;
                    bEnd++;
                    if(bEnd >= back){
                        cout<<"error"<<endl;
                        exit(EXIT_FAILURE);
                    }
                }
                for(int i=0; i<current_state.size(); i++){
                    tmp_states = adding(regexp, fsa_table_elem, current_state[i], bStart, bEnd, maxN);
                    maxN++;
                    for(int j=0; j<tmp_states.size(); j++){
                        newElem.state = tmp_states[j];
                        newElem.str = "";
                        newElem.next_state = maxN;
                        fsa_table_elem.push_back(newElem);
                    }
                    next_state.push_back(maxN);
                }
                cursor = bEnd;
            }
            else {
                cout<<"error"<<endl;
                exit(EXIT_FAILURE);
            }
        }
        prev_state = current_state;
        current_state = next_state;
        next_state.clear();
        cursor++;
    }
    return current_state;
}

bool BuildRegExpMatcher(const char* regexp, RegExpMatcher* regexp_matcher){

    int maxN = 1;
    vector<FSATableElement> fsa_table_elem;
    vector<int> accept_states;

    accept_states = adding(regexp, fsa_table_elem, 1, 0, strlen(regexp), maxN);


    return BuildFSA(fsa_table_elem,  accept_states, &(regexp_matcher->fsa) );
}

bool RunRegExpMatcher(const RegExpMatcher& regexp_matcher, const char* str){
    return RunFSA(regexp_matcher.fsa, str);
}
