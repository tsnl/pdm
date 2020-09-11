#ifndef INCLUDED_CONFIG_H
#define INCLUDED_CONFIG_H

#define MAX_ID_LEN (256)

#define DEBUG (1)

// Tune these two parameters to allocate memory for the AST.
#define MAX_AST_NODE_COUNT (64 * 1024)
#define MAX_AST_LIST_COUNT (64 * 1024)
#define MAX_AST_NODES_PER_LIST (4)
#define MAX_IDS_PER_SHARED_FIELD (128)

#define MAX_JOB_COUNT (16)
#define MAX_SCOPER_COUNT (16)


#endif  // INCLUDED_CONFIG_H