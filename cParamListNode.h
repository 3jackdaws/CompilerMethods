#pragma once
//**************************************
// cParamListNode.h
//
// Defines AST node for actual params passed to a function
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cExprNode.h"

class cParamListNode : public cAstNode
{
    public:
        // param is first actual param passed to function
        cParamListNode(cExprNode *param)
            : cAstNode()
        {
            AddChild(param);
        }

        // add the next actual param
        void Insert(cExprNode *param)
        {
            AddChild(param);
        }

        cExprNode* GetParam(int index)
        {
            return static_cast<cExprNode*>(GetChild(index));
        }

        void SetSize(int size) { m_size = size; }
        int GetSize() { return m_size; }

        virtual string NodeType() { return string("params"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        virtual string AttributesToString()
        {
            if (m_size != 0)
            {
                return " size=\"" + std::to_string(m_size) + "\"";
            }
            else
            {
                return "";
            }
        }
    protected:
        int m_size;

};
