/**
Minh họa stack để định giá biểu thức dạng hậu tố
Toán tử và toán hạng chỉ có 1 chữ cái 
*/
#include <iostream>
#include <stack>
#include <cmath>
#include <cstring>
using namespace std;
// hàm kiểm tra xem có phải toán tử
// hàm trả về 1 nếu là toán tử
int isOperator(char op)
{
  if ((op == '+') || (op == '-') ||
      (op == '*') || (op == '%') || (op == '/') || (op == '^'))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

 

// Hàm tính giá trị của toán tử
int compute(int left, int right, char op) 
{
  int value;
  switch (op)
    {
    case '+':
      value = left + right;
      break;
    case '-':
      value = left - right;
      break;
    case '*':
      value = left * right;
      break;
    case '%':
      value = left % right;
      break;
    case '/':
      value = left / right;
      break;
    case '^':
      value = pow (left, right);
      break;
    }
  return value;
}

 

// Hàm tính và trả về giá trị biểu thức eq
void tinhGiatriBieuThucHauTo(const char *eq)
{
    int left, right, expValue;
    char ch;

 

    stack<int> stack;
    
    for(int i=0;i<strlen(eq);i++)
    {
        // nếu là toán hạng 
        if(isOperator(eq[i])==0){
              stack.push(eq[i]-'0');                  
        }
        else // là toán tử
        {
            right = stack.top();
            stack.pop();
            left = stack.top();
            stack.pop();
            
            expValue=compute(left,right,eq[i]);
            stack.push(expValue);   
         }                  
    }
    expValue = stack.top();
    cout<<expValue<<endl;
}

 

int main()
{
    tinhGiatriBieuThucHauTo("52+6*7/9-");
    return 0;
}