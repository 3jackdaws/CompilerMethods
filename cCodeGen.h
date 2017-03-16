#include "cVisitor.h"
#include "emit.h"

class cCodeGen : public cVisitor
{
  public:
    cCodeGen(string filename) : cVisitor()
    {
        InitOutput(filename);
    }

    void VisitAllNodes(cAstNode *node) { node->Visit(this); }

    // virtual void Visit(cArrayDeclNode *node);
    // virtual void Visit(cAstNode *node);
    virtual void Visit(cAssignNode *node){
        node->GetExpr()->Visit(this);
        // EmitString("POPVAR " + std::to_string(node->GetLVal()->GetOffset()) + "\n");
        PutAddressOfVariableOnTopOfStack(node->GetLVal());
        EmitString("POPVARIND\n");
    }
    virtual void Visit(cBinaryExprNode *node){
        VisitAllChildren(node);
        switch(node->GetOp()->GetOperator())
        {
            case '+':
            {
                EmitString("PLUS\n");
                break;
            }
            case '-':
            {
                EmitString("MINUS\n");
                break;
            }
            case '*':
            {
                EmitString("TIMES\n");
                break;
            }
            case '/':
            {
                EmitString("DIVIDE\n");
                break;
            }
            case '%':
            {
                EmitString("MOD\n");
                break;
            }
            case EQUALS:
            {
                EmitString("EQ\n");
                break;
            }
           
        }
    }
    virtual void Visit(cBlockNode *node){
        int size = node->GetSize();
        EmitString("ADJSP " + std::to_string(size) + "\n");
        VisitAllChildren(node);
        EmitString("ADJSP " + std::to_string(-size) + "\n");
    }
    // virtual void Visit(cDeclNode *node);
    // virtual void Visit(cDeclsNode *node);
    // virtual void Visit(cExprNode *node);
    virtual void Visit(cFloatExprNode *node){
        EmitString("PUSH " + std::to_string(node->GetValue()) + "\n");
    }
    virtual void Visit(cFuncDeclNode *node){
        string func_name = node->GetName()->GetName();
        StartFunctionOutput(func_name);
        cDeclsNode * parameters = node->GetParams();
        cDeclsNode * localvars = node->GetLocals();
        
        int param_size = 0;
        int localvar_size = 0;
        
        if(parameters) param_size = parameters->GetSize(); //if parameters, adjust SP
        if(localvars) localvar_size = localvars->GetSize();
        
        EmitString("ADJSP " + std::to_string(param_size + localvar_size) + "\n");
        
        if(node->GetStmts()) node->GetStmts()->Visit(this);
        
        EmitString("ADJSP -" + std::to_string(param_size + localvar_size) + "\n");
        
        EndFunctionOutput();
    }
    virtual void Visit(cFuncExprNode *node){
        cParamListNode * params = node->GetParams();
        int num_params = 0;
        int param_size = 0;
        
        if(params){
            num_params = params->NumChildren();
            param_size = params->GetSize();
        }
        string func_name = node->GetName()->GetName();
        EmitString("ADJSP " + std::to_string(param_size) + "\n");
        for(int i = num_params-1 ; i>=0; i--)
        {
            params->GetParam(i)->Visit(this);
        }
        EmitString("CALL @" + func_name + "\n");
    }
    virtual void Visit(cIfNode *node)
    {
        cExprNode * condition = node->GetCondition();
        
        cStmtsNode * if_stmts = node->GetIfStmts();
        
        cStmtsNode * else_stmts = node->GetElseStmts();
        
        condition->Visit(this);
        
        string else_label = GenerateLabel();
        
        string end_label = GenerateLabel();
        
        EmitString("JUMPE @" + else_label + "\n");
        VisitAllChildren(if_stmts);
        EmitString("JUMP @"+end_label +"\n");
        EmitString(else_label + ":\n");
        if(else_stmts) VisitAllChildren(else_stmts);
        EmitString(end_label + ":\n");
    }
    virtual void Visit(cIntExprNode *node){
        EmitString("PUSH " + std::to_string(node->GetValue()) + "\n");
    }
    // virtual void Visit(cOpNode *node);
    // virtual void Visit(cParamListNode *node);
    // virtual void Visit(cParamsNode *node);
    virtual void Visit(cPrintNode *node){
        VisitAllChildren(node);
        EmitString("CALL @print\n");
        EmitString("POP\n");
        EmitString("POP\n");
    }
    virtual void Visit(cProgramNode *node){
        VisitAllChildren(node);
        FinalizeOutput();
    }
    virtual void Visit(cReturnNode *node){
        VisitAllChildren(node);
        EmitString("RETURNV\n");
    }
    // virtual void Visit(cStmtNode *node);
    // virtual void Visit(cStmtsNode *node);
    // virtual void Visit(cStructDeclNode *node);
    // virtual void Visit(cSymbol *node);
    virtual void Visit(cVarDeclNode *node){
        int offset = node->GetOffset();
        EmitString("PUSH 0\n");
        EmitString("POPVAR " + std::to_string(offset) + "\n");
    }
    virtual void Visit(cVarExprNode *node){
        PutAddressOfVariableOnTopOfStack(node);
        EmitString("PUSHVARIND\n");
    }
    virtual void Visit(cWhileNode *node){
        cExprNode * condition = node->GetCondition();
        
        cStmtNode * stmt = node->GetStmt();
        
        string start_label = GenerateLabel();
        string end_label = GenerateLabel();
        
        EmitString(start_label + ":\n");
        
        condition->Visit(this);
        
        
        EmitString("JUMPE @" + end_label + "\n");
        
        VisitAllChildren(stmt);
        
        EmitString("JUMP @"+start_label + "\n");
        
        EmitString(end_label + ":\n");
    }
  protected:
    void PutAddressOfVariableOnTopOfStack(cVarExprNode * node){
        int initial_offset = node->GetOffset();
        int base_type_size = node->GetType()->GetSize();
        cExprNode * first_index = node->GetIndex(0);
        EmitString("PUSHFP\n");
        EmitString("PUSH " + std::to_string(initial_offset) + "\n");
        EmitString("PLUS\n");
        if(first_index){
            first_index->Visit(this);
            EmitString("PUSH " + std::to_string(base_type_size) + "\n");
            EmitString("TIMES\n");
            EmitString("PLUS\n");
        }else{
            
        }
        EmitString(";" + node->GetTextName() + "\n");
        // EmitString("CALL @print\n");
        // EmitString("POP\n");
    }
};
    

   
