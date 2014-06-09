#ifndef ETHSERP_UTIL
#define ETHSERP_UTIL

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <cerrno>

const int TOKEN = 0,
          ASTNODE = 1,
          SPACE = 2,
          BRACK = 3,
          SQUOTE = 4,
          DQUOTE = 5,
          SYMB = 6,
          ALPHANUM = 7,
          LPAREN = 8,
          RPAREN = 9,
          COMMA = 10,
          COLON = 11,
          UNARY_OP = 12,
          BINARY_OP = 13,
          COMPOUND = 14;

// Stores metadata about each token
struct Metadata {
    std::string file;
    int ln;
    int ch;
};
Metadata metadata(std::string file="main", int ln=0, int ch=0);

std::string mkUniqueToken();

// type can be TOKEN or ASTNODE
struct Node {
    int type;
    std::string val;
    std::vector<Node> args;
    Metadata metadata;
};
Node token(std::string val, Metadata met=metadata());
Node astnode(std::string val, std::vector<Node> args, Metadata met=metadata());

// Print token list
std::string printTokens(std::vector<Node> tokens);

// Prints a lisp AST on one line
std::string printSimple(Node ast);

// Pretty-prints a lisp AST
std::string printAST(Node ast);

// Splits text by line
std::vector<std::string> splitLines(std::string s);

// Inverse of splitLines
std::string joinLines(std::vector<std::string> lines);

// Indent all lines by 4 spaces
std::string indentLines(std::string inp);

// Does the node contain a number (eg. 124, 0xf012c, "george")
bool isNumberLike(Node node);

//Normalizes number representations
Node nodeToNumeric(Node node);

//If a node is numeric, normalize its representation
Node tryNumberize(Node node);

//Converts a value to an array of byte number nodes
std::vector<Node> toByteArr(std::string val, Metadata metadata);

//Reads a file
std::string get_file_contents(std::string filename);

//Does a file exist?
bool exists(std::string fileName);

//Report error
void err(std::string errtext, Metadata met);

#endif