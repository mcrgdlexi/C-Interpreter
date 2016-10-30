//  Alexis_Miller_Interpreter.c
//  Created by Alexis Miller on 10/18/16.
//  Language: C++
//  Xcode 8.0

#include <iostream>
#include <string>
using namespace std;

bool B(string* x);
bool IT(string* x);
bool IT_Tail(string* x);
bool OT(string* x);
bool OT_Tail(string* x);
bool AT(string* x);
bool AT_Tail(string* x);
bool L(string* x);
bool A(string* x);
string* split(string str);

bool B(string* x){
    if(IT(x))
        if(x[x->length()-1] == ".")
            return true;
    return false;
}

bool IT(string* x){
    if(OT(x))
        return true;
    return false;
}

bool IT_Tail(string* x){
    return true;
}

bool OT(string* x){
    return true;
}

bool OT_Tail(string* x){
    return true;
}

bool AT(string* x){
    return true;
}

bool AT_Tail(string* x){
    return true;
}

bool L(string* x){
    return true;
}

bool A(string* x){
    return true;
}

string* split(string str){
    string del[100];
    int j=0;
    for(int i=0; i<str.length(); i++){
        if(str[i] == '-'){
            if(str[i+1] == '>'){
                del[j] = "->";
                i++;
                j++;
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
        else if(str[i] == char(32)){
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
    return(a);
}

int main(int argc, const char * argv[]) {
    string a;
    cout << "Enter a boolean expression to check: ";
    // user inputs a string
    cin >> a;
    string *b = split(a);
    int ans = B(b);
    if(ans == 1)
        cout << "true\n";
    else
        cout << "false\n";
    return 0;
}
