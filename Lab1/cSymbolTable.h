#include <unordered_map>
using std::unordered_map;

#include <deque>
using std::deque;

#include <string>
using std::string;

#define CURRENT_SCOPE m_stack.front() 


class cSymbolTable{
    public:
        cSymbolTable(){
            IncreaseScope();
        }
        
        void IncreaseScope(){
            
            m_stack.push_front(new unordered_map<string, cSymbol *>);
        };
        
        void DecreaseScope(){
            m_stack.pop_front();
        };
        
        cSymbol * Insert(char * identifier){
            
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