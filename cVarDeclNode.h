#pragma once
//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//

#include "cAstNode.h"

class cVarDeclNode : public cDeclNode
{
    public:
        cVarDeclNode(cSymbol * type, cSymbol * name) : cDeclNode() {
            
            if( ! g_SymbolTable.FindLocal(name->GetName()))
            {
                
                if (g_SymbolTable.Find(name->GetName()) )
                {
                    name = new cSymbol(name->GetName());
                }
                g_SymbolTable.Insert(name);
            }
            else
            {
                SemanticError("Symbol " + name->GetName() + " already defined in current scope");
            }
            
            AddChild(type);
            AddChild(name);

            name->SetDecl(this);

        }
        
        virtual cSymbol* GetName(){
            return dynamic_cast<cSymbol *>(GetChild(1));
        }
        
        virtual cDeclNode * GetType()
        {
            return dynamic_cast<cSymbol *>(GetChild(0))->GetDecl();
        }
        
        virtual bool IsVar(){ return true; }
        

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
