#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct {
    int top;
    char items[MAX];
} CharStack;

typedef struct {
    int top;
    int items[MAX];
} IntStack;

// Function to initialize the character stack
void initCharStack(CharStack *s) {
    s->top = -1;
}

// Function to initialize the integer stack
void initIntStack(IntStack *s) {
    s->top = -1;
}

// Function to check if the character stack is empty
int isCharStackEmpty(CharStack *s) {
    return s->top == -1;
}

// Function to check if the integer stack is empty
int isIntStackEmpty(IntStack *s) {
    return s->top == -1;
}

// Function to push an element onto the character stack
void pushChar(CharStack *s, char item) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = item;
    } else {
        printf("Character stack overflow\n");
    }
}

// Function to push an element onto the integer stack
void pushInt(IntStack *s, int item) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = item;
    } else {
        printf("Integer stack overflow\n");
    }
}

// Function to pop an element from the character stack
char popChar(CharStack *s) {
    if (!isCharStackEmpty(s)) {
        return s->items[(s->top)--];
    } else {
        printf("Character stack underflow\n");
        return '\0';
    }
}

// Function to pop an element from the integer stack
int popInt(IntStack *s) {
    if (!isIntStackEmpty(s)) {
        return s->items[(s->top)--];
    } else {
        printf("Integer stack underflow\n");
        return 0;
    }
}

// Function to get the top element of the character stack
char peekChar(CharStack *s) {
    if (!isCharStackEmpty(s)) {
        return s->items[s->top];
    }
    return '\0';
}

// Function to get the top element of the integer stack
int peekInt(IntStack *s) {
    if (!isIntStackEmpty(s)) {
        return s->items[s->top];
    }
    return 0;
}

// Function to check precedence of operators
int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to convert infix to postfix
void infixToPostfix(char *infix, char *postfix) {
    CharStack s;
    initCharStack(&s);
    int j = 0;

    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            pushChar(&s, ch);
        } else if (ch == ')') {
            while (!isCharStackEmpty(&s) && peekChar(&s) != '(') {
                postfix[j++] = popChar(&s);
            }
            popChar(&s); // Pop '('
        } else if (isOperator(ch)) {
            while (!isCharStackEmpty(&s) && precedence(peekChar(&s)) >= precedence(ch)) {
                postfix[j++] = popChar(&s);
            }
            pushChar(&s, ch);
        }
    }

    while (!isCharStackEmpty(&s)) {
        postfix[j++] = popChar(&s);
    }
    postfix[j] = '\0'; // Null terminate the postfix expression
}

// Function to evaluate a postfix expression
int evaluatePostfix(char *postfix) {
    IntStack s;
    initIntStack(&s);

    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];

        if (isdigit(ch)) {
            pushInt(&s, ch - '0'); // Convert char to int
        } else if (isOperator(ch)) {
            int right = popInt(&s);
            int left = popInt(&s);
            int result;

            switch (ch) {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                case '/':
                    if (right != 0) {
                        result = left / right;
                    } else {
                        printf("Division by zero error\n");
                        return 0;
                    }
                    break;
                case '^': result = (int)pow(left, right); break;
            }

            pushInt(&s, result);
        }
    }

    return popInt(&s);
}

int main() {
    char infix[MAX];
    char postfix[MAX];

    printf("Enter an infix expression (use single digit operands, type 'exit' to quit): \n");

    while (1) {
        printf("> ");
        fgets(infix, MAX, stdin);
        infix[strcspn(infix, "\n")] = 0; // Remove newline

        // Check for exit condition
        if (strcmp(infix, "exit") == 0) {
            break;
        }

        // Check for backspace
        if (strstr(infix, "<backspace>") != NULL) {
            // Remove last character
            infix[strlen(infix) - 1] = '\0'; // Remove the last character
            printf("Updated input after backspace: %s\n", infix);
        }

        infixToPostfix(infix, postfix);
        printf("Postfix expression: %s\n", postfix);

        int result = evaluatePostfix(postfix);
        printf("Evaluation result: %d\n", result);
    }

    return 0;
}
