#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int MATCH = 0, EXISTS = 1, NOT_EXISTS = 2;
vector<string> dict;

struct Word{
    int a[5];
    bool is_perfect_match(){
        for(int i = 0; i < 5; i++){
            if(a[i] != MATCH){
                return false;
            }
        }
        return true;
    }
    bool operator == (const Word& other){
        for(int i = 0; i < 5; i++){
            if(a[i] != other.a[i]) return false;
        }
        return true;
    }
    void print(string guess){
    for(int i = 0; i < 5; i++){
        if(a[i] == MATCH){
            cout << "\033[1;32m";
        }else if(a[i] == EXISTS){
            cout << "\033[1;33m";
        }else{
            cout << "\033[1;37m";
        }
        cout << guess[i] << " " << "\033[0m";
    }
    cout << "\n";
}

};


void load_data(){
    ifstream cin("wordle.txt");
    string s;
    while(cin >> s){
        dict.push_back(s);
    }
}

Word compare(string hidden, string guess){
    Word word;
    vector<bool> used(5, 0);
    for(int i = 0;  i < 5; i++){
        word.a[i] = NOT_EXISTS;
        if(hidden[i] == guess[i]){
            used[i] = true;
            word.a[i] = MATCH;
        }
    }
    for(int i = 0; i < 5; i++){
        if(word.a[i] == NOT_EXISTS){
            for(int j = 0; j < 5; j++){
                if(!used[j] && hidden[j] == guess[i]){
                    used[j] = true;
                    word.a[i] = EXISTS;
                }
            }
        }
    }
    return word;
}

int solve(){
    vector<string> matching_words = dict;
    int queries = 0;
    int i = 1;
    
    while(true && matching_words.size()){
        string s = "";
        if(i++ != 1)
            s = matching_words[rand() % matching_words.size()];
        else
            s = "awarn";
        cout << s << "\n";
        Word word;
        for(int i = 0; i < 5; i++){
            cin >> word.a[i]; 
        }
        queries++;
        word.print(s);
        if(word.is_perfect_match()){
            matching_words.resize(1);
            matching_words[0] = s;
            break;
        }
        vector<string> new_matching_words;
        for(string maybe: matching_words){
            if(compare(maybe, s) == word){
                new_matching_words.push_back(maybe);
            }
        }
        matching_words = new_matching_words;
    }
    if(matching_words.size() == 1)
        cout << "congratulations! You Won!" << "\n";
    else
        cout << "Please enter the correct output from game." << "\n";
    return queries;
}


int main(){
    std::srand(std::time(0));
    load_data();
    int avg = 0;
    int n = dict.size();
    solve();
    return 0;
}