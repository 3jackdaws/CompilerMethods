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
#include "cParamListNode.h"

class cFuncExprNode : public cStmtNode
{
    public:
        cFuncExprNode(cSymbol * ident, cAstNode * params = nullptr) : cStmtNode() 
        {
            AddChild(ident);
            AddChild(params);
        }
        
        virtual string AttributesToString() 
        {
            return "";
        }
        
        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        float m_value;        // value of integer constant (literal)
};
