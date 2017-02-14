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

class cWhileNode : public cStmtNode
{
    public:
        cWhileNode(cExprNode * expr, cStmtNode * stmt) : cStmtNode() 
        {
            AddChild((cAstNode *)expr);
            AddChild(stmt);
        }
 
        
        virtual string NodeType() { return string("while"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
