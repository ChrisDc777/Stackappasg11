// Online C compiler to run C program online
#include<stdio.h>
#include<string.h> 
#include<limits.h>
#include<stdlib.h>
#include <ctype.h>
# define MAX 100
int top = -1;
char stack[MAX];

// checking if stack is full
int isFull() {
    return top == MAX - 1;
} 

// checking is stack is empty
int isEmpty() { 
    return top == -1; 
}

// Push function here, inserts value in stack and increments stack top by 1
void push(char item) {
    if (isFull()) 
        return; 
	top++;
	stack[top] = item;
}

// Function to remove an item from stack.  It decreases top by 1 
int pop() { 
    if (isEmpty()) 
        return INT_MIN; 
        
    // decrements top and returns what has been popped      
    return stack[top--]; 
} 

// Function to return the top from stack without removing it 
int peek(){ 
    if (isEmpty()) 
        return INT_MIN; 
    return stack[top]; 
} 

// A utility function to check if the given character is operand 
int checkIfOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'); 
} 

// Fucntion to compare precedence
// If we return larger value means higher precedence 
int precedence(char ch) 
{ 
    switch (ch) 
    { 
    case '+': 
    case '-': 
        return 1; 

    case '*': 
    case '/': 
        return 2; 

    case '^': 
        return 3; 
    } 
    return -1; 
} 

// The driver function for infix to postfix conversion 
int getPostfix(char* expression) 
{ 
    int i, j;

    for (i = 0, j = -1; expression[i]; ++i) 
    { 
        // Here we are checking is the character we scanned is operand or not
        // and this adding to to output. 
        if (checkIfOperand(expression[i])) 
            expression[++j] = expression[i]; 

        // Here, if we scan character ‘(‘, we need push it to the stack. 
        else if (expression[i] == '(') 
            push(expression[i]); 

        // Here, if we scan character is an ‘)’, we need to pop and print from the stack  
        // do this until an ‘(‘ is encountered in the stack. 
        else if (expression[i] == ')') 
        { 
            while (!isEmpty(stack) && peek(stack) != '(') 
                expression[++j] = pop(stack); 
            if (!isEmpty(stack) && peek(stack) != '(') 
                return -1; // invalid expression              
            else
                pop(stack); 
        } 
        else // if an opertor
        { 
            while (!isEmpty(stack) && precedence(expression[i]) <= precedence(peek(stack))) 
                expression[++j] = pop(stack); 
            push(expression[i]); 
        } 

    } 

    // Once all inital expression characters are traversed
    // adding all left elements from stack to exp
    while (!isEmpty(stack)) 
        expression[++j] = pop(stack); 

    expression[++j] = '\0'; 
    
}

void reverse(char *exp){

    int size = strlen(exp);
    int j = size, i=0;
    char temp[size];

    temp[j--]='\0';
    while(exp[i]!='\0')
    {
        temp[j] = exp[i];
        j--;
        i++;
    }
    strcpy(exp,temp);
}
void brackets(char* exp){
    int i = 0;
    while(exp[i]!='\0')
    {
        if(exp[i]=='(')
            exp[i]=')';
        else if(exp[i]==')')
            exp[i]='(';
        i++;
    }
}
void InfixtoPrefix(char *exp){

    int size = strlen(exp);

    // reverse string
    reverse(exp);
    //change brackets
    brackets(exp);
    //get postfix
    getPostfix(exp);
    // reverse string again
    reverse(exp);
}

int covertInfixToPostfix(char* expression) 
{ 
    int i, j;

    for (i = 0, j = -1; expression[i]; ++i) 
    { 
        // Here we are checking is the character we scanned is operand or not
        // and this adding to to output
        if (checkIfOperand(expression[i])) 
            expression[++j] = expression[i]; 

        // Here, if we scan character ‘(‘, we need push it to the stack. 
        else if (expression[i] == '(') 
            push(expression[i]); 

        // Here, if we scan character is an ‘)’, we need to pop and print from the stack  
        // do this until an ‘(‘ is encountered in the stack. 
        else if (expression[i] == ')') 
        { 
            while (!isEmpty() && peek() != '(') 
                expression[++j] = pop(); 
            if (!isEmpty() && peek() != '(') 
                return -1; // invalid expression              
            else
                pop(); 
        }
        else // if an opertor
        { 
            while (!isEmpty() && precedence(expression[i]) <= precedence(peek())) 
                expression[++j] = pop(); 
            push(expression[i]); 
        } 

    } 

    // Once all inital expression characters are traversed
    // adding all left elements from stack to exp
    while (!isEmpty()) 
        expression[++j] = pop(); 

    expression[++j] = '\0'; 
    printf( "%s", expression); 
} 

void EvalPostfix(char postfix[])
{

    int i;
    char ch;
    int val;
    int A, B;

    /* evaluate postfix expression */
    for (i = 0; postfix[i] != ')'; i++) {
        ch = postfix[i];
        if (isdigit(ch)) {
            /* we saw an operand,push the digit onto stack
ch - '0' is used for getting digit rather than ASCII code of digit */
            push(ch - '0');
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            /* we saw an operator
* pop top element A and next-to-top elemnet B
* from stack and compute B operator A
*/
            A = pop();
            B = pop();

            switch (ch) /* ch is an operator */
            {
            case '*':
                val = B * A;
                break;

            case '/':
                val = B / A;
                break;

            case '+':
                val = B + A;
                break;

            case '-':
                val = B - A;
                break;
            }

            /* push the value obtained above onto the stack */
            push(val);
        }
    }
    printf("Result of expression evaluation : %d \n", pop());
}
int main()
{   
    printf("The infix is: ");

    char expression[] = "((a/b)+c)-(d+(e*f))"; 
    printf("%s\n",expression);
    InfixtoPrefix(expression); 

    printf("The prefix is: ");
    printf("%s\n",expression);
    
    printf("\nThe infix is: ");
    char expression1[] = "((a+(b*c))-d)";
    printf("%s\n",expression1);
    printf("The postfix is: ");
    covertInfixToPostfix(expression1);
    
    char postfix[] = "456*+)";
    printf("\n\nThe postfix is: ");
    printf("%s\n",postfix);
    EvalPostfix(postfix);
    
    //Well formedness of parenthesis 
    printf("\nThe input is: ");
    char a[120] = "{()}[]",t;
    printf("%s\n",a);
    int i,f=1;
    for(i=0;i<strlen(a);i++)
    {
        if(a[i]=="("||a[i]=="{"||a[i]=="[")
            push(a[i]);
        if(a[i]==")"||a[i]=="}"||a[i]=="]")
        {
            if(top==-1)
            f=0;
        
            else
            {
                t=pop();
                if(a[i]==")"&&(t=="["||t=="{"))
                f=0;
                if(a[i]=="}"&&(t=="("||t=="["))
                f=0;
                if(a[i]=="]"&&(t=="{"||t=="("))
                f=0;
            }
        }   
    }
    if(top>=0)
    f=0;
    if(f==0)
    printf("It's Unbalanced\n");
    else
    printf("It's Balanced\n");

    return 0; 
}
