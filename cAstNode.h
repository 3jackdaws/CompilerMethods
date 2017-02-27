#pragma once
//**************************************
// cAstNode.h
//
// pure virtual base class for all AST nodes
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 7, 2016
//
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

#define print( x ) std::cout<< x << std::endl;
extern int yylineno; 
#include "cVisitor.h"

class cAstNode
{
    public:
        typedef vector<cAstNode*>::iterator iterator;

        cAstNode() {
            m_lineNumber = yylineno;
        }
        
        int GetLevel()
        {
            return m_level;
        }
        
        void SetLevel(int level)
        {
            m_level = level;
        }

        void AddChild(cAstNode *child)
        {
            m_children.push_back(child);
        }

        iterator FirstChild()
        {
            return m_children.begin();
        }

        iterator LastChild()
        {
            return m_children.end();
        }

        bool HasChildren()      { return !m_children.empty(); }

        int NumChildren()       { return (int)m_children.size(); }
        cAstNode* GetChild(int child)
        {
            if (child >= (int)m_children.size()) return nullptr;
            return m_children[child];
        }

        // return a string representation of the node
        string ToString() 
        {
            string result("");
            result += GetNodeLevelSpacing();
            result += "<" + NodeType();
            result += AttributesToString();

            if (HasChildren())
            {
                result += ">\n";
                iterator it;
                for (it=FirstChild(); it != LastChild(); it++)
                {
                    if ( (*it) != nullptr)
                    {
                        (*it)->SetLevel(m_level+2);
                        result += (*it)->ToString();
                    } 
                }
            }

            if (HasChildren()) 
            {
                result += GetNodeLevelSpacing();
                result += "</" + NodeType() + ">\n";
            }
            else
                result += "/>\n";

            return result;
        }
        
        void ClearChildNodes()
        {
            m_children.clear();
        }
        
        int LineNumber()
        {
            return m_lineNumber;
        }
        
        void SetHasError()
        {
            m_hasSemanticError = true;
        }
        

        virtual string AttributesToString()   { return string(""); }
        virtual string NodeType() = 0; //      { return "AST"; }
        virtual void Visit(cVisitor *visitor) = 0;

    protected:
        vector<cAstNode *> m_children;     // list of statements
        int m_level = 0;
        int m_lineNumber;
        bool m_hasSemanticError = false;
        
        string GetNodeLevelSpacing()
        {
            string spacing = "";
            for(int i = 0; i<m_level; i++){
                spacing.append(" ");
            }
            return spacing;
        }

};

