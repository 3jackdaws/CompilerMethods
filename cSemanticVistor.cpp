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
void cSemanticVisitor::Visit(cIntExprNode *node)      { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cOpNode *node)           { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cPrintNode *node)        { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cProgramNode *node)      { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cStmtNode *node)         { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cStmtsNode *node)        { VisitAllChildren(node); }
void cSemanticVisitor::Visit(cSymbol *node)
{ 
    if(node->GetDecl() == nullptr){
        cSemanticVisitor::SemanticError(node, "Symbol " + node->GetName() + " not defined ");
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

