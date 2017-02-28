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
#include "cParamsNode.h"

class cFuncDeclNode : public cDeclNode
{
    public:
        cFuncDeclNode(cSymbol * type, cSymbol * ident):cDeclNode()        
        {
            AddChild(type);
            AddChild(ident);
           
            
            ident->SetDecl(this);
            // print("Constr");
            
            AddChild(nullptr);
            AddChild(nullptr);
            AddChild(nullptr);
        }
        
        void AddParams(cParamsNode * params)
        {
            // print("AddParams");
            cParamsNode * set_params = GetParams();
            if ( set_params )
            {
                int decl_num = set_params->NumChildren();
                if (decl_num != params->NumChildren())
                {
                    SemanticError(GetName()->GetName() + " previously declared with a different number of parameters");
                }
                
                for (int i = 0; i < decl_num; i++)
                {
                    cVarDeclNode * prev = static_cast<cVarDeclNode *>(set_params->GetChild(i));
                    cVarDeclNode * curr = static_cast<cVarDeclNode *>(params->GetChild(i));
                    
                    if (prev->GetType() != curr->GetType())
                    {
                        SemanticError(GetName()->GetName() + " previously declared with different parameters");
                    }
                }
            }
            
            
            m_children[2] = params;
        }
        
        cParamsNode * GetParams()
        {
            return static_cast<cParamsNode *>(m_children[2]);
        }
        
        void AddDecls(cDeclsNode * decls)
        {
            m_children[3] = decls;
        }
        
        cDeclsNode * GetDecls()
        {
            return static_cast<cDeclsNode *>(m_children[3]);
        }
        
        void AddStmts(cStmtsNode * stmts)
        {
            if (GetStmts())
            {
                SemanticError(GetName()->GetName() + " already has a definition");
            }
            m_children[4] = stmts;
        }
        
        cStmtsNode * GetStmts()
        {
            return static_cast<cStmtsNode *>(m_children[4]);
        }
        
        virtual cSymbol * GetName()
        {
            return dynamic_cast<cSymbol *> (GetChild(1));
        }
        
        virtual cDeclNode * GetType()
        {
            return dynamic_cast<cSymbol *> (GetChild(0))->GetDecl();
        }
        
        static cFuncDeclNode * Create(cSymbol * type, cSymbol * ident)
        {
            // print("Create");
            if (!g_SymbolTable.FindLocal(ident->GetName()))
            {
                if(g_SymbolTable.Find(ident->GetName()))
                {
                    ident = new cSymbol(ident->GetName());
                }
                
                g_SymbolTable.Insert(ident);
            }
            
            cDeclNode * prev = g_SymbolTable.Find(ident->GetName())->GetDecl();
            
            if ( prev )
            {
                
                if (prev->GetType() != type->GetDecl())
                {
                    SemanticError(ident->GetName() + " previously declared with different return type");
                }
                else if ( ! prev->IsFunc() )
                {
                    SemanticError(ident->GetName() + " previously declared as other than a function");
                }
                else
                {
                    cFuncDeclNode * decl = new cFuncDeclNode(type, ident);
                    cFuncDeclNode * prev_decl = dynamic_cast<cFuncDeclNode *>(prev);
                    
                    decl->AddParams(prev_decl->GetParams());
                    decl->AddDecls(prev_decl->GetDecls());
                    decl->AddStmts(prev_decl->GetStmts());
                    
                    return decl;
                }
            }
            
            return new cFuncDeclNode(type, ident);
        }
        
        
        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        
        virtual bool IsFunc(){ return true; }
};
