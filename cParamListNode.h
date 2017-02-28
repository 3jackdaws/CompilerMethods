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

#include "cStmtNode.h"

class cParamListNode : public cStmtNode
{
    public:
        cParamListNode(cExprNode * expr) : cStmtNode() 
        {
            AddChild(expr);
        }
        
        void AddExpr(cExprNode * expr)
        {
            AddChild(expr);
        }
        
        int NumberParams()
        {
            return NumChildren();
        }
        
        cSymbol * GetParamTypeSymbol(int index)
        {
            return static_cast<cExprNode *>(GetChild(index))->GetType()->GetType()->GetName();
        }
        
        
        virtual string NodeType() { return string("params"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
