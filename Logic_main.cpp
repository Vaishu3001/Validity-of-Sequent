#include <iostream>
#include <string>

using namespace std;

/// @brief function used to reverse a string, used since input to converting infix to prefix needs to be reversed first, output must also be reversed in the end.
/// @param str any string that is to be reversed
/// @return reversed string
string reverse(string& str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++){
        swap(str[i], str[n - i - 1]);
    }
    return str;
}



/// @brief function to push an element onto the stack.
/// @param stack stack into which operators including brackets are pushed and popped for during infix to prefix conversion.
/// @param a character to be pushed into the stack
/// @return returns the stack itself since it needs to be updated after each time the push operation is performed
string push(string &stack,char a){
    stack += a;
    return stack;
}



/// @brief function to pop an element out of the stack.
/// @param stack stack into which operators including brackets are pushed and popped for during infix to prefix conversion.
/// @return returns the character that is popped from the stack.
char pop(string &stack){
    char a = stack[stack.length()-1];
    stack.pop_back();
    return a;
}

/// @brief Checks if the given character ch is a logical operator or brackets
/// @param ch The character to be checked
/// @return true if ch is an Operator or Brackets [*,+,>,~,(,)] and vice versa
bool isOperator(char ch){
	if(ch=='*' || ch=='+' || ch=='>'|| ch=='~' || ch=='(' || ch==')' )
		return true;
	else
		return false;
}


/// @brief Given an operator o, this function defines the precedence of the logical operator.
/// @param o any logical operator o.
/// @return returns the precedence of the logical operators in an increasing range of 0-4.
/// @warning Brackets must be included too, if they are not included, the function might not know the precedence of the operators and the appropriate action is not performed.
int precedence(char o){

    switch (o){
    case '~':
        return 1;
        break;
    case '+':
        return 2;
        break;
    case '*':
        return 3;
        break;
    case '>':
        return 4;
    case '#':
        case ')':
        case '(':
        return 0;
        break;
    default:
        return -1;
    }
}



/// @brief This is the function to convert the infix to the prefix expression.
/// @param infix An infix expression which is to be reversed.
/// @return A prefix expression which is already reversed and is obtained in the final required.
string infixToPrefix(string infix){
	string stack ="#";
	string rev_infix = reverse(infix);
	string prefix ="";
    //length of string.
    int n = rev_infix.size();
    //variable that is encountered upon traversal through the reverse of the infix expression.
    char symbol;
    // //defining the top (0th) element of the stack as # to ensure that we stop when we reach the bottom of the stack. Basically a buffer element to check if we have reached the bottom.
    // stack[++top]='#';
    for (int i = 0; i < n; i++){
        symbol = rev_infix[i];
        //if the symbol is not an operator, assign the element directly to the reverse of the prefix expression.
        if (!isOperator(symbol)){
            prefix += symbol;

        }
        else{
            //if the operator is a closing bracket, push it into the stack.
            if (symbol == ')'){
                push(stack,symbol);
            }
            //if the operator is an opening bracket, start looping.
            else if (symbol == '('){
                //As long as the top of the stack is not a closing bracket (it is an operator), in which case pop the operator from the stack and assign it to the reverse of the prefix expression.
                while (stack[stack.length()-1] != ')'){
                    prefix += pop(stack);

                }
                //pop the opening bracket from the stack.
                pop(stack);
            }
            else{
                //if the precedence of the element on top of the stack is less than the precedence of the current symbol, push it onto the stack.
                if (precedence(stack[stack.length()-1]) <= precedence(symbol)){
                    push(stack,symbol);
                }
                else{
                    //as long as the precedence of the element on top of the stack is greater than the precedence of the current symbol, pop the operator on top of the stack and assign it to the reverse of the prefix expression.
                    while (precedence(stack[stack.length()-1]) >= precedence(symbol)){
                        prefix += pop(stack);

                    }
                    //Push the symbol into the stack once it is of highest precedence.
                    push(stack,symbol);
                }
            }
        }

    }
     //In the end, As long as the top of the stack is not the bottom most buffer element, pop it onto the reverse of the prefix expression.
    while (stack[stack.length()-1] != '#'){
        prefix += pop(stack);

    }
    return reverse(prefix);
}

/// @brief Defining structure Node to create nodes for the binary tree implementation
struct Node
{	
	/// @brief Data block to store single char representing actual atom or operator
	char data;
	/// @brief Expects the memory to the root node of left subtree. NULL if no left subtree defined
	struct Node* left;
	/// @brief Expects the memory to the root node of right subtree. NULL if no right subtree defined
	struct Node* right;

	Node(char val){
		data=val;
		left = NULL;
		right = NULL;
	}
};


/// @brief Make Binary Parse Tree using Logical Expression in Prefix(Polish Notation)
///
/// Recursive function to convert string exp in prefix into a binary tree. Fills in tree by filling left subtree first, then right subtree
/// @param token call by reference int token to keep track of character from exp to be inserted into resp. node
/// @param exp Logical expression in the prefix notation @see infixToPrefix.cpp
/// @return The root node to the binary parse tree completely filled
Node* makeExpressionTree(int &token,string exp)
{
	if(token==(exp.length()))
	{
			return NULL;
	}
	struct Node* node = new Node(exp[token]);
	token++;


		if (isOperator(exp[token-1]))
		{
			if(exp[token-1]!='~')
			{
			node->left = makeExpressionTree(token,exp);
			node->right = makeExpressionTree(token,exp);
			}
			else
			{
				node->right = makeExpressionTree(token,exp);
			}
		}

	return node;
}

/// @brief Traverse the tree in Inorder Format 
///
/// Prints the original logic expression with appropriate brackets
/// @param node Root node of Tree to be traversed
void inorderTraverse(struct Node* node){

	if(node == NULL)
		return;
	if(isOperator(node->data))
		cout<<"(";
	inorderTraverse(node->left);
	cout<<(node->data);
	inorderTraverse(node->right);
	if(isOperator(node->data))
		cout<<")";

}

/// @brief Replaces the old_char with new_char inside the string expr
/// @param old_char 
/// @param new_char 
/// @param expr Logic expression where the character are to be replaced
/// @return The new expression with the propositional atom replaced by their truth value
string replace(char old_char,char new_char,string expr)
{
     for(int i=0;i<expr.length();i++)
     	if(expr[i]==old_char)
     		expr[i]=new_char;
     return expr;
}


/// @brief Assign the truth values of all the unique propositional atoms in the Logic Expression
/// @param prefix Logic statement that needs to be modified
/// @param num_of_atoms Number of atoms in the statement - Used to streamline the conversion and reduce complexity
/// @return Logic Expression with the atoms replaced by their truth values
string assignTruthValueToAtoms(string prefix, int num_of_atoms)
{
	int i=0;
	while(num_of_atoms)
	{
		if(!isOperator(prefix[i]))
		{
			if(prefix[i] !='T' && prefix[i] !='F')
			{
				char TruthValueOfAtom;
				cout<<"Enter truth value of "<<prefix[i]<<" :"<<endl;
				cin>>TruthValueOfAtom;
				prefix=replace(prefix[i],TruthValueOfAtom,prefix);
				num_of_atoms--;
			}
		}
		i++;
	}


	return prefix;
}


/// @brief Carry out Logic Operation Implementations 
///
/// Operation such as conjunction(*) , disjunction(+), implication(>), negation(~) 
/// @param left_char Character in the left node 
/// @param right_char Character in the right node
/// @param oper Character in the parent - operation
/// @return Character F-false , T-true after doing the logical operation
char doOperation(char left_char, char right_char,char oper){
	bool left_bool = (left_char=='F')?false:true;
	bool right_bool = (right_char=='F')?false:true;
	if(oper == '*')
		return ((left_bool&&right_bool)?'T':'F');
	else if(oper == '+')
		return ((left_bool||right_bool)?'T':'F');
	else if(oper == '>')
		return (((!left_bool)||right_bool)?'T':'F');
	else
		return 'F';

}


/// @brief Driver Function for Checking Truth Value
///
/// Recursively checks the truth value of every subtree and assigns the parent node with the characters 'T' and 'F'
/// @param node Root node of tree to be checked
void checkTruthValue(struct Node* node)
{

	if(node == NULL)
		return ;
	if(isOperator(node->data))
	{
		if(node->data!='~')
		{
			checkTruthValue(node->left);
			checkTruthValue(node->right);
			node->data = doOperation(node->left->data,node->right->data,node->data);
		}
		else
		{
			checkTruthValue(node->right);
			node->data = (node->right->data=='T')?'F':'T';
		}
	}
	return;

}

/// @brief Calculate the height of the tree
///
/// Recursively calculates the heights of left and right subtrees and returns 1 more than the maximum of these heights
/// Height = **number of edges in the longest path in the tree** + **1**
/// @param node The root node of the tree for which the height needs to be calculated
/// @return The height of the tree as an integer
int calculateHeight(Node* node){
	if(node==NULL)
		return 0;
	int l_ht = calculateHeight(node->left);
	int r_ht = calculateHeight(node->right);
	int temp = 1 + max(l_ht,r_ht);
	return temp;

}

/// @brief Main driving function
///
///This is the main driving function which calls all the necessary functions sequentially
int main()
{
    //The logic expression which is being taken from the user as input
    cout << "Enter valid infix expression: ";
    string input_infix_str;   
    cin >> input_infix_str;

    //Number of propositional atoms involved in the logic expression
    cout << "Enter No. of propositional atoms in the string: ";
    int no_of_atoms;
    cin>>no_of_atoms;

    //Conversion of Infix to Prefix(Polish) Notation and assigning
    string prefix_str = infixToPrefix(input_infix_str);
    cout << "The Prefix String is: ";
    cout<<prefix_str<<endl;
    //Making the Expression tree from prefix notation
    int x = 0;
    struct Node* root = makeExpressionTree(x,prefix_str);

    //Inorder Traversal of tree
    cout << "The inorder traversal of tree gives: ";
    inorderTraverse(root);
    cout<<endl;

    //Calculating height of tree = Number of edges in the maximum path + 1
    cout << "Height of tree is: ";
    cout << calculateHeight(root) << endl;


    //Assigning the truth value to the Atoms in the Logical Expression
    int y=0;
    string assigned_prefix = assignTruthValueToAtoms(prefix_str,no_of_atoms);

    //Making another tree to calculate the truth value
    struct Node* root_of_truth_value = makeExpressionTree(y,assigned_prefix);

    //Checking for the truth value of statement
    checkTruthValue(root_of_truth_value);
    cout << "The Truth Value of expression is: ";
    cout << root_of_truth_value->data << endl;


    return 0;
}