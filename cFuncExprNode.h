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

#include "cExprNode.h"

#include "cParamListNode.h"

#include "cFuncDeclNode.h"


class cFuncExprNode : public cExprNode
{
    public:
        cFuncExprNode(cSymbol * ident, cParamListNode * params = nullptr) : cExprNode() 
        {
            AddChild(ident);
            AddChild(params);
        }
        
        virtual cDeclNode * GetType(){
            return static_cast<cSymbol *>(GetChild(0))->GetDecl()->GetType();
        }
        
        cSymbol * GetFuncName()
        {
            return static_cast<cSymbol *>(GetChild(0));
        }
        
        bool DeclarationExists()
        {
            return static_cast<cSymbol *>(GetChild(0))->GetDecl() != nullptr;
        }
        
        cFuncDeclNode * GetFuncDeclNode()
        {
            return static_cast<cFuncDeclNode*>(GetFuncName()->GetDecl());
            
        }
        
        cParamListNode * GetParamListNode()
        {
            return static_cast<cParamListNode *>(GetChild(1));
        }
        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
