//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Program_Generate_Code_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_PROGRAM_GENERATE_CODE_1
#define CT_PROGRAM_GENERATE_CODE_1 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Program/Generate_Code.h"
#include "CT/Sequence/Kernel_1a.h"
   
///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

concrete_template <
        concrete_instance class Statement,
        /*!
            implements
                abstract_instance Statement_Kernel <Statement>
        !*/
        concrete_instance class Program_Base,
        /*!
            implements
                abstract_instance Program_Kernel <Statement>
        !*/
        concrete_instance class Compiled_Program =
            Sequence_Kernel_1a <Integer>
        /*!
            implements
	        abstract_instance Sequence_Kernel <Integer>
        !*/
    >
class Program_Generate_Code_1 :
    implements
        abstract_instance Program_Generate_Code <
                Statement,
                Compiled_Program
            >,
    extends
        concrete_instance Program_Base
{
private:

    local_procedure_body Generate_Code_Block_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind = BLOCK
	ensures
	    if IS_CONSISTENT_WITH_CONTEXT (stmnt, p.context)  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_BLOCK (
			   |#cp|, children (stmnt), p.context)
    !*/
    {
        // Students to fill this in
    }

    local_procedure_body Generate_Code_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind /= BLOCK
	ensures
	    if IS_CONSISTENT_WITH_CONTEXT (stmnt, p.context)  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_STATEMENT (
			   |#cp|, stmnt, p.context)
    !*/
    {
        // Students to fill this in
    }

    local_procedure_body Generate_Code_If_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind = IF
	ensures
	    if IS_CONSISTENT_WITH_CONTEXT (stmnt, p.context)  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_IF (
			   |#cp|, root (stmnt).test,
			   first (children (stmnt)), p.context)
    !*/
    {
	object Integer cond, jump, dummy;
	object Statement body;

	stmnt.Decompose_If (cond, body);

	Generate_Code_Test_Condition (cp, cond);

	jump = cp.Length ();
	cp.Add (jump, dummy);

	Generate_Code_Block_Statement (p, cp, body);

	cp[jump] = cp.Length ();

	stmnt.Compose_If (cond, body);
    }

    local_procedure_body Generate_Code_If_Else_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind = IF_ELSE
	ensures
	    if IS_CONSISTENT_WITH_CONTEXT (stmnt, p.context)  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_IF_ELSE (
			   |#cp|, root (stmnt).test,
			   first (children (stmnt)),
			   last (children (stmnt)), p.context)
    !*/
    {
        // Students to fill this in
    }

    local_procedure_body Generate_Code_While_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind = WHILE
	ensures
	    if IS_CONSISTENT_WITH_CONTEXT (stmnt, p.context)  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_WHILE (
			   |#cp|, root (stmnt).test,
			   first (children (stmnt)), p.context)
    !*/
    {
        // Students to fill this in
    }

    local_procedure_body Generate_Code_Call_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind = CALL
	ensures
	    if (IS_PRIMITIVE_INSTRUCTION (root (stmnt).instruction) or
		IS_DEFINED_IN (root (stmnt).instruction, p.context))  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_CALL (
			   |#cp|, root (stmnt).instruction,
			   p.context)
    !*/
    {
        // Students to fill this in
	object Text call;
	stmnt.Decompose_Call(call);
	if(Is_Primitive_Instruction(call) and not p.Is_In_Context(call)
	    
    }

    local_procedure_body Generate_Code_Primitive_Statement (
	    alters Compiled_Program& cp,
	    preserves Text inst
	)
    /*!
	requires
	    IS_PRIMITIVE_INSTRUCTION (inst)
	ensures
	    cp = #cp * GENERATE_INSTRUCTION_CODE (inst)
    !*/
    {
        if(inst.Is_Equal_To("move")) {
	    cp.Add(cp.Length(), MOVE);
	}
        else if(inst.Is_Equal_To("turnleft")) {
	    cp.Add(cp.Length(), TURNLEFT);
	}
        else if(inst.Is_Equal_To("turnright")) {
	    cp.Add(cp.Length(), TURNRIGHT);
	}
        else if(inst.Is_Equal_To("infect")) {
	    cp.Add(cp.Length(), INFECT);
	}
        else if(inst.Is_Equal_To("skip")) {
	    cp.Add(cp.Length(), SKIP);
	}
	else {
	    assert(Is_Primitive_Instruction(inst), "Expecting primitive instruction (ie 'move', 'turnleft', 'turnright', 'infect' or 'skip').");
	}
	
    }

    local_procedure_body Generate_Code_Test_Condition (
	    alters Compiled_Program& cp,
	    preserves Integer condition
	)
    /*!
	requires
	    IS_CONDITION (condition)
	ensures
	    cp = #cp * <GENERATE_TEST_CODE (condition)>
    !*/
    {
        case_select(condition){
	case(NEXT_IS_EMPTY):{
	    cp.Add(cp.Length(), JUMP_IF_NOT_NEXT_IS_EMPTY);
	}break;
	case(NEXT_IS_NOT_EMPTY):{
	    cp.Add(cp.Length(), JUMP_IF_NOT_NEXT_IS_NOT_EMPTY);
	}break;
	case(NEXT_IS_WALL):{
	    cp.Add(cp.Length(), JUMP_IF_NOT_NEXT_IS_WALL);
	}break;
	case(NEXT_IS_NOT_WALL):{
	    cp.Add(cp.Length(), JUMP_IF_NOT_NEXT_IS_NOT_WALL);
	}break;
	case(NEXT_IS_FRIEND):{
	    cp.Add(cp.Length(), JUMP_IF_NOT_NEXT_IS_FRIEND);
	}break;
	case(NEXT_IS_NOT_FRIEND):{
	    cp.Add(cp.Length(), JUMP_IF_NOT_NEXT_IS_NOT_FRIEND);
	}break;
	case(NEXT_IS_ENEMY):{
	    cp.Add(cp.Length(), JUMP_IF_NOT_NEXT_IS_ENEMY);
	}break;
	case(NEXT_IS_NOT_ENEMY):{
	    cp.Add(cp.Length(), JUMP_IF_NOT_NEXT_IS_NOT_ENEMY);
	}break;
	case(RANDOM):{
	    cp.Add(cp.Length(), JUMP_IF_NOT_RANDOM);
	}break;
	case(TRUE):{
	    cp.Add(cp.Length(), JUMP_IF_NOT_TRUE);
	}break;
	default:{
	    assert(false, "Expecting condition");
	}
	}
	    
    }

    local_function_body Boolean Is_Primitive_Instruction (
	    preserves Text inst
	)
    /*!
	ensures
	    Is_Primitive_Instruction = IS_PRIMITIVE_INSTRUCTION (inst)
    !*/
    {
        // {"move", "turnleft", "turnright", "infect", "skip"}
	return inst.Is_Equal_To("move") or 
	       inst.Is_Equal_To("turnleft") or 
	       inst.Is_Equal_To("turnright") or 
	       inst.Is_Equal_To("infect") or 
	       inst.Is_Equal_To("skip");
    }

public:
    
    procedure_body Generate_Code (
	    produces Compiled_Program& cp
	)
    {
        // Students to fill this in
    }

};

#endif // CT_PROGRAM_GENERATE_CODE_1
