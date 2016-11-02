//  Alexis_Miller_Interpreter.c
//  Created by Alexis Miller on 10/18/16.
//  Language: C++
//  Xcode 8.1

/* User will run the code and input a string, not a file, to be tested. Press enter when done entering the string.
   use -> for implication
   use v for or
   use ^ for and
   use T for true
   use F for false
   end the statement with a . to be syntactically correct.
 */
#include <iostream>
#include <string>
#include <stack>
using namespace std;

stack<bool> answer;

bool B(string* x, int len);
void IT(string* x, int len);
void IT_Tail(string* x, int len);
void OT(string* x, int len);
void OT_Tail(string* x, int len);
void AT(string* x, int len);
void AT_Tail(string* x, int len);
void L(string* x, int len);
void A(string* x, int len);
string* split(string str);
int j=0;

// B := IT.
bool B(string* x, int len){
    IT(x, len-1);
    if(x[len-1] == "." and !answer.empty()){
        bool a = answer.top();
        answer.pop();
        return a;
    }
    return false;
}

// IT := OT IT_Tail
void IT(string* x, int len){
    bool o = false;
    for(int i=0; i<len; i++){
        if(x[i] == "("){
            for(int j=i+1; j<len; j++){
                if(x[j] == ")"){
                    OT(x, j+1);
                    IT_Tail(x+j+2, len-j-1);
                }
            }
            break;
        }
        if(x[i] == "->"){
            o = true;
            OT(x, i);
            IT_Tail(x+i, len-i);
        }
    }
    if(!o)
        OT(x, len);
}

// IT_Tail := -> OT IT_Tail
//         :=
void IT_Tail(string* x, int len){
    bool o = false;
    if(len == 0)
        answer.push(true);
    for(int i=0; i<=len; i++){
        if(x[i] == "->"){
            o = true;
            if(!answer.top()){
                answer.pop();
                answer.push(true);
            }
            else{
                IT_Tail(x+i+1, len);
                if(!answer.top()){
                    answer.pop();
                    answer.pop();
                    answer.push(false);
                }
                else{
                    answer.pop();
                    answer.pop();
                    answer.push(true);
                }
            }
            break;
        }
    }
    if(!o)
        OT(x, len);
}

// OT := AT OT_Tail
void OT(string* x, int len){
    bool o = false;
    for(int i=0; i<len; i++){
        if(x[i] == "("){
            for(int j=i+1; j<len; j++){
                if(x[j] == ")"){
                    AT(x, j+1);
                    OT_Tail(x+j+2, len-j-1);
                }
            }
            break;
        }
        if(x[i] == "v"){
            o = true;
            AT(x, i);
            OT_Tail(x+i, len-i);
        }
    }
    if(!o)
        AT(x, len);
}

// OT_Tail := v AT OT_Tail
//         :=
void OT_Tail(string* x, int len){
    bool o = false;
    if(len == 0)
        answer.push(true);
    for(int i=0; i<len; i++){
        if(x[i] == "v"){
            o = true;
            if(answer.top()){
                answer.pop();
                answer.push(true);
            }
            else{
                OT_Tail(x+i+1, len-i-1);
                if(answer.top()){
                    answer.pop();
                    answer.pop();
                    answer.push(true);
                }
                else{
                    answer.pop();
                    answer.pop();
                    answer.push(false);
                }
            }
            break;
        }
    }
    if(!o)
        AT(x, len);
}

// AT := L AT_Tail
void AT(string* x, int len){
    bool o = false;
    for(int i=0; i<len; i++){
        if(x[i] == "("){
            for(int j=i+1; j<len; j++){
                if(x[j] == ")"){
                    L(x, j+1);
                    AT_Tail(x+j+2, len-j-1);
                }
            }
            break;
        }
        if(x[i] == "^"){
            o = true;
            L(x, i);
            AT_Tail(x+i, len-i);
        }
    }
    if(!o)
        L(x, len);
}

// AT_Tail := ^ L AT_Tail
//         :=
void AT_Tail(string* x, int len){
    bool o = false;
    if(len == 0)
        answer.push(true);
    for(int i=0; i<len; i++){
        if(x[i] == "^"){
            o = true;
            if(answer.top()){
                AT_Tail(x+i+1, len-i-1);
                if(answer.top()){
                    answer.pop();
                    answer.pop();
                    answer.push(true);
                }
                else{
                    answer.pop();
                    answer.pop();
                    answer.push(false);
                }
            }
            else{
                answer.pop();
                answer.push(false);
            }
        }
    }
    if(!o)
        L(x, len);
}

// L := A
//   := ~L
void L(string* x, int len){
    if(x[0] == "~"){
        L(x+1, len);
        bool a = answer.top();
        answer.pop();
        answer.push(!a);
    }
    else
        A(x, len);
}

// A := T
//   := F
//   := (IT)
void A(string* x, int len){
    if(x[0] == "T"){
        answer.push(true);
    }
    else if(x[0] == "F"){
        answer.push(false);
    }
    else if(x[0] == "(")
        if(x[len-1] == ")")
            IT(x+1, len-2);
}

// function that splits a string into a string* by each symbol (->, ., ~, ^, v, (, ), T, F)
string* split(string str){
    string del[100];
    for(int i=0; i<str.length(); i++){
        if(isspace(str[i])){
        }
        else if(str[i] == '-'){
            if(str[i+1] == '>'){
                del[j] = "->";
                i++;
                j++;
            }
            else{
                error_code();
            }
        }
        else if(str[i] == '.'){
            del[j] = ".";
            j++;
        }
        else if(str[i] == '~'){
            del[j] = "~";
            j++;
        }
        else if(str[i] == '^'){
            del[j] = "^";
            j++;
        }
        else if(str[i] == 'v'){
            del[j] = "v";
            j++;
        }
        else if(str[i] == '('){
            del[j] = "(";
            j++;
        }
        else if(str[i] == ')'){
            del[j] = ")";
            j++;
        }
        else if(str[i] == 'T'){
            del[j] = "T";
            j++;
        }
        else if(str[i] == 'F'){
            del[j] = "F";
            j++;
        }
        else{
            error_code();
        }
    }
    string* a = new string[j];
    for(int i=0; i<j; i++){
        a[i]=del[i];
    }
    string* array = a;
    delete[] a;
    return(array);
}

int main(int argc, const char * argv[]) {
    string a;
    cout << "Enter a boolean expression to check: ";
    
    // user inputs a string
    getline(cin, a);
    
    string* b = split(a);
    int ans = B(b, j);
    if(ans == 1)
        cout << "T\n";
    else
        cout << "F\n";
    return 0;
}
