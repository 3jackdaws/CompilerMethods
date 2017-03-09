#pragma once

#include "cVisitor.h"


class cSizeOffsetVisitor : public cVisitor
{
public:
    cSizeOffsetVisitor() : cVisitor()
    {
        
    }
    
    void VisitAllNodes(cAstNode* node) { node->Visit(this); }
    
    void Visit(cProgramNode * node)
    {
        VisitAllChildren(node);
        cBlockNode * first_block = node->GetBlock();
        first_block->SetSize(WordPad(first_block->GetSize()));
    }
    
    void Visit(cBlockNode* node)
    {
        int n_size     = m_current_size;
        int offset     = m_current_offset;
        int max_size   = m_max_size;
        
        m_max_size     = 0;
        m_current_size = 0;
        
        VisitAllChildren(node);
        
        int computed_size = m_current_size + m_max_size;
        
        m_max_size = computed_size > max_size ? computed_size : max_size;
        
        // if(offset == 0){
        //     computed_size = WordPad(computed_size);
        // }
        node->SetSize(computed_size);
       
        m_current_offset = offset;
        m_current_size = n_size;
    }
    
    void Visit(cDeclsNode* node)
    {
        VisitAllChildren(node);
        node->SetSize(m_current_size);
    }
    
    void Visit(cFuncDeclNode* node)
    {
        int max_size = m_max_size;
        int offset = m_current_offset;
        int n_size = m_current_size;
        
        
        m_max_size = 0;
        m_current_size = 0;
        m_current_offset = 0;
        
        VisitAllChildren(node);
        int computed_size = m_current_size + m_max_size;
        computed_size = WordPad(computed_size);
        node->SetSize(computed_size);
        
        m_max_size = max_size;
        m_current_size = n_size;
        m_current_offset = offset;
    }
    
    void Visit(cVarDeclNode* node)
    {
        int node_size = node->GetType()->Sizeof();
        
        
        if (m_offset_direction > 0)
        {
            if (node_size > 1)
            {
                while (m_current_offset % 4)
                {
                    m_current_offset++;
                    m_current_size++;
                }
                // m_current_offset = WordPad(m_current_offset);
                // m_current_size = WordPad(m_current_size);
            }
            
            node->SetOffset(m_current_offset);
            
            m_current_offset += node_size;
            m_current_size += node_size;
        }
        else// if (m_offset_direction < 0)
        {
            int pad_size = node_size < 4 ? 4 : node_size;
            
            m_current_size   += pad_size;
            m_current_offset -= pad_size;
            node->SetOffset(m_current_offset);
            
        }
        
        node->SetSize(node_size);
    }
    
    
    
    void Visit(cParamsNode* node)
    {
        int max_size = m_max_size;
        int offset = m_current_offset;
        int n_size = m_current_size;
        
        
        m_offset_direction = -1;
        
        m_max_size = 0;
        m_current_size = 0;
        m_current_offset = -8;
        
        VisitAllChildren(node);
        int computed_size = m_current_size;
        while (computed_size % 4) computed_size++;
        node->SetSize(computed_size);
        
        m_offset_direction = 1;
        
        m_max_size = max_size;
        m_current_size = n_size;
        m_current_offset = offset;
    }
    
    void Visit(cParamListNode* node)
    {
        m_current_varrefs = 0;
        
        VisitAllChildren(node);
        node->SetSize(m_current_varrefs);
    }
    
    
    void Visit(cVarExprNode* node)
    {
        m_current_varrefs += node->GetSize();
    }
    
protected:

    int WordPad(int val)
    {
        int diff = val % 4;
        return diff == 0 ? val : val + (4 - diff ); 
    }
    
    
    int m_current_size     = 0;
    int m_current_offset   = 0;
    int m_max_size         = 0;
    int m_offset_direction = 1;
    int m_current_varrefs  = 0;
    
};
