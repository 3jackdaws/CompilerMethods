#pragma once
//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//

#include "cDeclNode.h"

class cStructDeclNode : public cDeclNode
{
    public:
        cStructDeclNode(cDeclsNode * decls, cSymbol * name) : cDeclNode() 
        {
            AddChild(decls);
            AddChild(name);
        }
        
        // Add a decl to the list
        void Insert(cDeclNode *decl)
        {
            AddChild(decl);
        }

        virtual string NodeType() { return string("struct_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
