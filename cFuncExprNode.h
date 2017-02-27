#pragma once
//**************************************
// cExprNode.h
//
// Defines base class for all expressions
//
// This is a pure virtual class because there is no definition for
// cAstNode::ToString()
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//

#include "cExprNode.h"
#include "cParamListNode.h"

class cFuncExprNode : public cExprNode
{
    public:
        cFuncExprNode(cSymbol * ident, cParamListNode * params = nullptr) : cExprNode() 
        {
            AddChild(ident);
            AddChild(params);
        }
        
        virtual cDeclNode * GetType(){
            return static_cast<cSymbol *>(GetChild(0))->GetDecl()->GetType();
        }
        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
