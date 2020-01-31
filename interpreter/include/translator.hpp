#pragma once
#include <iostream>
#include <map>
#include <string>
namespace vm {
	enum InsTag:char {
		// bin_op sub_ins op1,op2 
		/*
			sub_ins First Bit, 0-> i8
					  1-> i16
					  2-> i32
					  3-> i64
					  4-> r32
					  5-> r64
					  6-> r128
					Second Bit, 
					0-> imm op imm
					1-> add op add
					2-> imm op add
					3-> add op imm
		*/
		ADD=0x01,SUB,MUL,DIV,
		EQ,NE,GT,GE,LE,LT,
		AND,OR,W8,W16,W32,W64,WR128,
		// sub_ins 
		/*
			0-> common
			1-> Expr
		*/
		JMP,CALL
	};

	extern std::string ir_content;
	extern int ir_index;
	extern int line_no;
	extern std::map<std::string, void(*)()> parsing_table;
	extern std::string cur_instruction; // cur instruction name

	
	//======================================================
	void match(char ch);


	void parsing();
	std::string extract_word();
	
	void parse_bin();

	class Error {
	public:
		Error(const std::string &str) :err_msg(str), line(line_no) {}
		std::string what() { return "<line:" + std::to_string(line) + ">" + err_msg; }
	private:
		std::string err_msg;
		int line;
	};
	// to store the bin info of the imm or var add.
	struct InsData {
		InsData(char *i, int len) :info(i), length(len) {}
		int length;
		char *info;
		~InsData() { delete[] info; }
	};
}