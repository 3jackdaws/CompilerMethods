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

#include "cDeclNode.h"
#include "cDeclsNode.h"

class cArrayDeclNode : public cDeclNode
{
    public:
        cArrayDeclNode(cSymbol * type, cSymbol * name, int size):cDeclNode(){
            
            AddChild(type);
            AddChild(name);
            m_size = size;
        }
        
        void SetSize(int size){
            m_size = size;
        }
        
        int GetSize()
        {
            return m_size;
        }
        
        virtual string AttributesToString() 
        {
            string result(" count='");
            result += std::to_string(m_size);
            result += "'";
            return result;
        }
        
        virtual string NodeType() { return string("array_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        int m_size;        // value of integer constant (literal)
};
