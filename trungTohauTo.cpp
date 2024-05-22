/*Minh họa chuyển biểu thức dạng trung tố sang dạng hâu tố
Toán tử và toán hạng chỉ gồm 1 ký tự*/
#include <iostream>
#include <stack>
#include<cstring>
using namespace std;

 

//Hàm kiểm tra xem có phải là toán tử
// hàm trả về 1 nếu ký tự op đúng là toán tử và 0 nếu ngược lại
int isOperator(char op)
{
    if ((op == '+') || (op == '-') || 
           (op == '*' )|| (op == '%' )|| 
           (op == '/' )|| (op == '^' )){
               return 1;
           }    
    return 0;  
}

 

/* Ham tra ve do uu tien cua toan tử
 chỉ xét 1 số toán tử cơ bản như + - * / % và ^
*/
int priority(char op)
{
    if((op == '+') || (op == '-')) {
        return 4;
    }
    if((op == '*' )|| (op == '%' )||(op == '/' )) {
        return 5;
    }
    if(op == '^'){
        return 6;
    }
    
    return 0;
}

 

// hàm chuyển biểu thức dạng trung tố sang dạng hậu tố
void chuyenSangHauTo(const char *eq)
{
    char ch;
    char *retVal=(char*)calloc(sizeof(char),strlen(eq)+1);
        
    stack<char> myStack;
    int j=0;
    for(int i=0;i<strlen(eq); i++)
    {
        if((eq[i]!='(')&&(eq[i]!=')')){
            if(isOperator(eq[i])==0)//toan hang
            {
                retVal[j]=eq[i];
                j++;
            }
            else //toan tu
            {
                if(myStack.empty() || myStack.top()=='(' || 
                     priority(eq[i])==6 ||priority(eq[i])>priority(myStack.top())) 
                     {
                         myStack.push(eq[i]);
                     }
                else 
                {
                    ch = myStack.top(); 
                    while(myStack.empty() !=true && priority(eq[i]) <= priority(ch)) {
                        retVal[j]=ch;
                        myStack.pop();
                        j++;
                        if(myStack.empty()!=true) ch = myStack.top(); 
                    }
                    myStack.push(eq[i]);
                }  
            }
        }           
        else //dau ( hoac )
        {
            if(eq[i]=='(') myStack.push(eq[i]);
            else 
            {    
                ch=myStack.top();
                myStack.pop();
                while(ch!='(')
                {
                    retVal[j]=ch;
                    j++;
                    ch=myStack.top();  
                    myStack.pop();        
                }
            }
        }                                                                 
    }
    
    while(!myStack.empty()) //lay not cac toan tu con lai
    {
         ch=myStack.top();  
         myStack.pop();  
         retVal[j]=ch;
         j++;
    }
    
    // gán ký tự cuối xâu
    retVal[j]='\0';

 

    printf("%s sang Hauto: %s\n",eq,retVal);
}

 

// test code
int main()
{
    char ep[250];
    fgets(ep, sizeof(ep), stdin);
    ep[strcspn(ep, "\r\n")] = 0;
    chuyenSangHauTo(ep);
    return 0;
}