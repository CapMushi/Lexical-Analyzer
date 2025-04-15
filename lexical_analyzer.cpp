#include <iostream>
#include <unordered_map>
#include <cstring>
#include <fstream>
#include <sys/stat.h>
#include <queue>
#include <windows.h>  
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);  


using namespace std;

const int BUFFER_SIZE = 25;
bool doprint=false;

string identifiers[100];
int identifier_count = 0;

int literal_count = 0;
string literals_storage[100];

string keywords[] = {
        "asm", "Wagarna", "new", "this", "auto", "enum", "operator", "throw",
        "Mantiqi", "explicit", "private", "True", "break", "export", "protected",
        "try", "case", "extern", "public", "typedef", "catch", "False", "register",
        "typeid", "Harf", "Ashriya", "typename", "Adadi", "class", "for", "Wapas",
        "union", "const", "dost", "short", "unsigned", "goto", "signed", "using",
        "continue", "Agar", "sizeof", "virtual", "default", "inline", "static",
        "Khali", "delete", "volatile", "do", "long", "struct", "double", "mutable",
        "switch", "while", "namespace", "template", "Marqazi", "Matn", "input->",
        "output<-"
    };

// 2D Array for final states classification
int final_states[6][2] = {
    {9, 0},  // Punctuation
    {10, 1}, // Operator
    {11, 1}, // Operator
    {15, 2}, // Identifier
    {21, 3}, // Numbers
    {22, 4}  // Keyword
};

unordered_map<int, unordered_map<char, int>> transition_table = {
    // Transitions from state 0
    {0, {
        {'-', 5}, {'+', 6}, {'0', 16}, {'1', 16}, {'2', 16}, {'3', 16}, {'4', 16}, 
        {'5', 16}, {'6', 16}, {'7', 16}, {'8', 16}, {'9', 16}, {'(', 9}, {')', 9}, 
        {'{', 9}, {'}', 9}, {'[', 9}, {']', 9}, {':', 7}, {'%', 10}, {'*', 10}, 
        {'"', 10}, {'!', 8}, {'=', 8}, {'^', 10}, {'&', 1}, {'|', 2}, {'<', 3}, 
        {'>', 4}, {'/', 12}, 
        {'a', 13}, {'b', 13}, {'c', 13}, {'d', 13}, {'e', 13}, {'f', 13}, {'g', 13}, 
        {'h', 13}, {'i', 13}, {'j', 13}, {'k', 13}, {'l', 13}, {'m', 13}, {'n', 13}, 
        {'o', 13}, {'p', 13}, {'q', 13}, {'r', 13}, {'s', 13}, {'t', 13}, {'u', 13}, 
        {'v', 13}, {'w', 13}, {'x', 13}, {'y', 13}, {'z', 13}, {'A', 13}, {'B', 13}, 
        {'C', 13}, {'D', 13}, {'E', 13}, {'F', 13}, {'G', 13}, {'H', 13}, {'I', 13}, 
        {'J', 13}, {'K', 13}, {'L', 13}, {'M', 13}, {'N', 13}, {'O', 13}, {'P', 13}, 
        {'Q', 13}, {'R', 13}, {'S', 13}, {'T', 13}, {'U', 13}, {'V', 13}, {'W', 13}, 
        {'X', 13}, {'Y', 13}, {'Z', 13}, {'_', 14}
    }},

    // Number transitions
    {5, {{'0', 16}, {'1', 16}, {'2', 16}, {'3', 16}, {'4', 16}, {'5', 16}, {'6', 16}, {'7', 16}, {'8', 16}, {'9', 16}}},
    {6, {{'0', 16}, {'1', 16}, {'2', 16}, {'3', 16}, {'4', 16}, {'5', 16}, {'6', 16}, {'7', 16}, {'8', 16}, {'9', 16}}},
    {16, {{'0', 16}, {'1', 16}, {'2', 16}, {'3', 16}, {'4', 16}, {'5', 16}, {'6', 16}, {'7', 16}, {'8', 16}, {'9', 16}, {'.', 17},{'e', 18},{'E', 18}}},
    {17, {{'0', 17}, {'1', 17}, {'2', 17}, {'3', 17}, {'4', 17}, {'5', 17}, {'6', 17}, {'7', 17}, {'8', 17}, {'9', 17},{'e', 18},{'E', 18}}},
    {18, {{'-', 20}, {'+', 20}, {'0', 19}, {'1', 19}, {'2', 19}, {'3', 19}, {'4', 19}, {'5', 19}, {'6', 19}, {'7', 19}, {'8', 19}, {'9', 19}}},
    {19, {{'0', 19}, {'1', 19}, {'2', 19}, {'3', 19}, {'4', 19}, {'5', 19}, {'6', 19}, {'7', 19}, {'8', 19}, {'9', 19}}},
    {20, {{'0', 19}, {'1', 19}, {'2', 19}, {'3', 19}, {'4', 19}, {'5', 19}, {'6', 19}, {'7', 19}, {'8', 19}, {'9', 19}}},
    
    // Other transitions from second hashmap
    {9, {}}, {7, {{'=', 10}}}, {10, {}}, {8, {{'=', 10}}}, {2, {{'|', 10}}}, {1, {{'&', 10}}}, 
    {3, {{'=', 10}, {'<', 10}, {'>', 10}}}, {4, {{'=', 10}, {'>', 10}}}, {5, {{'=', 10}}}, 
    {6, {{'=', 10}, {'+', 10}}}, {12, {}}, {11, {}},

    // Identifier transitions
    {13, {
        {'a', 13}, {'b', 13}, {'c', 13}, {'d', 13}, {'e', 13}, {'f', 13}, {'g', 13}, 
        {'h', 13}, {'i', 13}, {'j', 13}, {'k', 13}, {'l', 13}, {'m', 13}, {'n', 13}, 
        {'o', 13}, {'p', 13}, {'q', 13}, {'r', 13}, {'s', 13}, {'t', 13}, {'u', 13}, 
        {'v', 13}, {'w', 13}, {'x', 13}, {'y', 13}, {'z', 13}, {'A', 13}, {'B', 13}, 
        {'C', 13}, {'D', 13}, {'E', 13}, {'F', 13}, {'G', 13}, {'H', 13}, {'I', 13}, 
        {'J', 13}, {'K', 13}, {'L', 13}, {'M', 13}, {'N', 13}, {'O', 13}, {'P', 13}, 
        {'Q', 13}, {'R', 13}, {'S', 13}, {'T', 13}, {'U', 13}, {'V', 13}, {'W', 13}, 
        {'X', 13}, {'Y', 13}, {'Z', 13}, {'0', 13}, {'1', 13}, {'2', 13}, {'3', 13}, 
        {'4', 13}, {'5', 13}, {'6', 13}, {'7', 13}, {'8', 13}, {'9', 13}, {'_', 14}
    }},
    
    {14, {
        {'a', 14}, {'b', 14}, {'c', 14}, {'d', 14}, {'e', 14}, {'f', 14}, {'g', 14}, 
        {'h', 14}, {'i', 14}, {'j', 14}, {'k', 14}, {'l', 14}, {'m', 14}, {'n', 14}, 
        {'o', 14}, {'p', 14}, {'q', 14}, {'r', 14}, {'s', 14}, {'t', 14}, {'u', 14}, 
        {'v', 14}, {'w', 14}, {'x', 14}, {'y', 14}, {'z', 14}, {'A', 14}, {'B', 14}, 
        {'C', 14}, {'D', 14}, {'E', 14}, {'F', 14}, {'G', 14}, {'H', 14}, {'I', 14}, 
        {'J', 14}, {'K', 14}, {'L', 14}, {'M', 14}, {'N', 14}, {'O', 14}, {'P', 14}, 
        {'Q', 14}, {'R', 14}, {'S', 14}, {'T', 14}, {'U', 14}, {'V', 14}, {'W', 14}, 
        {'X', 14}, {'Y', 14}, {'Z', 14}, {'0', 14}, {'1', 14}, {'2', 14}, {'3', 14}, 
        {'4', 14}, {'5', 14}, {'6', 14}, {'7', 14}, {'8', 14}, {'9', 14}, {'_', 14}
    }},
    
    {15, {}} // Identifier final state
};

queue<char> lexeme_queue;

void enqueue_character(char c) {
    lexeme_queue.push(c);
}

bool isKeyword(const string& input,int &index) {
    int size = sizeof(keywords) / sizeof(keywords[0]); // Get array size
    index=-1;
    // Check if the input exactly matches any keyword
    for (int i = 0; i < size; i++) {
        if (input == keywords[i]) {
        	index=i;
            return true;
        }
	}
	return false;
}


bool is_final_state(int state) {
    for (int i = 0; i < 6; i++) {
        if (final_states[i][0] == state) {
            return true;
        }
    }
    return false;
}

void process_lexeme(int state) {
	int id_index=0;
    if (is_final_state(state)) {
    	string lexeme = "";
    	SetConsoleTextAttribute(color, 12);
        cout << "<";
        SetConsoleTextAttribute(color, 7);
        if ((state == 11 || state==15 || state==21) &&!doprint)  {
            // Print all except the last character in queue
            size_t queue_size = lexeme_queue.size();
            for (size_t i = 0; i < queue_size - 1; i++) {
            	if (lexeme_queue.front()!=' ')
            	{
            		if (state!=15)
            			cout << lexeme_queue.front();
	                lexeme+=lexeme_queue.front();
	                
				}
				lexeme_queue.pop();
                
            }
            lexeme_queue.pop(); // Remove last character but do not print
            if (state==15) {
			    bool exists = false;
			    for (int i = 0; i < identifier_count; i++) {
			        if (identifiers[i] == lexeme) {
			            exists = true;
			            id_index=i;
			            break;
			        }
			    }
			    if (!exists) {
			        identifiers[identifier_count] = lexeme;
			        id_index=identifier_count;
			        ofstream symbolsFile("symbols.txt", ios::app);
			        symbolsFile << identifier_count << " " << lexeme << endl;
			        symbolsFile.close();
			        identifier_count++;
			    }
			    cout<<"Id, "<<id_index;
			}
        } else {
            while (!lexeme_queue.empty()) {
            	if (lexeme_queue.front()!=' ')
            	{
            		lexeme+=lexeme_queue.front();
            		if (state!=15)
            		 	cout << lexeme_queue.front();
				}

                	
                lexeme_queue.pop();
            }
            //if symbol in last and last character also has to be printed
            if (state==15) {
			    bool exists = false;
			    for (int i = 0; i < identifier_count; i++) {
			        if (identifiers[i] == lexeme) {
			            exists = true;
			            id_index=i;
			            break;
			        }
			    }
			    if (!exists) {
			        identifiers[identifier_count] = lexeme;
			        id_index=identifier_count;
			        ofstream symbolsFile("symbols.txt", ios::app);
			        symbolsFile << identifier_count << " " << lexeme << endl;
			        symbolsFile.close();
			        identifier_count++;
			    }
			    cout<<"Id, "<<id_index;
			}
        }
        SetConsoleTextAttribute(color, 12);
        cout << "> ";
        SetConsoleTextAttribute(color, 7);
    }
}

int literal_processing(const string& lexeme)
{
	bool exists = false;
	int index=0;
    for (int i = 0; i < literal_count; i++) {
        if (literals_storage[i] == lexeme) {
            exists = true;
            index=i;
            break;
        }
    }
    if (!exists) {
        literals_storage[literal_count] = lexeme;
        index=literal_count;
        ofstream symbolsFile("literals.txt", ios::app);
        symbolsFile << literal_count << " " << lexeme << endl;
        symbolsFile.close();
        literal_count++;
    }
    return index;
}

void process_input(const string& input, int start_state) {
    int state = start_state;
    string literal;
    bool firstquote=false;
    size_t i = 0;
    int lit_index;
    while (i < input.length()) {
    	
    	if (input[i]=='"' )
    	{
    		if (firstquote)
    		{
    			firstquote=false;
    			SetConsoleTextAttribute(color, 12);
		        cout << "<";
		        SetConsoleTextAttribute(color, 7);
		        
		        
		        lit_index=literal_processing(literal);
		        cout<<"Literal, "<<lit_index;
		        SetConsoleTextAttribute(color, 12);
		        cout << "> ";
		        SetConsoleTextAttribute(color, 7);
		        literal="";
		        
			}
			else
				firstquote=true;
			i++;
	    	continue;
    		
		}
		
		if (firstquote)//meaning letters inside quotes
		{
			literal+=input[i];
			i++;
			continue;
		}
	    
	    
        
        char c = input[i];
        enqueue_character(c); // Enqueue the current character
        
        
        
        if (state == 3 || state == 4 || state == 5 || state == 6) {
            if (transition_table[state].find(c) == transition_table[state].end()) {
                state = 11;
                if (lexeme_queue.size() > 1) {
                    i--; // Only decrement i for multi-character lexemes
                }
            }
        }
        
        //identifier state but can turn keyword
        else if (state == 13 ) {
        	string keyword;
        	int kidx=0;
            if (transition_table[state].find(c) == transition_table[state].end()) {
            	while (!lexeme_queue.empty())
                {
                	keyword+=lexeme_queue.front();
                	lexeme_queue.pop();
                }
                keyword.pop_back();
            	if (c==' ')//meaning space broke identifier
            	{
            		if(isKeyword(keyword,kidx))
            		{
            			SetConsoleTextAttribute(color, 12);
				        cout << "<";
				        SetConsoleTextAttribute(color, 7);
				        cout<<"Keyword, "<<kidx;
				        SetConsoleTextAttribute(color, 12);
				        cout << "> ";
				        SetConsoleTextAttribute(color, 7);
            			
					}
				}
				else//check whether your current matches if not matches check whether it is input output then check next 2 characters
				{
					if(isKeyword(keyword,kidx))
            		{
            			SetConsoleTextAttribute(color, 12);
				        cout << "<";
				        SetConsoleTextAttribute(color, 7);
				        cout<<"Keyword, "<<kidx;
				        SetConsoleTextAttribute(color, 12);
				        cout << "> ";
				        SetConsoleTextAttribute(color, 7);
            			
					}
					else
					{
						if (keyword=="input" && (i+1)<input.length())
						{
							if(c=='-' && input[i+1]=='>')
							{
								SetConsoleTextAttribute(color, 12);
						        cout << "<";
						        SetConsoleTextAttribute(color, 7);
						        cout<<"Keyword, 60";
						        SetConsoleTextAttribute(color, 12);
						        cout << "> ";
						        SetConsoleTextAttribute(color, 7);
						        state=0;
						        i+=2;
						        continue;

							}
						}
						else if(keyword=="output" && (i+1)<input.length())
						{
							if(c=='<' && input[i+1]=='-')
							{
								SetConsoleTextAttribute(color, 12);
						        cout << "<";
						        SetConsoleTextAttribute(color, 7);
						        cout<<"Keyword, 61";
						        SetConsoleTextAttribute(color, 12);
						        cout << "> ";
						        SetConsoleTextAttribute(color, 7);
						        state=0;
						        i+=2;
						        continue;
							}
							
						}
						
					}
				}
                

                
                if (lexeme_queue.size() > 1) {
                    i--; // Only decrement i for multi-character lexemes
                }
            }
        }
        //
        
        
        else if (state == 14 ) {
            if (transition_table[state].find(c) == transition_table[state].end()) {
                state = 15;
                if (lexeme_queue.size() > 1) {
                    i--; // Only decrement i for multi-character lexemes
                }
            }
        }
        
        else if (state == 16 || state == 17 || state == 19) {
            if (transition_table[state].find(c) == transition_table[state].end()) {
                state = 21;
                if (lexeme_queue.size() > 1) {
                    i--; // Only decrement i for multi-character lexemes
                }
            }
        }
        
        if (transition_table[state].find(c) != transition_table[state].end()) {
            state = transition_table[state][c];
            if (i == input.length() - 1) {
		        if (state == 3 || state == 4 || state == 5 || state == 6) 
	                state = 11;
		        else if (state == 14 ) 
		            state = 15;
		        else if (state == 16 || state == 17 || state == 19 ) 
		            state = 21;
		        else if(state==13)//only keyword plus null character
		        {
		            if (lexeme_queue.front(==' ')
		                lexeme_queue.pop();
		        	string keyword;
        			int kidx=0;
        			while (!lexeme_queue.empty())
	                {
	                	keyword+=lexeme_queue.front();
	                	lexeme_queue.pop();
	                }
	                if(isKeyword(keyword,kidx))
            		{
            			SetConsoleTextAttribute(color, 12);
				        cout << "<";
				        SetConsoleTextAttribute(color, 7);
				        cout<<"Keyword, "<<kidx;
				        SetConsoleTextAttribute(color, 12);
				        cout << "> ";
				        SetConsoleTextAttribute(color, 7);
            			
					}
	                
		        	
				}
		    doprint=true;
	    }
            
            
        } else {
            process_lexeme(state); // Process and print lexeme if final state is reached
            state = 0; // Reset state to start recognizing the next lexeme
            i++; // Ensure we move to the next character
            continue;
        }
        
        
        
        if (is_final_state(state)) {
            process_lexeme(state);
            state = 0; // Reset DFA for next lexeme
        }
        
        i++;
        
    }
    
}

bool file_exists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void create_files() {
    if (!file_exists("keywords.txt")) {
        fstream keywords("keywords.txt", ios::out);
        keywords.close();
    }
    
    fstream symbols("symbols.txt", ios::out);
    fstream literals("literals.txt", ios::out);
    symbols.close();
    literals.close();
}

void Lexical_Analyzer()
{
	create_files();
    
    string input;
    cout << "Enter input string: ";
    getline(cin, input);
    
    char buffer[BUFFER_SIZE + 1];
    int final_state = 0;
    int length = input.length();
    
    for (size_t i = 0; i < length; i += BUFFER_SIZE) {
        int chunk_size = min(BUFFER_SIZE, static_cast<int>(length - i));
        strncpy(buffer, input.c_str() + i, chunk_size);
        buffer[chunk_size] = '\0';  
        process_input(string(buffer), final_state);
    }
	
	
}

int main() {

    Lexical_Analyzer(); 
    return 0;
}