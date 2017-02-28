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
#include "cDeclNode.h"

class cParamsNode : public cAstNode
{
    public:
        cParamsNode(cDeclNode * decl) : cAstNode() {
            AddChild(decl);
        }
        
        // Add a decl to the list
        void AddDecl(cDeclNode *decl)
        {
            AddChild(decl);
        }
        
        int NumberParams()
        {
            return NumChildren();
        }
        
        cSymbol * GetParamTypeSymbol(int index)
        {
            return static_cast<cDeclNode *>(GetChild(index))->GetType()->GetType()->GetName();
        }

        virtual string NodeType() { return string("args"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
