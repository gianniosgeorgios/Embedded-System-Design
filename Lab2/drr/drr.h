//define SLL_CL
//#define DLL_CL
#define DYN_ARR_CL

//#define SLL_PK
//#define DLL_PK
#define DYN_ARR_PK

#if defined(SLL_CL) || defined(SLL_PK)
#include "../synch_implementations/cdsl_queue.h"
#endif
#if defined(DLL_CL) || defined(DLL_PK)
#include "../synch_implementations/cdsl_deque.h"
#endif
#if defined(DYN_ARR_CL) || defined(DYN_ARR_PK)
#include "../synch_implementations/cdsl_dyn_array.h"
#endif

typedef struct Packet_struct {
	unsigned int src; 
  	unsigned int dst;  
  	unsigned int size; 
} Packet;

typedef struct Node_struct { 
  	unsigned int src_ip; //source IP of the node
  	unsigned int dst_ip; //destination IP of the node
  	unsigned int no_of_packets;
	unsigned int deficit;
#if defined(SLL_PK)
	cdsl_sll *pList;
#elif defined(DLL_PK)
	cdsl_dll *pList;
#else
	cdsl_dyn_array *pList;
#endif
} Node; 

