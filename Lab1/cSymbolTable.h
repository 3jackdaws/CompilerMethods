#include <unordered_map>
using std::unordered_map;

#include <deque>
using std::deque;

#include <string>
using std::string;

#include <iostream>

#define CURRENT_SCOPE m_stack.front() 


class cSymbolTable{
    public:
        cSymbolTable(){
            IncreaseScope();
        }
        
        void IncreaseScope(){
            // std::cout << "Increasing Scope" << std::endl;
            m_stack.push_front(new unordered_map<string, cSymbol *>);
        };
        
        void DecreaseScope(){
            // std::cout << "Decreasing Scope" << std::endl;
            m_stack.pop_front();
        };
        
        cSymbol * Insert(char * identifier){
            // std::cout << "Inserting Identifier" << std::endl;
            cSymbol * symbol = NULL;
            string identifier_string(identifier);
            
            auto search = CURRENT_SCOPE->find(identifier_string);
            
            if(search == CURRENT_SCOPE->end()){
                
                symbol = new cSymbol(identifier_string);
                CURRENT_SCOPE->insert({identifier_string, symbol});
                
            }else{
                symbol = search->second;
            }
            return symbol;
        };
        
    private:
        
        deque<unordered_map<string, cSymbol *> * > m_stack;
        
};