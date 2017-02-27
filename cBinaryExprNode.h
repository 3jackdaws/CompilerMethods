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
        
        virtual cDeclNode * GetType(){
            cExprNode * type_left = static_cast<cExprNode *>(GetChild(0));
            cExprNode * type_right = static_cast<cExprNode *>(GetChild(2));
            if(type_left->GetType()->IsFloat()) return type_left->GetType();
            if(type_right->GetType()->IsFloat()) return type_right->GetType();
            
            if(type_left->GetType()->IsInt()) return type_left->GetType();
            if(type_right->GetType()->IsInt()) return type_right->GetType();
            
            return type_left->GetType();
            
        }
        
    
        virtual string NodeType() { return string("expr"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        float m_value;        // value of integer constant (literal)
};