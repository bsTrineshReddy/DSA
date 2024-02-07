// method1: techdose
class Solution {
    unordered_map<string,bool> mem;
    bool check(string s1,string s2,string s3,int len1,int len2,int len3,int p1,int p2,int p3)
    {
        if(p3==len3)
            return (p1==len1 and p2==len2)?true:false;
        
        string key = to_string(p1)+"*"+to_string(p2)+"*"+to_string(p3);
        if(mem.find(key)!=mem.end())
            return mem[key];
        
        if(p1==len1)
            return mem[key] = s2[p2]==s3[p3]? check(s1,s2,s3,len1,len2,len3,p1,p2+1,p3+1):false;
        if(p2==len2)
            return mem[key] = s1[p1]==s3[p3]? check(s1,s2,s3,len1,len2,len3,p1+1,p2,p3+1):false;
        
        bool one = false,two = false;
        if(s1[p1]==s3[p3])
            one = check(s1,s2,s3,len1,len2,len3,p1+1,p2,p3+1);
        if(s2[p2]==s3[p3])
            two = check(s1,s2,s3,len1,len2,len3,p1,p2+1,p3+1);
        
        return mem[key] = one or two;
    }
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.length();
        int len2 = s2.length();
        int len3 = s3.length();
        if(len3 != len1+len2)
            return false;
        
        return check(s1,s2,s3,len1,len2,len3,0,0,0);
    }
};

//JAVA CODE
class Solution {
    private boolean isInterleaving(String a, String b, String c, Map<String, Boolean> map){
        if(a.length() + b.length() != c.length()) return false;
        if(a.isEmpty() && b.isEmpty() && c.isEmpty()) return true;
        String key = a + "->" + b + "->" + c;
        boolean resultOne = false;
        boolean resultTwo = false;
        if(!map.containsKey(key)){
            if(!a.isEmpty() && a.charAt(0) == c.charAt(0)) resultOne = isInterleaving(a.substring(1), b, c.substring(1), map);
            if(!b.isEmpty() && b.charAt(0) == c.charAt(0)) resultTwo = isInterleaving(a, b.substring(1), c.substring(1), map);
            map.put(key, resultOne || resultTwo);
        }
        return map.get(key);
    }
    public boolean isInterleave(String s1, String s2, String s3) {
        return isInterleaving(s1, s2, s3, new HashMap<>());
    }
}