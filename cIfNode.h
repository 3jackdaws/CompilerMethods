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

class cIfNode : public cStmtNode
{
    public:
        cIfNode(cStmtNode * expr, cStmtsNode * nIf, cStmtsNode * nElse) : cStmtNode() 
        {
            // print( " IF NODE " );
            AddChild(static_cast<cAstNode *>(expr));
            AddChild(nIf);
            AddChild(nElse);
        }
        
        virtual string AttributesToString() 
        {
            return "";
        }
        
        virtual string NodeType() { return string("if"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        float m_value;        // value of integer constant (literal)
};
