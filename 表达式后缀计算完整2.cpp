#include <iostream>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <string >
#include <cstring>
using namespace std;
const int N=1000;

//确定优先级
char precede(char c1,char c2) {
    if(c1=='+'||c1=='-') {
        if(c2=='*'||c2=='/')
            return '<';
        else
            return '>';//+-同级则按顺序来，因此执行顺序有先后
    }
    if(c1=='*'||c1=='/') {
        return '>';
    }
}


//二元运算
double comput(double a,char c,double b) {
    switch(c) {
    case '+':
        return a+b;
        break;
    case '-':
        return a-b;
        break;
    case '*':
        return a*b;
        break;
    case '/':
        return a/b;
        break;
    }
}
int main() {
    cout<<"\n*******************Welcome to personal formula calculator*********************\n";
    cout<<endl;
    cout<<endl;
    string str2;
    cout<<"Are you ready?(Enter yes or no):   ";
    cin>>str2;
    while(str2=="yes") {
        stack<char> op;
        stack <char> num;
        stack<char>num1;
        string str;
        char oper;
        cout<<"\nInput the formula:                 ";
        cin>>str;
        for(int i=0; i<str.length(); i++) {
            if(isdigit(str[i])) {
                num.push(str[i]);
            }
            //若是右系列则入操作符栈
            if(str[i]=='('||str[i]=='['||str[i]=='{') {
                op.push(str[i]);
            }
            //若遇到左系列则将字符栈顶压入数字栈，弹出字符栈顶直至遇到对应的右系列
            if(str[i]==')') {
                while(op.top()!='(') {
                    num.push(op.top());
                    op.pop();
                }
                op.pop();
            }
            if(str[i]=='}') {
                while(op.top()!='{') {
                    num.push(op.top());
                    op.pop();
                }
                op.pop();
            }
            if(str[i]==']') {
                while(op.top()!='[') {
                    num.push(op.top());
                    op.pop();
                }
                op.pop();
            }
            //遇到操作符
            if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/') {
                    //若字符栈为空，则直接入字符栈
                if(op.empty()) {
                    op.push(str[i]);
                }
                //若字符栈不为空且栈顶为右系列，则将字符压入操作符栈
                else if((!op.empty()&&op.top()=='(')||(!op.empty()&&op.top()=='[')||(!op.empty()&&op.top()=='{')) {
                    op.push(str[i]);
                } else {
                    oper=precede(op.top(),str[i]);
                    //所遇操作符优先级较高
                    if(oper=='<') {
                        op.push(str[i]);
                    } else {
                        //弹出操作符栈顶后，若操作符栈不为空，则继续与栈顶操作符比较
                        while((oper=precede(op.top(),str[i]))=='>') {
                            num.push(op.top());
                            op.pop();
                            //栈空，则停止比较
                            if(op.empty()) {
                                break;
                            }
                        }
                        op.push(str[i]);
                    }
                }

            }
        }
        //弹出操作符栈的所有操作符并压入数字栈中
        while(!op.empty()) {
            num.push(op.top());
            op.pop();
        }
        //调整顺序
        while(!num.empty()) {
            num1.push(num.top());
            num.pop();
        }
        char str1[N];
        int i=0;
        cout<<"\nThe concerted formula:             ";
        while(!num1.empty()) {
            cout<<num1.top();
            str1[i++]=num1.top();
            num1.pop();
        }
        str1[i]='\0';
        cout<<endl;
        //计算转换成功的表达式结果
        stack<double>num2;
        for(int i=0; i<strlen(str1); i++) {
            double x,y;
            if(isdigit(str1[i])) {
                double z=str1[i]-'0';
                num2.push(z);
            } else {
                x=num2.top(),num2.pop();
                y=num2.top(),num2.pop();
                //cout<<"compute:"<<comput(y,str1[i],x)<<endl;
                num2.push(comput(y,str1[i],x));
            }

        }
        cout<<"\nThe result is:                     "<<num2.top()<<endl;
        cout<<"********************************************************************************"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"Are you ready?(Enter Yes or No):   ";
        cin>>str2;
    }
    return 0;
}

