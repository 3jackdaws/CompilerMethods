#pragma once
//**************************************
// cIntExprNode.h
//
// Defines an AST node for an integer constant (literals).
//
// Inherits from cExprNode so that integer constants can be used anywhere 
// expressions are used.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//

#include "cAstNode.h"
#include "cExprNode.h"

class cFloatExprNode : public cExprNode
{
    public:
        // param is the value of the integer constant
        cFloatExprNode(float value) : cExprNode()
        {
            // print(value);
            m_value = value;
        }
        
        float GetValue()
        {
            return m_value;
        }
        
        virtual cDeclNode * GetType(){
            return g_SymbolTable.Find("float")->GetDecl();
        }

        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        virtual string NodeType() { return string("float"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        float m_value;        // value of integer constant (literal)
};
