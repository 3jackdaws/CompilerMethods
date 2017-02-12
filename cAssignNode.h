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

class cAssignNode : public cStmtNode
{
    public:
        cAssignNode(cAstNode * varexpr, cAstNode * expr) : cStmtNode() 
        {
            
            AddChild(varexpr);
            AddChild(expr);
        }
        
        virtual string AttributesToString() 
        {
            return "";
        }
        
        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        float m_value;        // value of integer constant (literal)
};
