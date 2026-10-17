#include<cstdio>
#include<cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

const long long M=1000000007;

bool isoperator(char a)
{
    return a=='+'||a=='-'||a=='*'||a=='^';
}

//优先级
int priority(char op)
{
    if(op=='^')return 3;
    if(op=='*')return 2;
    if(op=='+'||op=='-')return 1;
    return 0;
}

//多项式类
class polynomial
{
public:
    long long* coefficient;
    int degree;

    //构造和析构函数
    int getdegree()
    {
        return degree;
    }

    polynomial():degree(0)
    {
        coefficient=new long long[1];
        coefficient[0]=0;
    }

    polynomial(long long c):degree(0)
    {
        coefficient=new long long[1];
        coefficient[0]=(c%M+M)%M;
    }

    polynomial(int d,long long c):degree(d)
    {
        coefficient=new long long[d+1]();
        coefficient[degree]=(c%M+M)%M;
    }

    polynomial(const polynomial& other)
    {
        degree=other.degree;
        coefficient=new long long[degree+1];
        for(int i=0;i<=degree;i++)
        {
            coefficient[i]=other.coefficient[i];
        }
    }

    ~polynomial() 
    {
        delete[] coefficient;
    }

    //去除高位0
    void trim()
    {
        while(degree>0&&coefficient[degree]==0)degree--;

        long long *newcoefficient=new long long[degree+1];
        for(int i=0;i<=degree;i++)
        {
            newcoefficient[i]=coefficient[i];
        }
        delete[] coefficient;
        coefficient=newcoefficient;
    }

    //扩容最高次（方便计算）
    void expand(int d)
    {
        if(d<=degree)return ;
        long long *newcoefficient=new long long[d+1]();
        for(int i=0;i<=degree;i++)
        {
            newcoefficient[i]=coefficient[i];
        }
        delete[] coefficient;
        coefficient=newcoefficient;
        degree=d;
    }

    //各种计算
    polynomial operator+(const polynomial& other) const
    {
        polynomial result;
        int newd=max(degree,other.degree);
        result.expand(newd);
        for(int i=0;i<=newd;i++)
        {
            long long c1,c2;
            if(i<=degree)c1=coefficient[i];
            else c1=0;
            if(i<=other.degree)c2=other.coefficient[i];
            else c2=0;
            result.coefficient[i]=(c1+c2+M)%M;
        }
        result.trim();
        return result;
    }

    polynomial operator-(const polynomial& other) const
    {
        polynomial result;
        int newd=max(degree,other.degree);
        result.expand(newd);
        for(int i=0;i<=newd;i++)
        {
            long long c1,c2;
            if(i<=degree)c1=coefficient[i];
            else c1=0;
            if(i<=other.degree)c2=other.coefficient[i];
            else c2=0;
            result.coefficient[i]=(c1-c2+M)%M;
        }
        result.trim();
        return result;
    }

    polynomial operator*(const polynomial& other) const
    {
        polynomial result;
        int newd=degree+other.degree;
        result.expand(newd);
        for(int i=0;i<=degree;i++)
        {
            for(int j=0;j<=other.degree;j++)
            {
                result.coefficient[i+j]=(result.coefficient[i+j]+coefficient[i]*other.coefficient[j])%M;
            }
        }
        result.trim();
        return result;
    }

    polynomial pow(int k) const
    {
        if(k==1)return *this;
        polynomial result(1);
        polynomial base=*this;
        for(int i=1;i<=k;i++)
        {
            result=result*base;
        }
        result.trim();
        return result;
    }

    polynomial& operator=(const polynomial& other)
    {
        if(this==&other)return *this;
        delete[] coefficient;

        degree=other.degree;
        coefficient=new long long[degree+1];
        for(int i=0;i<=degree;i++)
        {
            coefficient[i]=other.coefficient[i];
        }
        return *this;
    }
};

//简化定义的栈
template <typename T>class stack
{
public:
    T* data;
    int top;
    int capacity;

    stack():top(-1),capacity(100)
    {
        data=new T[capacity];
    }

    ~stack()
    {
        delete[] data;
    }

    //扩容
    void expand()
    {
        capacity*=2;
        T* newdata=new T[capacity];
        for(int i=0;i<=top;i++)
        {
            newdata[i]=data[i];
        }
        delete[] data;
        data=newdata; 
    }

    //增加新元素
    void push(const T& s)
    {
        if(top+1>=capacity)expand();
        top++;
        data[top]=s;
    }

    //弹出
    void pop()
    {
        if(top>=0)top--;
    }

    //获取顶部
    T& gettop()
    {
        return data[top];
    }

    bool isempty() {
        return top == -1;
    }
};

//定义令牌组
class Tokens
{
public:
    string* tokens;
    int size;
    int capacity;
    Tokens():size(0),capacity(100)
    {
        tokens=new string[capacity];
    }

    ~Tokens()
    {
        delete[] tokens;
    }

    void expand() {
        capacity *= 2;
        string* newtokens = new string[capacity];
        for (int i = 0; i < size; ++i) 
        {
            newtokens[i] = tokens[i];
        }
        delete[] tokens;
        tokens = newtokens;
    }

    void add(const string& s)
    {
        if(size>=capacity)expand();
        tokens[size++]=s;
    }

    void insert(int index,const string& s)
    {
        if(size>=capacity)expand();
        for(int i=size;i>index;i--)
        {
            tokens[i]=tokens[i-1];
        }
        tokens[index]=s;
        size++;
    }
};

//处理为标准的令牌组
Tokens process(const string& s)
{
    Tokens tokens;
    int n=s.size();
    int i=0;//指针

    while(i<n)
    {
        //处理运算符
        if(isoperator(s[i])||s[i]=='('||s[i]==')')
        {
            tokens.add(string(1,s[i]));
            i++;
            continue;
        }

        //处理数字
        if(s[i]>='0'&&s[i]<='9')
        {
            int j=i;
            while(j<n&&s[j]>='0'&&s[j]<='9')j++;
            tokens.add(s.substr(i,j-i));
            i=j;
            continue;
        }

        //处理x
        if(s[i]=='x')
        {
            tokens.add("x");
            i++;
            continue;
        }
    }

    //补齐缺少的*
    int idx=0;
    while(idx<tokens.size-1)
    {
        string current=tokens.tokens[idx];
        string next=tokens.tokens[idx+1];
        bool panduan=0;

        bool currentIsNum=(isdigit(current[0]) || current == ")");
        bool nextIsx=(next == "(" || next == "x");

        if(currentIsNum&&nextIsx)panduan=1;

        if(current=="x" && next=="(")panduan=1;

        if(panduan)
        {
            tokens.insert(idx+1,"*");
            idx++;
        }

        idx++;
    }
    return tokens;
}

//中缀改后缀
Tokens trans(const Tokens& s)
{
    Tokens postfix;
    stack<string> opstack;

    for(int i=0;i<s.size;i++)
    {
        string token=s.tokens[i];

        if(token=="(")
        {
            opstack.push(token);
            continue;
        }

        if(token==")")
        {
            while(!opstack.isempty()&&opstack.gettop()!="(")
            {
                postfix.add(opstack.gettop());
                opstack.pop();
            }
            opstack.pop(); 
            continue;
        }

        if(isoperator(token[0]))
        {
            while(!opstack.isempty())
            {
                string topop=opstack.gettop();
                if(topop=="(")break;
                bool panduan=0;
                if(priority(topop[0])>priority(token[0]))panduan=1;
                else if(priority(topop[0])==priority(token[0]))
                {
                    panduan=1;
                }
                if(panduan)
                {
                    postfix.add(topop);
                    opstack.pop();
                }
                else break;
            }
            opstack.push(token);
            continue;
        }
        postfix.add(token);
    }
    while(!opstack.isempty())
    {
        postfix.add(opstack.gettop());
        opstack.pop();
    }
    return postfix;
}

//计算求值
polynomial calculate(const Tokens& postfix)
{
    stack<polynomial> polystack;

    for(int i=0;i<postfix.size;i++)
    {
        string token=postfix.tokens[i];
        if(token=="x")
        {
            polystack.push(polynomial(1,1));
        }

        else if(token[0]>='0'&&token[0]<='9')
        {
            int lengh=token.size();
            long long num=0;
            for(int j = 0; j < lengh; j++) 
            {
                num = num * 10 + (token[j] - '0');
            }
            polystack.push(polynomial(num));
        }

        else 
        {
            polynomial a=polystack.gettop();
            polystack.pop();
            polynomial b=polystack.gettop();
            polystack.pop();

            polynomial result;
            switch(token[0])
            {
                case '+':result=a + b ;break;
                case '-':result=b - a ;break;
                case '*':result=a * b ;break;
                case '^':result=b.pow(a.coefficient[0]);break;
            }
            polystack.push(result);
        }
    }

    return polystack.gettop();
}

int main()
{
    string s;
    getline(cin,s);

    Tokens tokens=process(s);

    Tokens posttokens=trans(tokens);

    polynomial poly=calculate(posttokens);
    poly.trim();

    for(int i=poly.degree;i>=0;i--)
    {
        printf("%lld ",poly.coefficient[i]);
    }
    printf("\n");
    
    return 0;
}