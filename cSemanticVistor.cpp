#include "lex.h"
#include "cSemanticVisitor.h"
#include "astnodes.h"

void cSemanticVisitor::PreVisitAllNodes(cAstNode *node)
{
    VisitAllChildren(node);

    node->Visit(this);
}

void cSemanticVisitor::PostVisitAllNodes(cAstNode *node)
{
    node->Visit(this);

    VisitAllChildren(node);
}

void cSemanticVisitor::VisitAllChildren(cAstNode *node)
{
    cAstNode::iterator it;
    for (it=node->FirstChild(); it!=node->LastChild(); it++)
    {
        if ((*it) != nullptr) (*it)->Visit(this);
    }
}

void cSemanticVisitor::SemanticError(cAstNode *node, string msg){
    m_numErrors++;

    node->SetHasError();
    std::cout << "ERROR: " << msg <<" on line " << node->LineNumber() << "\n";

}

int cSemanticVisitor::NumErrors()
{
    return m_numErrors;
}



void cSemanticVisitor::Visit(cAssignNode *node)
{ 
    // print("assign");
    if(node->GetLType() != node->GetRType())
    {
        SemanticError(node, "Cannot assign " + node->GetRType()->GetName() + " to " + node->GetLType()->GetName());
    }
    VisitAllChildren(node); 
}
void cSemanticVisitor::Visit(cAstNode *node)          { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cBlockNode *node)        { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cDeclNode *node)         { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cDeclsNode *node)        { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cExprNode *node)         { VisitAllChildren(node); }

void cSemanticVisitor::Visit(cFuncExprNode *node)
{ 
    if(!node->DeclarationExists())
    {
        // print("No decl");
        cSemanticVisitor::SemanticError(node, node->GetFuncName()->GetName() + " is not declared");
        node->SetHasError();
    }
    else if(!node->GetFuncName()->GetDecl()->IsFunc())
    {
        // print("Not func");
        cSemanticVisitor::SemanticError(node, node->GetFuncName()->GetName() + " is not a function");
        node->SetHasError();
    }
    else 
    {
        cFuncDeclNode * declnode = node->GetFuncDeclNode();
        
        if(!declnode->GetStmts() && !declnode->GetDecls())
        {
            // print("Not fully def");
            cSemanticVisitor::SemanticError(node, node->GetFuncName()->GetName() + " is not fully defined");
            node->SetHasError();
            // print("Not fully def--");
        }
        
        // print("set params");
        cParamListNode * passed_params = node->GetParamListNode();
        // cFuncDeclNode * func_decl = node->GetFuncDeclNode();
        cParamsNode * required_params = node->GetFuncDeclNode()->GetParams();
        // if(func_decl) required_params = func_decl->GetParams();
        // else {print("NoFuncDecl");}
        // print("set params--");
        
        // print(passed_params);
        // print(required_params);
        
        bool params_differ = (passed_params && !required_params) || (required_params && !passed_params);
        bool both_null = !(passed_params || required_params);
        
        // print(params_differ);
        if(both_null){
            // print("bn");
        }
        else if(params_differ || passed_params->NumberParams() != required_params->NumberParams())
        {
            // print("wrong num");
            cSemanticVisitor::SemanticError(node, node->GetFuncName()->GetName() + " called with wrong number of arguments");
            node->SetHasError();
        }
        else
        {
            // print("for");
            for(int i = 0; i < passed_params->NumberParams(); i++)
            {
                // print(i);
                cSymbol * pp_type = passed_params->GetParamTypeSymbol(i);
                cSymbol * rp_type = required_params->GetParamTypeSymbol(i);
                // print(pp_type->GetName() + " - " + rp_type->GetName());
                if(pp_type != rp_type)
                {
                    if(rp_type->GetDecl()->IsInt() && pp_type->GetDecl()->IsChar())
                    {
                        
                    }else{
                        cSemanticVisitor::SemanticError(node, node->GetFuncName()->GetName() + " called with incompatible argument");
                        node->SetHasError();
                    }
                    
                }
            }
        }
    }
    
    
    
    
    VisitAllChildren(node); 
}
void cSemanticVisitor::Visit(cIntExprNode *node)      { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cOpNode *node)           { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cPrintNode *node)        { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cProgramNode *node)      { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cStmtNode *node)         { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cStmtsNode *node)        { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cSymbol *node)
{ 
    if(node->GetDecl() == nullptr){
        cSemanticVisitor::SemanticError(node, "Symbol " + node->GetName() + " not defined");
        node->SetHasError();
    }
    VisitAllChildren(node); 
}

void cSemanticVisitor::Visit(cVarExprNode *node)
{ 
    // cSemanticVisitor::SemanticError(node, node->GetVarSymbol()->GetName() + " is of type " + node->GetActualTypeSymbol()->GetName());
    if(node->IsBeingIndexed())
    {
        if(! node->GetVarType()->GetDecl()->IsArray())
        {
            cSemanticVisitor::SemanticError(node, node->GetVarSymbol()->GetName() + " is not an array");
            node->SetHasError();
        }else{
            if( ! node->IndicesAreInts())
            {
                cSemanticVisitor::SemanticError(node, "Index of " + node->GetVarSymbol()->GetName() + " is not an int");
                node->SetHasError();
            }
        }
        // cSemanticVisitor::SemanticError(node, node->GetVarSymbol()->GetName() + " is being indexed");
        // cSemanticVisitor::SemanticError(node, node->GetType()->GetName()->GetName() + " is not an array");
        // node->SetHasError();
    }
  
    VisitAllChildren(node); 
}

