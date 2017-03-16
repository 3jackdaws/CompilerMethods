#include "cVisitor.h"

#define STACK_FRAME_SIZE 8

static void FatalError(const char *msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}

class cComputeSize : public cVisitor
{
  public:
    cComputeSize() : cVisitor()
    {
        m_offset = 0;
        m_highwater = 0;
    }

    void VisitAllNodes(cAstNode *node) { node->Visit(this); }

    virtual void Visit(cArrayDeclNode *node)
    {
        int size;
        size = node->GetBaseType()->GetSize() * node->GetCount();
        node->SetSize(size);
    }

    virtual void Visit(cBlockNode *node)
    {
        int start_offset = m_offset;
        int start_highwater = m_highwater;

        m_highwater = m_offset;
        VisitAllChildren(node);

        if (m_offset > m_highwater) m_highwater = m_offset;

        node->SetSize(m_highwater - start_offset);

        if (start_highwater > m_highwater) m_highwater = start_highwater;
        m_offset = start_offset;
    }

    virtual void Visit(cDeclsNode *node)
    {
        int start_offset = m_offset;

        VisitAllChildren(node);

        node->SetSize(m_offset - start_offset);
    }

    virtual void Visit(cFuncDeclNode *node)
    {
        int start_offset = m_offset;
        int start_highwater = m_highwater;

        m_offset = -STACK_FRAME_SIZE;
        m_highwater = 0;

        if (node->GetParams() != nullptr) node->GetParams()->Visit(this);
        m_offset = 0;
        m_highwater = 0;
        if (node->GetLocals() != nullptr) node->GetLocals()->Visit(this);
        if (node->GetStmts() != nullptr) node->GetStmts()->Visit(this);

        node->SetSize( RoundUp(m_highwater) );

        m_highwater = start_highwater;
        m_offset = start_offset;
    }

    virtual void Visit(cParamListNode *node)
    {
        int size = 0;
        
        // need to explicitly visit the children because expressions don't 
        // update a size so we can't use VisitAllChildren
        for (int ii=0; ii<node->NumChildren(); ii++)
        {
            cExprNode *expr = node->GetParam(ii);

            if ( expr != nullptr) 
            {
                expr->Visit(this);
                size += RoundUp(expr->GetType()->GetSize());
            }
        }

        node->SetSize(size);
    }

    virtual void Visit(cParamsNode *node)
    {
        VisitAllChildren(node);

        node->SetSize(-m_offset - STACK_FRAME_SIZE);
        if (m_offset > m_highwater) m_highwater = m_offset;
    }

    virtual void Visit(cProgramNode *node)
    {
        VisitAllChildren(node);
        cBlockNode *block = node->GetBlock();
        block->SetSize( RoundUp(block->GetSize()) );
    }

    virtual void Visit(cStructDeclNode *node)
    {
        int start_offset = m_offset;

        m_offset = 0;

        VisitAllChildren(node);

        node->SetSize(m_offset);
        m_offset = start_offset;
    }

    virtual void Visit(cVarDeclNode *node)
    {
        int size = node->GetType()->GetSize();
        node->SetSize(size);

        if (size != 1 || m_offset < 0) m_offset = RoundUp(m_offset);

        if (m_offset < 0)
        {
            node->SetOffset( m_offset - RoundUp(size) );
            m_offset = node->GetOffset();
        }
        else
        {
            node->SetOffset(m_offset);
            m_offset += node->GetSize();
        }

        if (m_offset > m_highwater) m_highwater = m_offset;
    }

    virtual void Visit(cVarExprNode *node)
    {
        bool isStruct = false;
        bool isArray = false;

        int offset = 0;
        cDeclNode *decl;
        cDeclNode *base_decl;

        // need to visit array indexes
        VisitAllChildren(node);

        base_decl = node->GetName()->GetDecl();
        decl = base_decl; // needed if this is an array

        offset = base_decl->GetOffset();

        // Need to explicitly visit all children because expressions won't 
        // AddRowSize so we can't use VisitAllChildren
        for (int ii=0; ii<node->NumItems(); ii++)
        {
            if (node->ItemIsIndex(ii))
            {
                cDeclNode *aDecl = base_decl->GetType();
                isArray = true;
                if (isStruct) 
                    FatalError("Mixed structs and arrays is not supported");
                node->AddRowSize( aDecl->GetType(ii+1)->GetSize() );
            }
            else
            {
                isStruct = true;
                if (isArray && isStruct) 
                    FatalError("Mixed structs and arrays is not supported");

                decl = node->GetElement(ii)->GetDecl();
                offset += decl->GetOffset();
            }
        }
        node->SetOffset(offset);

        // decl is the last in the list, which is correct for size
        node->SetSize(decl->GetSize());
    }
  protected:
    int m_offset;
    int m_highwater;

    int RoundUp(int value)
    {
        if (value % WORD_SIZE == 0) return value;
        if (value < 0)
            return (value/WORD_SIZE) * WORD_SIZE - WORD_SIZE;
        else
            return (value/WORD_SIZE) * WORD_SIZE + WORD_SIZE;
    }

    static const int WORD_SIZE = 4;
};
