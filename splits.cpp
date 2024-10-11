#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int find_end_bracket(int start, string& expr){
        int count = 1;

        int i = start+1;

        while(i<expr.size()){
            if(expr[i] == ')'){
                count--;

                if(count == 0){
                    return i;
                }
            }
            else if(expr[i] == '('){
                count++;
            }

            i++;
        }

        return -1;
    }

    bool is_expression(string& s, int i){
        return s[i] == '(';
    }

    string get_expression(string& s){
        int n = s.size();

        string expr = s.substr(1, n-2);

        return expr;
    }


    vector<string> parse_string(string& expr){
        vector<string> splits;
        
        int i = 0, prev = 0;

        while(true){
            if(is_expression(expr, i)){
                int end = find_end_bracket(i, expr);

                splits.push_back(expr.substr(prev, end-prev+1));

                i = end+1;
            }
            else{
                while(i< expr.size() && expr[i] != ' '){
                    i++;
                }

                splits.push_back(expr.substr(prev, i-prev));
            }

            while(i< expr.size() && expr[i] == ' '){
                i++;
            }

            if(i >= expr.size()){
                break;
            }

            prev = i;
        }

        return splits;
    }

    bool is_number(string& s){
        if (s.empty()) return false;
        std::size_t start = (s[0] == '+' || s[0] == '-') ? 1 : 0;
        if (start == s.size()) return false; // Only '+' or '-' without digits
        for (std::size_t i = start; i < s.size(); i++) {
            if (!std::isdigit(s[i])) return false;
        }
        return true;
    }

    int dfs(string expr, unordered_map<string,int> values){
        if(is_expression(expr, 0)){
            expr = get_expression(expr);
        }

        //first find the first space
        vector<string> exprs = parse_string(expr);

        if(exprs[0] == "let"){
            int n = exprs.size();

            for(int i=1;i<n-1;i+=2){
                values[exprs[i]] = dfs(exprs[i+1], values);
            }

            return dfs(exprs[n-1], values);
        }
        else if(exprs[0] == "add"){
            int l = dfs(exprs[1], values);
            int r = dfs(exprs[2], values);

            return l+r;
        }
        else if(exprs[0] == "mult"){
            int l = dfs(exprs[1], values);
            int r = dfs(exprs[2], values);

            return l*r;
        }
        else if(is_number(exprs[0])){
            return stoi(exprs[0]);
        }
        else{
            return values[exprs[0]];
        }

    }

    int evaluate(string s) {
        unordered_map<string,int> values;

        return dfs(s, values);
    }
};

int main(){
    return 0;
}