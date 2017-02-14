#pragma once
//**************************************
// cStmtNode.h
//
// Defines abstract class for a single statment
//
// NOTE: all statement types must inherit from this class
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//

#include "cStmtNode.h"

class cReturnNode : public cStmtNode
{
    public:
        cReturnNode(cExprNode * expr) : cStmtNode() 
        {
            AddChild((cAstNode *)expr);
        }
        
        virtual string NodeType() { return string("return"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
