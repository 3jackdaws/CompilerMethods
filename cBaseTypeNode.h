#include "cDeclNode.h"
#include "cDeclsNode.h"

class cBaseTypeNode : public cDeclNode
{
    public:
        cBaseTypeNode(string name, int base_type):cDeclNode()        
        {
            m_base_type = base_type;
            m_name = g_SymbolTable.Find(name);
            m_name->SetDecl(this);
        }
        
    
        virtual string NodeType() { return string("base"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        
        virtual bool IsType(){return true;}
        
        virtual cDeclNode * GetType()
        {
            return this;
        }
        
        virtual cSymbol * GetName()
        {
            return m_name;
        }
        
        virtual bool IsChar(){
            return m_base_type == 1;
        }
        
        virtual bool IsInt(){
            return m_base_type == 2;
        }
        
        virtual bool IsFloat(){
            return m_base_type == 3;
        }
        
    protected:
        int m_base_type; 
        cSymbol * m_name;
};