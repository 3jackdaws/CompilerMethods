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

#include "cDeclNode.h"

class cStructDeclNode : public cDeclNode
{
    public:
        cStructDeclNode(cDeclsNode * decls, cSymbol * name) : cDeclNode() 
        {
            AddChild(decls);
            AddChild(name);
            
            if ( ! g_SymbolTable.Find(name->GetName()) )
            {
                g_SymbolTable.Insert(name);
            }
            
            name->SetDecl(this);
        }
        
        // Add a decl to the list
        void Insert(cDeclNode *decl)
        {
            AddChild(decl);
        }
        
        virtual bool IsStruct() { return true; }
        virtual bool IsType() { return true; }

        virtual cSymbol* GetName()
        {
            return dynamic_cast<cSymbol*>(GetChild(1));
        }
        
        virtual cDeclNode* GetType()
        {
            return dynamic_cast<cSymbol*>(GetChild(0))->GetDecl();
        }

        virtual string NodeType() { return string("struct_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
