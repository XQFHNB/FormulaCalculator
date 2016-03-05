#include <iostream>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <string >
#include <cstring>
using namespace std;
const int N=1000;

//ȷ�����ȼ�
char precede(char c1,char c2) {
    if(c1=='+'||c1=='-') {
        if(c2=='*'||c2=='/')
            return '<';
        else
            return '>';//+-ͬ����˳���������ִ��˳�����Ⱥ�
    }
    if(c1=='*'||c1=='/') {
        return '>';
    }
}


//��Ԫ����
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
            //������ϵ�����������ջ
            if(str[i]=='('||str[i]=='['||str[i]=='{') {
                op.push(str[i]);
            }
            //��������ϵ�����ַ�ջ��ѹ������ջ�������ַ�ջ��ֱ��������Ӧ����ϵ��
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
            //����������
            if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/') {
                    //���ַ�ջΪ�գ���ֱ�����ַ�ջ
                if(op.empty()) {
                    op.push(str[i]);
                }
                //���ַ�ջ��Ϊ����ջ��Ϊ��ϵ�У����ַ�ѹ�������ջ
                else if((!op.empty()&&op.top()=='(')||(!op.empty()&&op.top()=='[')||(!op.empty()&&op.top()=='{')) {
                    op.push(str[i]);
                } else {
                    oper=precede(op.top(),str[i]);
                    //�������������ȼ��ϸ�
                    if(oper=='<') {
                        op.push(str[i]);
                    } else {
                        //����������ջ������������ջ��Ϊ�գ��������ջ���������Ƚ�
                        while((oper=precede(op.top(),str[i]))=='>') {
                            num.push(op.top());
                            op.pop();
                            //ջ�գ���ֹͣ�Ƚ�
                            if(op.empty()) {
                                break;
                            }
                        }
                        op.push(str[i]);
                    }
                }

            }
        }
        //����������ջ�����в�������ѹ������ջ��
        while(!op.empty()) {
            num.push(op.top());
            op.pop();
        }
        //����˳��
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
        //����ת���ɹ��ı��ʽ���
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

