
#ifndef _DRR_C_
#define _DRR_C_

#include <stdio.h>
#include "drr.h"
#include "trace.h"

#ifndef _FUNCTIONS_INSTANTIATIONS_
#define _FUNCTIONS_INSTANTIATIONS_
// Creates a new packet:
Packet* get_next_packet(unsigned int psrc_ip, unsigned int pdst_ip, unsigned int size);
// Finds the node that holds the packet with the lowest finish time:
Node* min_fin_node(Node* node_head);
Node* find_node(Packet* packet, Node* node_head);
void insert_packet(Packet* packet, Node* node);
Packet* forward_packet(Node* node_head);
#endif

#define QUANTUM 9216 // the value to be added to increment the deficit see CISCO router
#define DEFICIT 16384 //initial value of deficit in a newly created node see CISCO router

#if defined(SLL_CL)
cdsl_sll *clientList;
#elif defined(DLL_CL)
cdsl_dll *clientList;
#else
cdsl_dyn_array *clientList;
#endif

/**********  MAIN  FUNCTION  **********/
int main(int argc, char **argv) {
	int k, i;
	// The node_head:
	Node* node_head = (Node*)malloc(sizeof(Node));
	node_head->src_ip = 0;
	node_head->dst_ip = 0;
	node_head->no_of_packets = 0;
	node_head->deficit = 0;
	Node *v;
	// A packet:
	Packet* packet = NULL;
#if defined (SLL_CL)
	iterator_cdsl_sll it, end;
	clientList = cdsl_sll_init();
#elif defined (DLL_CL)
	iterator_cdsl_dll it, end;
	clientList = cdsl_dll_init();
#else 
	iterator_cdsl_dyn_array it, end;
	clientList = cdsl_dyn_array_init();	
#endif
	unsigned a=0;
	int rounds = 1783;

	while (a < rounds) {
		//printf("round: %d\n", a);
		a++;

		for (k = 0; k < mallocs[a]; k++) {
			packet = get_next_packet(psrc[a], pdst[a], psize[a]);
			Node* n = find_node(packet, node_head);
			insert_packet(packet, n);		
		}
		it = clientList->iter_begin(clientList);
		end = clientList->iter_end(clientList);

		//printf("---------------------\n");
		for (;it != end; it = clientList->iter_next(it)) {		
			v = (Node*)(clientList->iter_deref(clientList, it));
			//printf("node: %d with deficit: %d\n", v->src_ip, v->deficit);
		}
		//printf("---------------------\n");
		for (k = 0; k < frees[a]; k++) {
			Packet* forwarded_packet = forward_packet(node_head);
			if(forwarded_packet!=NULL)
			{	
				//printf("forwarded with: %d\n", forwarded_packet->size);
				free(forwarded_packet);
			}
		}
	}
	return 0;
}

#ifndef _GET_NEXT_PACKET_
#define _GET_NEXT_PACKET_
Packet* get_next_packet(unsigned int psrc_ip, unsigned int pdst_ip, unsigned int size)
{ 
	Packet *npacket = (Packet*)malloc(sizeof(Packet));
	npacket->src = psrc_ip;
	npacket->dst = pdst_ip;
	npacket->size = size;
	return npacket;
}
#endif

#ifndef _FIND_NODE_
#define _FIND_NODE_
Node* find_node(Packet* packet, Node* node_head)
{
	// Find the destination:
	Node *v;
#if defined (SLL_CL)
	iterator_cdsl_sll it, end;
#elif defined (DLL_CL)
	iterator_cdsl_dll it, end;
#else
	iterator_cdsl_dyn_array it, end;
#endif
	it = clientList->iter_begin(clientList);
	end = clientList->iter_end(clientList);
	for (;it != end; it = clientList->iter_next(it)) {
		v = (Node*)(clientList->iter_deref(clientList, it));
		if((v->src_ip == packet->src) && (v->dst_ip == packet->dst)) {
			return v;
		}
	}
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->src_ip = packet->src;
	new_node->dst_ip = packet->dst;
	new_node->no_of_packets = 0;
	new_node->deficit = DEFICIT;
#if defined (SLL_PK)
	new_node->pList = cdsl_sll_init();
#elif defined (DLL_PK)
	new_node->pList = cdsl_dll_init();
#else 
	new_node->pList = cdsl_dyn_array_init();
#endif
	clientList->enqueue(0, clientList, (void*)new_node);

	return new_node;
}
#endif

#ifndef _INSERT_PACKET_
#define _INSERT_PACKET_
void insert_packet(Packet* packet, Node* node) {
	if(node->no_of_packets == 0) {
		node->no_of_packets++;
		node->pList->enqueue(0, node->pList, (void*)packet);
		return;
	}
	else {		
		node->no_of_packets++;
		//place the packet in the last position of the packet list
		node->pList->enqueue(0, node->pList, (void*)packet);
	}
}
#endif

#ifndef _FORWARD_PACKET_
#define _FORWARD_PACKET_
Packet* forward_packet(Node* node_head) {
	Node *v;
	Packet* first_packet = NULL;
#if defined (SLL_CL)
	iterator_cdsl_sll it, end;
#elif defined (DLL_CL)
	iterator_cdsl_dll it, end;
#else
	iterator_cdsl_dyn_array it, end;
#endif
	it = clientList->iter_begin(clientList);
	end = clientList->iter_end(clientList);
	//increment the deficit in each node by QUANTUM
	for (;it != end; it = clientList->iter_next(it)) {
		v = (Node*)(clientList->iter_deref(clientList, it));
		v->deficit += QUANTUM;
	}
	it = clientList->iter_begin(clientList);
	for (;it != end; it = clientList->iter_next(it)) {
		v = (Node*)(clientList->iter_deref(clientList, it));
		if(v != NULL && v->src_ip != 0 && v->no_of_packets > 0) { //making sure it is not the deficit_head	
			first_packet = v->pList->get_head(0, v->pList);
			if(v->deficit >= first_packet->size) {
				v->deficit -= first_packet->size;
				v->no_of_packets--;
				v->pList->dequeue(0, (v->pList));
				if (v->no_of_packets == 0) {
					clientList->remove(0, clientList, v);
				}
			}
		}
	}
	return first_packet;
}
#endif

#endif
