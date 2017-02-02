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
        
        cSymbol * Insert(string identifier){
            // std::cout << "Inserting Identifier" << std::endl;
            cSymbol * symbol = NULL;
            
            
            auto search = CURRENT_SCOPE->find(identifier);
            
            if(search == CURRENT_SCOPE->end()){
                
                symbol = new cSymbol(identifier);
                CURRENT_SCOPE->insert({identifier, symbol});
                
            }else{
                symbol = search->second;
            }
            return symbol;
        };
        
        cSymbol * Lookup(string key){
            auto search = CURRENT_SCOPE->find(key);
            if (search != CURRENT_SCOPE->end()){
                return search->second;
            }
            return nullptr;
        }
        
        cSymbol * LookupAll(string key){
            for (auto scope : m_stack){
                auto search = scope->find(key);
                if (search != scope->end()){
                    return search->second;
                }
            }
            return nullptr;
        }
        
    private:
        
        deque<unordered_map<string, cSymbol *> * > m_stack;
        
};