#include <iostream>
#include <bits/stdc++.h>
#include <conio.h>
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
            cout << guess[i] << " " << "\033[1;37m";
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
void styled_cout(string s){
    cout << "Word: ";
    for(const char ch:s){
        cout << ch << " ";
    }
    cout << "\n";
}

int solve(){
    vector<string> matching_words = dict;
    int queries = 0;
    int i = 1;
    while(true && matching_words.size()){
        string s = matching_words[rand() % matching_words.size()];
        styled_cout(s);
        if(matching_words.size() == 1){
            break;
        }
        Word word;
        cout << "wordle response: " ;
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
    cout << "\033[1;37m";
    cout << "Please enter below word in the wordle and input response\n";
    cout << "For \033[1;32mGreen \033[1;37mColor enter 0\n";
    cout << "For \033[1;33mYellow \033[1;37mColor enter 1\n";
    cout << "For \033[1;0mGray \033[1;37mColor enter 2\n";
    int n = dict.size();
    solve();
    cout << "\033[0m";
    return 0;
}