#pragma once

#include <inttypes.h>

const char* name_header = "Kaydara FBX Binary  \x00\x1A\x00"
											  "\xC4\x1C\x00\x00";

typedef struct
{
	uint32_t EndOffset;
	uint32_t PropertyCount;
	uint32_t PropertyListLength;

	uint8_t NameLength;
	char* Name; // repalse whan riting binary file

	int nodeCount;
	node* Nodes; // repalse whan riting binary file

} S_NodeHeader;

class node
{
public:
	S_NodeHeader Header;



};