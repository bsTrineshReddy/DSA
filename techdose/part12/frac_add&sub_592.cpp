class Solution {
public:
    string fractionAddition(string expression) {
        istringstream in(expression);
    int A = 0, B = 1, a, b;
    char _;
    while (in >> a >> _ >> b) {
        cout<<a<<" "<<_<<" "<<b<<endl;
        A = A * b + a * B;
        B *= b;
        int g = abs(__gcd(A, B));
        A /= g;
        B /= g;
    }
    return to_string(A) + '/' + to_string(B);
        
    }
};

class Solution {
  public String fractionAddition(String expression) {
    List<Character> sign = new ArrayList<>();
    for (int i = 1; i < expression.length(); i++) {
      if (expression.charAt(i) == '+' || expression.charAt(i) == '-')
        sign.add(expression.charAt(i));
    }
    List<Integer> num = new ArrayList<>();
    List<Integer> den = new ArrayList<>();
    for (String sub : expression.split("\\+")) {
      for (String subsub : sub.split("-")) {
        if (subsub.length() > 0) {
          String[] fraction = subsub.split("/");
          num.add(Integer.parseInt(fraction[0]));
          den.add(Integer.parseInt(fraction[1]));
        }
      }
    }
    if (expression.charAt(0) == '-') num.set(0, -num.get(0));
    int lcm = 1;
    for (int x : den) {
      lcm = lcm_(lcm, x);
    }

    int res = lcm / den.get(0) * num.get(0);
    for (int i = 1; i < num.size(); i++) {
      if (sign.get(i - 1) == '+') res += lcm / den.get(i) * num.get(i);
      else res -= lcm / den.get(i) * num.get(i);
    }
    int g = gcd(Math.abs(res), Math.abs(lcm));
    return (res / g) + "/" + (lcm / g);
  }

  public int lcm_(int a, int b) {
    return a * b / gcd(a, b);
  }

  public int gcd(int a, int b) {
    while (b != 0) {
      int t = b;
      b = a % b;
      a = t;
    }
    return a;
  }
}


class Solution {
  public String fractionAddition(String expression) {
    List<Character> sign = new ArrayList<>();
    if (expression.charAt(0) != '-') sign.add('+');
    for (int i = 0; i < expression.length(); i++) {
      if (expression.charAt(i) == '+' || expression.charAt(i) == '-')
        sign.add(expression.charAt(i));
    }
    int prev_num = 0, prev_den = 1, i = 0;
    for (String sub : expression.split("(\\+)|(-)")) {
      if (sub.length() > 0) {
        String[] fraction = sub.split("/");
        int num = (Integer.parseInt(fraction[0]));
        int den = (Integer.parseInt(fraction[1]));
        int g = Math.abs(gcd(den, prev_den));
        if (sign.get(i++) == '+') prev_num = prev_num * den / g + num * prev_den / g;
        else prev_num = prev_num * den / g - num * prev_den / g;
        prev_den = den * prev_den / g;
        g = Math.abs(gcd(prev_den, prev_num));
        prev_num /= g;
        prev_den /= g;
      }
    }
    return prev_num + "/" + prev_den;
  }

  public int gcd(int a, int b) {
    while (b != 0) {
      int t = b;
      b = a % b;
      a = t;
    }
    return a;
  }
}