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

#include "cAstNode.h"

class cVarDeclNode : public cDeclNode
{
    public:
        cVarDeclNode(cSymbol * type, cSymbol * name) : cDeclNode() {
            // print( type->GetName() );
            // print( name->GetName() );
            AddChild(type);
            AddChild(name);
        }

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
