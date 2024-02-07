// best intutuive solution
class Solution {
public:
    string solveEquation(string equation) {
        int i =0;
        int para=0, xpara=0;
        int flag = 1;
        while(i<equation.size())
        {
            int sign = 1;
            int temp = 0;
            if(equation[i] == '=') 
            {
                flag = -1;
                i++;
            }
            if(equation[i] == '-') 
            {
                sign = -1; 
                i++;
            }
            if(equation[i] == '+') 
            {
                sign = 1;
                i++;
            }
            
            if(isdigit(equation[i]))
            {
                while(i<equation.size() && isdigit(equation[i]))
                {
                    temp = temp*10 + equation[i]-'0';
                    i++;
                }
                if(i< equation.size() && equation[i] == 'x')
                {
                    xpara += flag*sign*temp;
                    i++;
                } 
                else 
                    para += flag*sign*temp;
            } 
            else //x
            {
                xpara += flag*sign;
                i++;
            }
            
        }
        string res;
        //cout<<para<<", "<<xpara<<endl;
        if(para == 0 && xpara == 0) 
            res = "Infinite solutions";
        else if(xpara == 0) 
            res = "No solution";
        else
            res = "x="+to_string(para/xpara*-1);
        return res;
    }
};
------------------------------
// leetcode sol:1
class Solution {
    vector<string> breakIt(string s) {
        vector<string> res;
        string r = "";

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '+' || s[i] == '-') {
                if (!r.empty())
                    res.push_back(r);
                r = s[i];
            } else {
                r += s[i];
            }
        }

        res.push_back(r);
        return res;
    }

    vector<string> splitEquation(string s, char delimiter) {
        vector<string> tokens;
        stringstream ss(s);
        string token;

        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }

        return tokens;
    }

    string coeff(string x) {
        if (x.length() > 1 && x[x.length() - 2] >= '0' && x[x.length() - 2] <= '9')
            return x.replace(x.find('x'), 1, "");
        return x.replace(x.find('x'), 1, "1");
    }

public:
    string solveEquation(string equation) {

        vector<string> lr = splitEquation(equation, '=');
        int lhs = 0, rhs = 0;

        for (const string& x : breakIt(lr[0])) {
            if (x.find('x') != string::npos) {
                lhs += stoi(coeff(x));
            } else {
                rhs -= stoi(x);
            }
        }

        for (const string& x : breakIt(lr[1])) {
            if (x.find('x') != string::npos) {
                lhs -= stoi(coeff(x));
            } else {
                rhs += stoi(x);
            }
        }

        if (lhs == 0) {
            if (rhs == 0)
                return "Infinite solutions";
            else
                return "No solution";
        }

        return "x=" + to_string(rhs / lhs);
    }
};
----------------------
// regex solution from leetcode editorial
