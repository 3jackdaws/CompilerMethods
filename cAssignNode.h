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
#include "cVarExprNode.h"

class cAssignNode : public cStmtNode
{
    public:
        cAssignNode(cVarExprNode * varexpr, cExprNode * expr) : cStmtNode() 
        {
            AddChild(varexpr);
            AddChild(expr);
        }
        
        cVarExprNode * GetLVal()
        {
            return static_cast<cVarExprNode *>(GetChild(0));
        }
        
        cExprNode * GetRVal()
        {
            return static_cast<cExprNode *>(GetChild(1));
        }
        
        cSymbol * GetLType()
        {
            return GetLVal()->GetType()->GetType()->GetName();
        }
        
        cSymbol * GetRType()
        {
            return GetRVal()->GetType()->GetType()->GetName();
        }
        
        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
