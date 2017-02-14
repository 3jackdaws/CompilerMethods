#pragma once
//**************************************
// cBinaryExprNode.h

//
// Author: Ian Murphy
//
// Date: Jan. 18, 2015
//

#include "cExprNode.h"
#include "cOpNode.h"

class cBinaryExprNode : public cExprNode
{
    public:
        cBinaryExprNode(cExprNode * left, cOpNode * op, cExprNode * right) : cExprNode() {
            AddChild(left);
            AddChild(op);
            AddChild(right);
        }
        
    
        virtual string NodeType() { return string("expr"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        float m_value;        // value of integer constant (literal)
};