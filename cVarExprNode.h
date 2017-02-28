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

class cVarExprNode : public cExprNode
{
    public:
        // param is the value of the integer constant
        cVarExprNode(cSymbol * var) : cExprNode()
        {
            AddChild(var);
        }
        
        void AddSymbol(cSymbol * name)
        {
            AddChild(name);
        }
        
        virtual cDeclNode * GetType(){
            if(IsBeingIndexed()) return GetActualTypeSymbol()->GetDecl()->GetType();
            
            return static_cast<cSymbol *>(GetChild(0))->GetDecl();
        }
        
        cExprNode * GetFirstIndex()
        {
            cExprNode * index = nullptr;
            for(int i = 0; i<NumChildren();i++)
            {
                index = dynamic_cast<cExprNode*>(GetChild(i));
                if(index) break;
            }
            return index;
        }
        
        cExprNode * GetIndexExpr(int num)
        {
            cExprNode * expr = nullptr;
            if(num < NumIndices())
            {
                int count = 0;
                for(int i = 0; i<NumChildren() && count<=num; i++)
                {
                    expr = dynamic_cast<cExprNode*>(GetChild(i));
                    if(expr) count++;
                }
                
            }
            return expr;
        }
        
        bool IndicesAreInts()
        {
            cExprNode * expr = nullptr;
            for(int i = 0; i<NumChildren(); i++)
            {
                expr = dynamic_cast<cExprNode*>(GetChild(i));
                if(expr)
                {
                    if(expr->GetType()->GetName()->GetDecl()->GetType()->IsInt())
                    {
                        // do nothing
                    }
                    else if(expr->GetType()->GetName()->GetDecl()->GetType()->IsChar())
                    {
                        // doo nothing
                    }
                    else
                    {
                        // print(expr->GetType()->GetName()->GetDecl()->GetType()->GetName()->GetName());
                        return false;
                    }
                } 
            }
            return true;
        }
        
        bool IsBeingIndexed()
        {
            return GetFirstIndex() != nullptr;
        }
        
        int NumIndices()
        {
            cExprNode * index = nullptr;
            int count = 0;
            for(int i = 0; i<NumChildren();i++)
            {
                index = dynamic_cast<cExprNode*>(GetChild(i));
                if(index) count++;
            }
            return count;
        }
        
        cSymbol * GetActualTypeSymbol()
        {
            int num = NumIndices();
            cSymbol * type = GetVarType();
            if(GetVarType()->GetDecl()->IsArray())
            {
                
                for(int i = 0;i<num;i++)
                {
                    type = type->GetDecl()->GetType()->GetType()->GetName();
                }

            }
            return type;
        }
        
        cSymbol * GetVarSymbol()
        {
            return static_cast<cSymbol *>(GetChild(0));
        }
        
        cSymbol * GetVarType()
        {
            return static_cast<cSymbol *>(GetChild(0))->GetDecl()->GetType()->GetName();
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
