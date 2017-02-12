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

class cFuncDeclNode : public cDeclNode
{
    public:
        cFuncDeclNode(cSymbol * type, cSymbol * ident, cParamsNode * params = nullptr, cDeclsNode * locals = nullptr, cStmtsNode * stmts = nullptr):cDeclNode()        {
            AddChild(type);
            AddChild(ident);
            
            if(params)
                AddChild(params);
            if(locals)
                AddChild(locals);
            if(locals)
                AddChild(stmts);
        }
        
       
        
        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
