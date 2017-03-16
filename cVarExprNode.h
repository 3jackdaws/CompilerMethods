#pragma once
//**************************************
// cVarExprNode.h
//
// Defines AST node for a variable reference
//
// Inherits from cExprNode so variable refs can be used in expressions`
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cSymbol.h"
#include "cAstNode.h"
#include "cExprNode.h"

class cVarExprNode : public cExprNode
{
    public:
        // param is the symbol for the variable
        cVarExprNode(cSymbol *name)
            : cExprNode()
        {
            AddChild(name);
        }

        // called for the fields in struct refs
        void AddElement(cSymbol *name)
        {
            AddChild(name);
        }

        void AddElement(cExprNode *index)
        {
            AddChild(index);
        }

        cSymbol* GetName() 
        {
            return static_cast<cSymbol*>(GetChild(0));
        }

        // return a string representation of the name of the var
        virtual string GetTextName()
        {
            string name("");
            cSymbol* sym;

            sym = GetName();

            name += sym->GetName();

            for (int ii=0; ii<NumItems(); ii++)
            {
                if (ItemIsIndex(ii))
                {
                    name += "[]";
                }
                else
                {
                    sym = GetElement(ii);
                    name += "." + sym->GetName();
                }
            }

            return name;
        }
        virtual cDeclNode *GetType() 
        { 
            cDeclNode* type = GetName()->GetDecl()->GetType();

            if (type->IsArray())
            {
                return type->GetType(NumItems());
            }
            else
            {
                return type; 
            }
        }

        int NumItems() { return NumChildren() - 1; }

        bool ItemIsIndex(int index)
        {
            // if the dynamic cast fails, this item must be a cSymbol* for
            // a struct member
            return dynamic_cast<cExprNode*>(GetChild(index + 1)) != nullptr;
        }

        cSymbol* GetElement(int index)
        {
             return (cSymbol*)GetChild(index + 1);
        }

        cExprNode* GetIndex(int index)
        {
             return (cExprNode*)GetChild(index + 1);
        }

        void SetSize(int size)      { m_size = size; }
        void SetOffset(int offset)  { m_offset = offset; }
        int GetSize()               { return m_size; }
        int GetOffset()             { return m_offset; }

        void AddRowSize(int size) { m_arrayRowSizes.push_back(size); }
        int  GetRowSize(int index) { return m_arrayRowSizes[index]; }

        virtual string AttributesToString()
        {
            if (m_size != 0 || m_offset != 0)
            {
                std::string result;
                result = " size=\"" + std::to_string(m_size) + "\" offset=\"" +
                    std::to_string(m_offset) + "\"";
                if (m_arrayRowSizes.size() > 0)
                {
                    result += " rowsizes=\"";

                    for (int ii : m_arrayRowSizes)
                    {
                        result += std::to_string(ii) + " ";
                    }

                    result.pop_back(); // remove trailing space
                    result += "\"";
                }
                return result;
            }
            else
            {
                return "";
            }
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        int m_size;
        int m_offset;
        vector<int> m_arrayRowSizes;
};
