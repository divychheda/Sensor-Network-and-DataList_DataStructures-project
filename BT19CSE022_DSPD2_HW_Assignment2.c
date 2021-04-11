// BT19CSE022
// Divy Chheda

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#define MAX 3   // max number of keys in node
#define MIN (int)ceil(MAX/2) 
#define ORDER_LEAF 3
#define MIN_DATA (int)ceil(ORDER_LEAF/2)

int NumRecords = 0;
struct date
{
	int dd;
	int mm;
	int yyyy;
};

int smaller(struct date a, struct date b)  // compares two dates  
{                                           // used in retreive data between date range
int flag = 0;
  if (a.yyyy < b.yyyy) 
    flag = 1; 
  else if (a.yyyy == b.yyyy && a.mm < b.mm) 
    flag = 1; 
  else if (a.yyyy == b.yyyy && a.mm == b.mm && a.dd < b.dd) 
    flag = 1; 
  return flag;
}

typedef struct data_node
{
    int sensor_id;
    char sensor_type;
    char sensor_station;
    float interval;
    float distance_btn_stations;
}S_data;

typedef struct sensor_repo
{
    int sensor_id;
    struct date dt;
    float time;
    float data;
}R_data;

typedef struct node_tag
{
    union b_plus_tree
    {
        struct key_nodes
        {
            int sensor_id[MAX];
            struct node_tag* ptr[MAX+1];
			int count;
        }key;
    	struct data_nodes
        {
            S_data arr[ORDER_LEAF];
            struct node_tag* next;
            struct node_tag* prev;
            int dataCount;
        }data;
    }u;
    char flag;
}Node;

typedef struct repo_node_tag
{
    union b_plus_tree_repo
    {
        struct key_repo_nodes
        {
            int sensor_id[MAX];
            struct repo_node_tag* ptr[MAX+1];
			int count;
        }key;
    	struct data_repo_nodes
        {
            R_data arr[ORDER_LEAF];
            struct repo_node_tag* next;
            struct repo_node_tag* prev;
            int dataCount;
        }data;
    }u;
    char flag;
}RepoNode;

int i;

// ------------------ question 1 -------------------------------------
void insertInDataNode(S_data sensor_data,Node *root)
{
	int i=root->u.data.dataCount-1;
	if(root->flag=='d')
	{
		while(root->u.data.arr[i].sensor_id>=sensor_data.sensor_id && i>=0)
		{
			root->u.data.arr[i+1]=root->u.data.arr[i];
			i--;
		}
		root->u.data.arr[i+1]=sensor_data;
	}
	root->u.data.dataCount++;
	NumRecords++;
}

void insertInRepoDataNode(R_data sensor_data,RepoNode *root)
{
	int i=root->u.data.dataCount-1;
	if(root->flag=='d')
	{
		while(root->u.data.arr[i].sensor_id>=sensor_data.sensor_id && i>=0)
		{
			root->u.data.arr[i+1]=root->u.data.arr[i];
			i--;
		}
		root->u.data.arr[i+1]=sensor_data;
	}
	root->u.data.dataCount++;
	NumRecords++;
}

void insertInKey(int id,Node *root,Node *right_subtree,int pos)
{
	int i;
	for(i=root->u.key.count;i>pos;i--)
	{
		root->u.key.sensor_id[i+1]=root->u.key.sensor_id[i];
		root->u.key.ptr[i+1]=root->u.key.ptr[i];
	}
	root->u.key.sensor_id[pos+1]=id;
	root->u.key.ptr[pos+1]=right_subtree;
	root->u.key.count++;
}
void insertInRepoKey(int id,RepoNode *root,RepoNode *right_subtree,int pos)
{
	int i;
	for(i=root->u.key.count;i>pos;i--)
	{
		root->u.key.sensor_id[i+1]=root->u.key.sensor_id[i];
		root->u.key.ptr[i+1]=root->u.key.ptr[i];
	}
	root->u.key.sensor_id[pos+1]=id;
	root->u.key.ptr[pos+1]=right_subtree;
	root->u.key.count++;
}

void splitLeafNode(S_data sensor_data,Node *root,Node **right_subtree,int* id)
{
     S_data virtual_node[MAX+1];
     Node *leaf_right;
     int i=0,j,k=0;
     while(sensor_data.sensor_id>root->u.data.arr[i].sensor_id && i<root->u.data.dataCount)
     {
        virtual_node[i]=root->u.data.arr[i];
        i++;
     }
     virtual_node[i]=sensor_data;
     while(i<=root->u.data.dataCount)
     {
        virtual_node[i+1]=root->u.data.arr[i];
        i++;
     }

     *id=virtual_node[i/2].sensor_id;
     root->u.data.dataCount=(int)ceil((double)root->u.data.dataCount/2);
     leaf_right=(Node *)malloc(sizeof(Node));
     leaf_right->flag='d';
     leaf_right->u.data.dataCount=i-root->u.data.dataCount;
     
     for(j=0;j<i/2;j++)
     {
         root->u.data.arr[j]=virtual_node[j];

     }
     for(j=i/2;j<i;j++)
     {
        leaf_right->u.data.arr[k]=virtual_node[j];
        k++;
     }
     if(root->u.data.next!=NULL)
     {
     	(root->u.data.next)->u.data.prev=leaf_right;
	 }

     leaf_right->u.data.next=root->u.data.next;
     root->u.data.next=leaf_right;
     leaf_right->u.data.prev=root;
     *right_subtree=leaf_right;
     NumRecords++;
}
void splitLeafRepoNode(R_data sensor_data,RepoNode *root,RepoNode **right_subtree,int* id)
{
     R_data virtual_node[MAX+1];
     RepoNode *leaf_right;
     int i=0,j,k=0;
     while(sensor_data.sensor_id>root->u.data.arr[i].sensor_id && i<root->u.data.dataCount)
     {
        virtual_node[i]=root->u.data.arr[i];
        i++;
     }
     virtual_node[i]=sensor_data;
     while(i<=root->u.data.dataCount)
     {
        virtual_node[i+1]=root->u.data.arr[i];
        i++;
     }

     *id=virtual_node[i/2].sensor_id;
     root->u.data.dataCount=(int)ceil((double)root->u.data.dataCount/2);
     leaf_right=(RepoNode *)malloc(sizeof(RepoNode));
     leaf_right->flag='d';
     leaf_right->u.data.dataCount=i-root->u.data.dataCount;
     
     for(j=0;j<i/2;j++)
     {
         root->u.data.arr[j]=virtual_node[j];

     }
     for(j=i/2;j<i;j++)
     {
        leaf_right->u.data.arr[k]=virtual_node[j];
        k++;
     }
     if(root->u.data.next!=NULL)
     {
     	(root->u.data.next)->u.data.prev=leaf_right;
	 }

     leaf_right->u.data.next=root->u.data.next;
     root->u.data.next=leaf_right;
     leaf_right->u.data.prev=root;
     *right_subtree=leaf_right;
     NumRecords++;
}

void splitKeyNode(int median_entry,Node *right_of_median,Node *root,int pos, int *newmedian,Node **newright)
{
	int i;
	int median;
											//to find the correct position of the median
	if(pos<=MIN)
	{
		median=MIN;
	}
	else
	{
		median=MIN+1;
	}
	*newright=(Node *)malloc(sizeof(Node));
	      								
	for(i=median+1;i<=MAX;i++)
	{
		(*newright)->u.key.sensor_id[i-median]=root->u.key.sensor_id[i];
		(*newright)->u.key.ptr[i-median]=root->u.key.ptr[i];
	}
	(*newright)->flag='k';
	(*newright)->u.key.count=MAX-median;
	root->u.key.count=median;
	if(pos<=MIN)
	{
		insertInKey(median_entry,root,right_of_median,pos);
	}
	else
	{
		insertInKey(median_entry,*newright,right_of_median,pos-median);
	}
	*newmedian=root->u.key.sensor_id[root->u.key.count];
	(*newright)->u.key.ptr[0]=root->u.key.ptr[root->u.key.count];
	root->u.key.count--;

}
void splitKeyRepoNode(int median_entry,RepoNode *right_of_median,RepoNode *root,int pos, int *newmedian,RepoNode **newright)
{
	int i;
	int median;
											//to find the correct position of the median
	if(pos<=MIN)
	{
		median=MIN;
	}
	else
	{
		median=MIN+1;
	}
	*newright=(RepoNode *)malloc(sizeof(RepoNode));
	      								
	for(i=median+1;i<=MAX;i++)
	{
		(*newright)->u.key.sensor_id[i-median]=root->u.key.sensor_id[i];
		(*newright)->u.key.ptr[i-median]=root->u.key.ptr[i];
	}
	(*newright)->flag='k';
	(*newright)->u.key.count=MAX-median;
	root->u.key.count=median;
	if(pos<=MIN)
	{
		insertInRepoKey(median_entry,root,right_of_median,pos);
	}
	else
	{
		insertInRepoKey(median_entry,*newright,right_of_median,pos-median);
	}
	*newmedian=root->u.key.sensor_id[root->u.key.count];
	(*newright)->u.key.ptr[0]=root->u.key.ptr[root->u.key.count];
	root->u.key.count--;
}


int PushDown(int id, Node *root, int *median, Node **right_subtree,S_data sensor_data)
{
	int pos,i=0;
	int found=0;
	if(root->flag=='d')
	{
		while(root->u.data.arr[i].sensor_id<id && i<root->u.data.dataCount)
		{
			i++;
		}
		if(root->u.data.arr[i].sensor_id==id)
		{
			root->u.data.arr[i]=sensor_data;
		}
		else
		{
			if(root->u.data.dataCount<ORDER_LEAF)
			{
				insertInDataNode(sensor_data,root);
				return 0;
			}
			else
			{
				splitLeafNode(sensor_data,root,right_subtree,median);
				return 1;
			}
		}
	}
	else if(root->flag=='k')
	{
		if(root->flag=='k')
		{
			if(id<root->u.key.sensor_id[1])
			{
				pos=0;
			}
			else
			{
				for(pos=root->u.key.count;id<root->u.key.sensor_id[pos];pos=pos-1);
			}
		}
		if(PushDown(id,root->u.key.ptr[pos],median,right_subtree,sensor_data))
		{
		    id=*median;
			if(root->u.key.count<MAX)
			{
				insertInKey(id,root,*right_subtree,pos);
				return 0;
			}
			else
			{
				splitKeyNode(id,*right_subtree,root,pos,median,right_subtree);
				return 1;
			}
		}
		return 0;
	}
}

int PushDownRepoNode(int id, RepoNode *root, int *median, RepoNode **right_subtree,R_data sensor_data)
{
	int pos,i=0;
	int found=0;
	if(root->flag=='d')
	{
		while(root->u.data.arr[i].sensor_id<id && i<root->u.data.dataCount)
		{
			i++;
		}
		if(root->u.data.arr[i].sensor_id==id)
		{
			root->u.data.arr[i]=sensor_data;
		}
		else
		{
			if(root->u.data.dataCount<ORDER_LEAF)
			{
				insertInRepoDataNode(sensor_data,root);
				return 0;
			}
			else
			{
				splitLeafRepoNode(sensor_data,root,right_subtree,median);
				return 1;
			}
		}
	}
	else if(root->flag=='k')
	{
		if(root->flag=='k')
		{
			if(id<root->u.key.sensor_id[1])
			{
				pos=0;
			}
			else
			{
				for(pos=root->u.key.count;id<root->u.key.sensor_id[pos];pos=pos-1);
			}
		}
		if(PushDownRepoNode(id,root->u.key.ptr[pos],median,right_subtree,sensor_data))
		{
		    id=*median;
			if(root->u.key.count<MAX)
			{
				insertInRepoKey(id,root,*right_subtree,pos);
				return 0;
			}
			else
			{
				splitKeyRepoNode(id,*right_subtree,root,pos,median,right_subtree);
				return 1;
			}
		}
		return 0;
	}
}

Node* insert(Node *root, S_data sensor_data, int id)
{
	int median_id;
	Node* right_subtree;
	Node* newroot;
	if(root==NULL)
	{
		Node *nptr;
		nptr=(Node *)malloc(sizeof(Node));
		nptr->flag='d';
		nptr->u.data.arr[0]=sensor_data;
		nptr->u.data.dataCount=1;
		nptr->u.data.next=NULL;
		nptr->u.data.prev=NULL;
		root=nptr;
		NumRecords++;
	}
	else if(PushDown(id,root,&median_id,&right_subtree,sensor_data))
	{
		newroot=(Node *)malloc(sizeof(Node));
		newroot->flag='k';
		newroot->u.key.count=1;
		newroot->u.key.sensor_id[1]=median_id;
		newroot->u.key.ptr[0]=root;
		newroot->u.key.ptr[1]=right_subtree;
		return newroot;
	}
	return root;
}

RepoNode* insertRepoNode(RepoNode *root, R_data sensor_data, int id)
{
	int median_id;
	RepoNode* right_subtree;
	RepoNode* newroot;
	if(root==NULL)
	{
		RepoNode *nptr;
		nptr=(RepoNode *)malloc(sizeof(RepoNode));
		nptr->flag='d';
		nptr->u.data.arr[0]=sensor_data;
		nptr->u.data.dataCount=1;
		nptr->u.data.next=NULL;
		nptr->u.data.prev=NULL;
		root=nptr;
		NumRecords++;
	}
	else if(PushDownRepoNode(id,root,&median_id,&right_subtree,sensor_data))
	{
		newroot=(RepoNode *)malloc(sizeof(RepoNode));
		newroot->flag='k';
		newroot->u.key.count=1;
		newroot->u.key.sensor_id[1]=median_id;
		newroot->u.key.ptr[0]=root;
		newroot->u.key.ptr[1]=right_subtree;
		return newroot;
	}
	return root;
}

void create_sensor_list(Node** head) // 1
{
	printf("Creating Sensor List\n");
    int n;
    printf("Enter the number of Nodes\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Storing the data for sensor %d\n",i+1);
		S_data data;
        printf("Enter the ID\n");
        scanf("%d",&data.sensor_id);
        printf("Enter the sensor type\n");
        scanf("\n%c",&data.sensor_type);
        printf("Enter the sesnor's station\n");
        scanf("\n%c",&data.sensor_station);
        printf("Enter the time interval of recordings\n");
        scanf("%f",&data.interval);
        if(i==0)
        {
            data.distance_btn_stations = 0;
        }
        else 
        {
            printf("Enter the distance between this station and the previous one\n");
            scanf("%f",&data.distance_btn_stations);
        }
        *head = insert(*head, data, data.sensor_id);
    }
}

void central_repository(Node* head_nodes, RepoNode **head_repo) // 1
{
	printf("Creating central repository\n");
    Node *iptr = head_nodes;
    while(iptr!=NULL)
	{
		for(i=0;i<iptr->u.data.dataCount;i++)
		{
			R_data rdata;
			printf("INCLUDING sensor with ID = %d to the repository\n",iptr->u.data.arr[i].sensor_id);
			printf("Enter date in dd-mm-yyyy format\n");
			scanf("\n%d-",&rdata.dt.dd);
			scanf("%d-",&rdata.dt.mm);
			scanf("%d",&rdata.dt.yyyy);
			printf("Enter data recorded\n");
			scanf("%f",&rdata.data);
			rdata.sensor_id = iptr->u.data.arr[i].sensor_id;
			rdata.time = iptr->u.data.arr[i].interval;
			*head_repo = insertRepoNode(*head_repo, rdata, rdata.sensor_id);
		}
		iptr=iptr->u.data.next; 
	}
}
 // ----------------------------------    question 2 below   ----------------------- 
void Install_new_sensor(Node* root)
{
	printf("Installing a new sensor \n\n");
	printf("Enter the location\n");
	char location, type;
	scanf("\n%c",&location);
	printf("Enter the type\n");
	scanf("\n%c",&type);
	Node* iptr;
	iptr=root;
	int flag = 0;
	while(iptr!=NULL)
	{
		for(i=0;i<iptr->u.data.dataCount;i++)
		{
			if(iptr->u.data.arr[i].sensor_station == location && iptr->u.data.arr[i].sensor_type == type)
			flag = 1;
		}
		iptr=iptr->u.data.next;
	}
	if(flag)
	{
		printf("Specified type is already present at location\n");
	}
	else
	{
		printf("Storing the data for sensor\n");
		S_data data;
        printf("Enter the ID\n");
        scanf("%d",&data.sensor_id);
		data.sensor_station = location;
		data.sensor_type = type;
		printf("Enter the time interval of recordings\n");
        scanf("%f",&data.interval);
		printf("Enter the distance between this station and the previous one\n");
        scanf("%f",&data.distance_btn_stations);
		root = insert(root, data, data.sensor_id);
	}
}


// ---------------------------------------   question 3 below --------------------------------------

void MoveLeftKey(RepoNode *root,int pos)
{
	int c;
	RepoNode *t;
	t=root->u.key.ptr[pos-1];
	t->u.key.count++;
	t->u.key.sensor_id[t->u.key.count]=root->u.key.sensor_id[pos];
	t->u.key.ptr[t->u.key.count]=(root->u.key.ptr[pos])->u.key.ptr[0];
	t=root->u.key.ptr[pos];
	root->u.key.sensor_id[pos]=t->u.key.sensor_id[1];
	t->u.key.ptr[0]=t->u.key.ptr[1];
	t->u.key.count--;
	for(c=1;c<=t->u.key.count;c++)
	{
		t->u.key.sensor_id[c]=t->u.key.sensor_id[c+1];
		t->u.key.ptr[c]=t->u.key.ptr[c+1];
	}
}


void MoveRightKey(RepoNode*root,int pos)
{
	int c;
	RepoNode*t;
	t=root->u.key.ptr[pos];
	for(c=t->u.key.count;c>0;c--)
	{
		t->u.key.sensor_id[c+1]=t->u.key.sensor_id[c];
		t->u.key.ptr[c+1]=t->u.key.ptr[c];
	}
	t->u.key.ptr[1]=t->u.key.ptr[0];
	t->u.key.count++;
	t->u.key.sensor_id[1]=root->u.key.sensor_id[pos];
	t=root->u.key.ptr[pos-1];
	root->u.key.sensor_id[pos]=t->u.key.sensor_id[t->u.key.count];
	(root->u.key.ptr[pos])->u.key.ptr[0]=t->u.key.ptr[t->u.key.count];
	t->u.key.count--;
}


void CombineKey(RepoNode*root,int pos)
{
	int c;
	RepoNode* right, * left;
	right=root->u.key.ptr[pos];
	left=root->u.key.ptr[pos-1];
	left->u.key.count++;
	
	left->u.key.sensor_id[left->u.key.count]=root->u.key.sensor_id[pos];
	left->u.key.ptr[left->u.key.count]=right->u.key.ptr[0];
	
	for(c=1;c<=right->u.key.count;c++)
	{
		left->u.key.count++;
		left->u.key.sensor_id[left->u.key.count]=right->u.key.sensor_id[c];
		left->u.key.ptr[left->u.key.count]=right->u.key.ptr[c];
	}
	
	for(c=pos;c<root->u.key.count;c++)
	{
		root->u.key.sensor_id[c]=root->u.key.sensor_id[c+1];
		root->u.key.ptr[c]=root->u.key.ptr[c+1];
	}
	
	root->u.key.count--;
	free(right);		
}



void MoveLeftLeaf(RepoNode*root,int pos)
{
	RepoNode*lhs;
	RepoNode*rhs;
	int c;
	lhs=root->u.key.ptr[pos-1];
	rhs=root->u.key.ptr[pos];
	lhs->u.data.arr[lhs->u.data.dataCount]=rhs->u.data.arr[0];
	lhs->u.data.dataCount++;
	root->u.key.sensor_id[pos]=rhs->u.data.arr[1].sensor_id;
	for(c=1;c<rhs->u.data.dataCount;c++)
	{
		rhs->u.data.arr[c-1]=rhs->u.data.arr[c];
		
	}
	rhs->u.data.dataCount--;
}

void MoveRightLeaf(RepoNode*root,int pos)
{
	RepoNode*lhs;
	RepoNode*rhs;
	int c;
	lhs=root->u.key.ptr[pos-1];
	rhs=root->u.key.ptr[pos];
	for(c=rhs->u.data.dataCount-1;c>=0;c--)
	{
		rhs->u.data.arr[c+1]=rhs->u.data.arr[c];
	}
	rhs->u.data.dataCount++;
	rhs->u.data.arr[0]=lhs->u.data.arr[lhs->u.data.dataCount-1];
	root->u.key.sensor_id[pos]=rhs->u.data.arr[lhs->u.data.dataCount-1].sensor_id;
	lhs->u.data.dataCount--;	
}

void CombineLeaf(RepoNode*root,int pos)
{

	RepoNode*lhs,*rhs;
	int c;
	lhs=root->u.key.ptr[pos-1];
	rhs=root->u.key.ptr[pos];
	int elems=lhs->u.data.dataCount;
	for(c=0;c<rhs->u.data.dataCount;c++)
	{
	
		lhs->u.data.arr[elems]=rhs->u.data.arr[c];
		elems++;
	}
	for(c=pos+1;c<=root->u.key.count;c++)
	{
		root->u.key.sensor_id[c-1]=root->u.key.sensor_id[c];
		root->u.key.ptr[c-1]=root->u.key.ptr[c];
	}
	lhs->u.data.next=rhs->u.data.next;
	if(rhs->u.data.next!=NULL)
	{
		(rhs->u.data.next)->u.data.prev=lhs;
	}
	lhs->u.data.dataCount=elems;
	root->u.key.count--;
	free(rhs);
	
}

void DeleteFromLeafDirect(int id,RepoNode *root)
{
	int pos,i=0;
	if(root->flag=='d')
	{
		while(root->u.data.arr[i].sensor_id<id)
		{
			i++;
		}
		if(root->u.data.arr[i].sensor_id>id)
		{
			printf("Id to be deleted was not found\n");
		}
		else if(root->u.data.arr[i].sensor_id==id)
		{
			i++;
			for(i;i<root->u.data.dataCount;i++)
			{
				root->u.data.arr[i-1]=root->u.data.arr[i];
			}
			root->u.data.dataCount--;
		}
	}
	NumRecords--;
}

int RestoreLeaf(int id,RepoNode *root,int pos)
{
	int k=0;
	int retval=0;
	if(pos==0)
	{
		if((root->u.key.ptr[1])->u.data.dataCount>MIN_DATA)
		{
			MoveLeftLeaf(root,1);
		}
		else
		{
			CombineLeaf(root,1);
			retval=1;
		}
	}
	else if(pos==root->u.key.count)
	{
		if((root->u.key.ptr[pos-1])->u.data.dataCount>MIN_DATA)
		{
			MoveRightLeaf(root,pos);
		}
		else
		{
			CombineLeaf(root,pos);
			retval=1;
		}
	}
	else if((root->u.key.ptr[pos-1])->u.data.dataCount>MIN_DATA)
	{
		MoveRightLeaf(root,pos);
	}
	else if((root->u.key.ptr[pos+1])->u.data.dataCount>MIN_DATA)
	{
		MoveLeftLeaf(root,pos+1);
	}
	else
	{
		CombineLeaf(root,pos);
		retval=1;
	}
	return retval;
	
}

int RestoreKey(int id,RepoNode *root,int pos)
{
	int k=0;
	int retval=0;
	if(pos==0)
	{
		if((root->u.key.ptr[1])->u.key.count>MIN)
		{
			MoveLeftKey(root,1);
		}
		else
		{
			CombineKey(root,1);
			retval=1;
		}
	}
	else if(pos==root->u.key.count)
	{
		if((root->u.key.ptr[pos-1])->u.key.count>MIN)
		{
			MoveRightKey(root,pos);
		}
		else
		{
			CombineKey(root,pos);
			retval=1;
		}
	}
	else if((root->u.key.ptr[pos-1])->u.key.count>MIN)
	{
		MoveRightKey(root,pos);
	}
	else if((root->u.key.ptr[pos+1])->u.key.count>MIN)
	{
		MoveLeftKey(root,pos+1);
	}
	else
	{
		CombineKey(root,pos);
		retval=1;
	}
	return retval;
}

int Delete_Node(int id,RepoNode *root)
{
	int pos,k,check_count;
	if((root->u.key.ptr[0])->flag=='d')
	{
		if(root->flag=='k')
		{
			if(id<root->u.key.sensor_id[1])
			{
				pos=0;
			}
			else
			{
				for(pos=root->u.key.count;id<root->u.key.sensor_id[pos];pos=pos-1);
			}
		}
		DeleteFromLeafDirect(id,root->u.key.ptr[pos]);
		check_count=(root->u.key.ptr[pos])->u.data.dataCount;
		if(check_count>=MIN_DATA)
		{
			return 0;
		}
		else
		{
			k=RestoreLeaf(id,root,pos);		//returns 1 if merge else 0
			return k;	
		}	
	}
	else
	{
		if(root->flag=='k')
		{
			if(id<root->u.key.sensor_id[1])
			{
				pos=0;
			}
			else
			{
				for(pos=root->u.key.count;id<root->u.key.sensor_id[pos];pos=pos-1);
			}
		}
		if(Delete_Node(id,root->u.key.ptr[pos]))
		{
			check_count=(root->u.key.ptr[pos])->u.key.count;
			if(check_count>=MIN)
			{
				return 0;
			}
			else
			{
				k=RestoreKey(id,root,pos);
				return k;
			}	
		}
	}
	return 0;
}

RepoNode* DeleteRepoNode(int id,RepoNode *root)
{
	RepoNode *oldroot;
	int k;
	if(root==NULL)
	{
		printf("Tree is empty\n");
	}
	else if(root->flag=='d')
	{
		DeleteFromLeafDirect(id,root);
	}
	else if (root->flag=='k')
	{
		Delete_Node(id,root);
		if(root->u.key.count==0)
		{
			oldroot=root;
			root=root->u.key.ptr[0];
			free(oldroot);
		}
	}
	return root;
}

void Remove_old_sensors(RepoNode *head) 
{
	printf("Removing old sensors \n\n");
    struct date curr_date;
    printf("Enter todays date in formate dd-mm-yyyy\n");
    scanf("\n%d-",&curr_date.dd);
    scanf("%d-",&curr_date.mm);
    scanf("%d",&curr_date.yyyy);

    RepoNode* nptr = head;
    while(nptr!=NULL)
	{
		for(i=0;i<nptr->u.data.dataCount;i++)
		{
			if(nptr->u.data.arr[i].dt.yyyy < curr_date.yyyy)
			{
				DeleteRepoNode(nptr->u.data.arr[i].sensor_id, head);
			}
			else if(nptr->u.data.arr[i].dt.yyyy == curr_date.yyyy && (curr_date.mm - nptr->u.data.arr[i].dt.mm)>2)
			{
				DeleteRepoNode(nptr->u.data.arr[i].sensor_id, head);
			}
			else if(nptr->u.data.arr[i].dt.yyyy == curr_date.yyyy && (curr_date.mm - nptr->u.data.arr[i].dt.mm) == 2 && (curr_date.dd > nptr->u.data.arr[i].dt.dd) )
			{
				DeleteRepoNode(nptr->u.data.arr[i].sensor_id, head);
			}
		}
		nptr=nptr->u.data.next;
    }
}

// --------------------------      question 4     ------------------------------------------ 

void Retrieve_info_all_stations(Node* lptr, RepoNode* head) // 4 
{
    char ch; Node* nptr = NULL; 
    RepoNode* dataptr = NULL;                                                        //menu driven 
	printf("\n Retrieving info all statons\n");
	printf("a) Depending on the sensor type \n");
	printf("b) Depending on specified date for specified type \n");
	printf("c) Depending on the time interval \n");
	printf("Kindly enter your option : a, b or c \n");
	scanf("\n%c",&ch);
	switch(ch)
    {
        case 'a':
			{
                nptr = lptr;
                dataptr = head;
				char type;
				printf("Enter sensor type : \n");
				scanf("\n%c",&type);
                while(nptr!=NULL)
				{
					for(i=0;i<nptr->u.data.dataCount;i++)
					{
						if(nptr->u.data.arr[i].sensor_type == type)
						{
							printf("Data recorded : %f by sensor ID : %d at Date : %d-%d-%d \n",dataptr->u.data.arr[i].data, nptr->u.data.arr[i].sensor_id, dataptr->u.data.arr[i].dt.dd, dataptr->u.data.arr[i].dt.mm, dataptr->u.data.arr[i].dt.yyyy);
						}
					}
                    nptr = nptr->u.data.next;
                    dataptr = dataptr->u.data.next;
                }
            }
            break;
        case 'b':
            {
                nptr = lptr;
                dataptr = head;
                char type;
				int i,dd1,mm1,yyyy1;
				printf("Enter specific sensor type : \n");
				scanf("\n%c",&type);
				printf("Enter the date as dd-mm-yyyy\n ");
				scanf("\n%d-",&dd1);
    			scanf("%d-",&mm1);
    			scanf("%d",&yyyy1);
				while(nptr!=NULL)
				{
					for(i=0;i<nptr->u.data.dataCount;i++)
					{
						if(nptr->u.data.arr[i].sensor_type == type && dataptr->u.data.arr[i].dt.dd == dd1 && dataptr->u.data.arr[i].dt.mm == mm1 && dataptr->u.data.arr[i].dt.yyyy == yyyy1)
						{
							printf("Data recorded : %f by sensor ID : %d \n",dataptr->u.data.arr[i].data, nptr->u.data.arr[i].sensor_id);
						}
					}
                    nptr = nptr->u.data.next;
                    dataptr = dataptr->u.data.next;
                }
            }
            break;
        case 'c':
            {
                nptr = lptr;
                dataptr = head;
                char type;
				float timeInt;
				int dd1,dd2,mm1,mm2,yyyy1,yyyy2;
				printf("Enter specific sensor type : ");
				scanf("\n%c",&type);
				printf("Enter specific time interval of sensor ");
				scanf("\n%f",&timeInt);
				char ch2;
				printf("Choose an option  \n");
				printf("a) Data of a specific date\n");
				printf("b) Data of a range of dates\n");
				scanf("\n%c",&ch2);

                switch(ch2)
				{
					case 'a':
						{
                            nptr = lptr;
                            dataptr = head;
							printf("Enter the date as dd-mm-yyyy\n ");
							scanf("\n%d-",&dd1);
    						scanf("%d-",&mm1);
    						scanf("%d",&yyyy1);
							while(nptr!=NULL)
							{
								for(i=0;i<nptr->u.data.dataCount;i++)
								{
									if(nptr->u.data.arr[i].sensor_type == type && nptr->u.data.arr[i].interval == timeInt && dataptr->u.data.arr[i].dt.dd == dd1 && dataptr->u.data.arr[i].dt.mm == mm1 && dataptr->u.data.arr[i].dt.yyyy == yyyy1)
									{
										printf("Data recorded : %f by sensor ID : %d \n",dataptr->u.data.arr[i].data, nptr->u.data.arr[i].sensor_id);
									}
								}
								nptr = nptr->u.data.next;
								dataptr = dataptr->u.data.next;
							}
                        }
                        break;
                    case 'b':
                        {
                            nptr = lptr;
                            dataptr = head;
                            printf("Enter the start date of range as dd-mm-yyyy\n ");
							scanf("\n%d-",&dd1);
    						scanf("%d-",&mm1);
    						scanf("%d",&yyyy1);
                            struct date d1 = {dd1,mm1,yyyy1};
    						
    						printf("Enter the end date of range as dd-mm-yyyy\n ");
							scanf("\n%d-",&dd2);
    						scanf("%d-",&mm2);
    						scanf("%d",&yyyy2);
                            struct date d2 = {dd2,mm2,yyyy2};
                            while(nptr!=NULL)
							{
								for(i=0;i<nptr->u.data.dataCount;i++)
								{
									if(smaller(d1, dataptr->u.data.arr[i].dt) && smaller(dataptr->u.data.arr[i].dt, d2)) 
										printf("Data : %f of sensor ID : %d \n ",dataptr->u.data.arr[i].data,nptr->u.data.arr[i].sensor_id);  
								}                 
                                nptr=nptr->u.data.next;
                                dataptr=dataptr->u.data.next;
							}     
                        }
                        break;
                    default :
						{
							printf("Invalid Input, choose a or b\n");
						}	
						break;		
                }
            }
            break;
        default:
			{
				printf("Invalid Input, choose a,b or c\n");
			}
			break;	
    }
}

void Retrieve_info_one_station(Node* lptr, RepoNode* head, char station) // 4
{
    char ch; Node* nptr = NULL; 
    RepoNode* dataptr = NULL;                                                        //menu driven 
	printf("\n Retrieving info for station : %c\n",station);
	printf("a) Depending on the sensor type \n");
	printf("b) Depending on specified date for specified type \n");
	printf("c) Depending on the time interval \n");
	printf("Kindly enter your option : a, b or c \n");
	scanf("\n%c",&ch);
	switch(ch)
    {
        case 'a':
			{
                nptr = lptr;
                dataptr = head;
				char type;
				printf("Enter sensor type : \n");
				scanf("\n%c",&type);
                while(nptr!=NULL)
				{
					for(i=0;i<nptr->u.data.dataCount;i++)
					{
						if(nptr->u.data.arr[i].sensor_type == type && nptr->u.data.arr[i].sensor_station == station)
						{
							printf("Data recorded : %f by sensor ID : %d at Date : %d-%d-%d \n",dataptr->u.data.arr[i].data, nptr->u.data.arr[i].sensor_id, dataptr->u.data.arr[i].dt.dd, dataptr->u.data.arr[i].dt.mm, dataptr->u.data.arr[i].dt.yyyy);
						}
					}
                    nptr = nptr->u.data.next;
                    dataptr = dataptr->u.data.next;
                }
            }
            break;
        case 'b':
            {
                nptr = lptr;
                dataptr = head;
                char type;
				int i,dd1,mm1,yyyy1;
				printf("Enter specific sensor type : \n");
				scanf("\n%c",&type);
				printf("Enter the date as dd-mm-yyyy\n ");
				scanf("\n%d-",&dd1);
    			scanf("%d-",&mm1);
    			scanf("%d",&yyyy1);
                while(nptr!=NULL)
				{
					for(i=0;i<nptr->u.data.dataCount;i++)
					{
						if(nptr->u.data.arr[i].sensor_type == type && nptr->u.data.arr[i].sensor_station == station && dataptr->u.data.arr[i].dt.dd == dd1 && dataptr->u.data.arr[i].dt.mm == mm1 && dataptr->u.data.arr[i].dt.yyyy == yyyy1)
						{
							printf("Data recorded : %f by sensor ID : %d \n",dataptr->u.data.arr[i].data, nptr->u.data.arr[i].sensor_id);
						}
					}
                    nptr = nptr->u.data.next;
                    dataptr = dataptr->u.data.next;
                }
            }
            break;
        case 'c':
            {
                nptr = lptr;
                dataptr = head;
                char type;
				float timeInt;
				int dd1,dd2,mm1,mm2,yyyy1,yyyy2;
				printf("Enter specific sensor type : ");
				scanf("\n%c",&type);
				printf("Enter specific time interval of sensor ");
				scanf("\n%f",&timeInt);
				char ch2;
				printf("Choose an option  \n");
				printf("a) Data of a specific date\n");
				printf("b) Data of a range of dates\n");
				scanf("\n%c",&ch2);

                switch(ch2)
				{
					case 'a':
						{
                            nptr = lptr;
                            dataptr = head;
							printf("Enter the date as dd-mm-yyyy\n ");
							scanf("\n%d-",&dd1);
    						scanf("%d-",&mm1);
    						scanf("%d",&yyyy1);

                            while(nptr!=NULL)
							{
								for(i=0;i<nptr->u.data.dataCount;i++)
								{
									if(nptr->u.data.arr[i].sensor_type == type && nptr->u.data.arr[i].sensor_station == station && nptr->u.data.arr[i].interval == timeInt && dataptr->u.data.arr[i].dt.dd == dd1 && dataptr->u.data.arr[i].dt.mm == mm1 && dataptr->u.data.arr[i].dt.yyyy == yyyy1)
									{
										printf("Data recorded : %f by sensor ID : %d \n",dataptr->u.data.arr[i].data, nptr->u.data.arr[i].sensor_id);
									}
								}
								nptr = nptr->u.data.next;
								dataptr = dataptr->u.data.next;
							}
                        }
                        break;
                    case 'b':
                        {
                            nptr = lptr;
                            dataptr = head;
                            printf("Enter the start date of range as dd-mm-yyyy\n ");
							scanf("\n%d-",&dd1);
    						scanf("%d-",&mm1);
    						scanf("%d",&yyyy1);
                            struct date d1 = {dd1,mm1,yyyy1};
    						
    						printf("Enter the end date of range as dd-mm-yyyy\n ");
							scanf("\n%d-",&dd2);
    						scanf("%d-",&mm2);
    						scanf("%d",&yyyy2);
                            struct date d2 = {dd2,mm2,yyyy2};
                            while(nptr!=NULL)
							{
								for(i=0;i<nptr->u.data.dataCount;i++)
								{
									if(smaller(d1, dataptr->u.data.arr[i].dt) && smaller(dataptr->u.data.arr[i].dt, d2) && nptr->u.data.arr[i].sensor_station == station ) 
										printf("Data : %f of sensor ID : %d \n ",dataptr->u.data.arr[i].data,nptr->u.data.arr[i].sensor_id);  
								}                 
                                nptr=nptr->u.data.next;
                                dataptr=dataptr->u.data.next;
							}
                        }
                        break;
                    default :
						{
							printf("Invalid Input, choose a or b\n");
						}	
						break;		
                }
            }
            break;
        default:
			{
				printf("Invalid Input, choose a,b or c\n");
			}
			break;	
    }
}

Node* searchNode(Node *root, unsigned long no)
{
	if(root->flag=='k')
	{
		int i=1;
		while(root->u.key.sensor_id[i]<=no && i<=root->u.key.count)
		{
			i++;
		}
		root=searchNode(root->u.key.ptr[i-1],no);

	}
	return root;
}

// ----------------------------     question 5   -------------------------------------------

void Sensors_in_Between(Node *root, unsigned int key1, unsigned int key2)
{
	printf("\nPrinting sensors in between range of keys : %d & %d\n",key1,key2);
	Node *node,*sptr;
	int found=0,i;
	
	if(root==NULL)
	{
		printf("Tree is empty\n");
	}
	else
	{
		node=searchNode(root,key1);
		sptr=node;
		printf("The details are: \n");
		while(sptr!=NULL && found==0)
		{
			for(i=0;i<sptr->u.data.dataCount && found==0;i++)
			{
				if(sptr->u.data.arr[i].sensor_id>=key1 && sptr->u.data.arr[i].sensor_id<=key2)
				{
					printf("\n-------- Dispalying details for sensor with id : %d -----------", sptr->u.data.arr[i].sensor_id);
					printf("Sensor ID ; %d \nSensor type: %c \nLocation : %c \nInterval : %f \nDistance from previous sensor : %f\n",sptr->u.data.arr[i].sensor_id, sptr->u.data.arr[i].sensor_type, sptr->u.data.arr[i].sensor_station, sptr->u.data.arr[i].interval, sptr->u.data.arr[i].distance_btn_stations);
				}
				if(sptr->u.data.arr[i].sensor_id>=key2)
				{
					found=1;
				}
	
			}
			sptr=sptr->u.data.next;
		}
		if(found==0)
		{
			printf("No sensors in the given range\n");
		}
	}
}

// ----------------------------          question 6         -----------------------------

struct data_val
{
	double data;
	struct data_val* down;
};

typedef struct entity_name                                       
{                                                               
    char entity_type[5];
    int standard_interval; // in hours 
    int duration;              // in mins 
    struct entity_name* next;
	struct entity_name* prev;
	struct data_val* ptr;
    float avg;
}Entity_data;

typedef struct AQI_node // stores aqi of different dates, so aqi struct uses entity structs to calculate aqi value
{
	int sensor_id;  
    float aqi; //will contain the max of avg of all entities
    struct date dt;
    char station;
    struct AQI_node* next;
}Entity_type;

typedef struct entity_node_tag
{
    union b_plus_tree_entity
    {
        struct key_nodes_entity
        {
            int sensor_id[MAX];
            struct entity_node_tag* ptr[MAX+1];
			int count;
        }key;
    	struct data_nodes_entity
        {
            Entity_type arr[ORDER_LEAF];
            struct entity_node_tag* next;
            struct entity_node_tag* prev;
            int dataCount;
        }data;
    }u;
    char flag;
}AQI;

void insertInDataEntityAQI(Entity_type sensor_data,AQI*root)
{
	int i=root->u.data.dataCount-1;
	if(root->flag=='d')
	{
		while(root->u.data.arr[i].sensor_id>=sensor_data.sensor_id && i>=0)
		{
			root->u.data.arr[i+1]=root->u.data.arr[i];
			i--;
		}
		root->u.data.arr[i+1]=sensor_data;
	}
	root->u.data.dataCount++;
	NumRecords++;
}

void insertInKeyAQI(int id,AQI*root,AQI*right_subtree,int pos)
{
	int i;
	for(i=root->u.key.count;i>pos;i--)
	{
		root->u.key.sensor_id[i+1]=root->u.key.sensor_id[i];
		root->u.key.ptr[i+1]=root->u.key.ptr[i];
	}
	root->u.key.sensor_id[pos+1]=id;
	root->u.key.ptr[pos+1]=right_subtree;
	root->u.key.count++;
}

void splitLeafEntityAQI(Entity_type sensor_data,AQI*root,AQI**right_subtree,int* id)
{
	Entity_type virtual_node[MAX+1];
	AQI*leaf_right;
	int i=0,j,k=0;
	while(sensor_data.sensor_id>root->u.data.arr[i].sensor_id && i<root->u.data.dataCount)
	{
	virtual_node[i]=root->u.data.arr[i];
	i++;
	}
	virtual_node[i]=sensor_data;
	while(i<=root->u.data.dataCount)
	{
	virtual_node[i+1]=root->u.data.arr[i];
	i++;
	}

	*id=virtual_node[i/2].sensor_id;
	root->u.data.dataCount=(int)ceil((double)root->u.data.dataCount/2);
	leaf_right=(AQI*)malloc(sizeof(AQI));
	leaf_right->flag='d';
	leaf_right->u.data.dataCount=i-root->u.data.dataCount;
	
	for(j=0;j<i/2;j++)
	{
		root->u.data.arr[j]=virtual_node[j];

	}
	for(j=i/2;j<i;j++)
	{
	leaf_right->u.data.arr[k]=virtual_node[j];
	k++;
	}
	if(root->u.data.next!=NULL)
	{
	(root->u.data.next)->u.data.prev=leaf_right;
	}

	leaf_right->u.data.next=root->u.data.next;
	root->u.data.next=leaf_right;
	leaf_right->u.data.prev=root;
	*right_subtree=leaf_right;
	NumRecords++;
}

void splitKeyEntityAQI(int median_entry,AQI*right_of_median,AQI*root,int pos, int *newmedian,AQI**newright)
{
	int i;
	int median;
											//to find the correct position of the median
	if(pos<=MIN)
	{
		median=MIN;
	}
	else
	{
		median=MIN+1;
	}
	*newright=(AQI*)malloc(sizeof(AQI));
	      								
	for(i=median+1;i<=MAX;i++)
	{
		(*newright)->u.key.sensor_id[i-median]=root->u.key.sensor_id[i];
		(*newright)->u.key.ptr[i-median]=root->u.key.ptr[i];
	}
	(*newright)->flag='k';
	(*newright)->u.key.count=MAX-median;
	root->u.key.count=median;
	if(pos<=MIN)
	{
		insertInKeyAQI(median_entry,root,right_of_median,pos);
	}
	else
	{
		insertInKeyAQI(median_entry,*newright,right_of_median,pos-median);
	}
	*newmedian=root->u.key.sensor_id[root->u.key.count];
	(*newright)->u.key.ptr[0]=root->u.key.ptr[root->u.key.count];
	root->u.key.count--;

}


int PushDownAQI(int id, AQI*root, int *median, AQI**right_subtree,Entity_type sensor_data)
{
	int pos,i=0;
	int found=0;
	if(root->flag=='d')
	{
		while(root->u.data.arr[i].sensor_id<id && i<root->u.data.dataCount)
		{
			i++;
		}
		if(root->u.data.arr[i].sensor_id==id)
		{
			root->u.data.arr[i]=sensor_data;
		}
		else
		{
			if(root->u.data.dataCount<ORDER_LEAF)
			{
				insertInDataEntityAQI(sensor_data,root);
				return 0;
			}
			else
			{
				splitLeafEntityAQI(sensor_data,root,right_subtree,median);
				return 1;
			}
		}
	}
	else if(root->flag=='k')
	{
		if(root->flag=='k')
		{
			if(id<root->u.key.sensor_id[1])
			{
				pos=0;
			}
			else
			{
				for(pos=root->u.key.count;id<root->u.key.sensor_id[pos];pos=pos-1);
			}
		}
		if(PushDownAQI(id,root->u.key.ptr[pos],median,right_subtree,sensor_data))
		{
		    id=*median;
			if(root->u.key.count<MAX)
			{
				insertInKeyAQI(id,root,*right_subtree,pos);
				return 0;
			}
			else
			{
				splitKeyEntityAQI(id,*right_subtree,root,pos,median,right_subtree);
				return 1;
			}
		}
		return 0;
	}
}

AQI* insert_AQI(AQI*root, Entity_type sensor_data, int id)
{
	int median_id;
	AQI* right_subtree;
	AQI* newroot;
	if(root==NULL)
	{
		AQI*nptr;
		nptr=(AQI*)malloc(sizeof(AQI));
		nptr->flag='d';
		nptr->u.data.arr[0]=sensor_data;
		nptr->u.data.dataCount=1;
		nptr->u.data.next=NULL;
		nptr->u.data.prev=NULL;
		root=nptr;
		NumRecords++;
	}
	else if(PushDownAQI(id,root,&median_id,&right_subtree,sensor_data))
	{
		newroot=(AQI*)malloc(sizeof(AQI));
		newroot->flag='k';
		newroot->u.key.count=1;
		newroot->u.key.sensor_id[1]=median_id;
		newroot->u.key.ptr[0]=root;
		newroot->u.key.ptr[1]=right_subtree;
		return newroot;
	}
	return root;
}

struct data_val* Insert_Entity_data(struct data_val **lpptr, float data) 
{ 
   
    struct data_val* new_node = (struct data_val*) malloc(sizeof(struct data_val)); 
    struct data_val *nptr = *lpptr;  
    new_node->data = data;
    new_node->down = NULL;   
    if (*lpptr == NULL) 
    { 
       *lpptr = new_node; 
    } 
    else
    {       
        while (nptr->down != NULL) 
            nptr = nptr->down; 
    
        nptr->down = new_node; 
    }
    return *lpptr;
}

AQI* create_aqi_structure(AQI* lptr)
{
	printf("\nCreating AQI structure\n");
	int flag;
	while(flag != -1)
    {
		int n;
		printf("Enter the number of entities\n");
		scanf("%d",&n);
		Entity_data read[n];
		for(i=0;i<n;i++)
		{
			
			printf("Enter entity name \n");
			scanf("\n%s",read[i].entity_type);
			printf("Enter standard interval in hours \n");
			scanf("%d",&read[i].standard_interval);
			printf("Enter the interval duration in mins\n");
			scanf("%d",&read[i].duration);
			int std_intl = read[i].standard_interval;
			std_intl = std_intl*60;    // converting to mins
			float sum=0; int count=0;
			while(std_intl > 0)        // take readings of entity till standard interval
			{
				float data;
				printf("Enter data \n");
				scanf("%f",&data);
				std_intl = std_intl - read[i].duration;
				read[i].ptr = Insert_Entity_data(&read[i].ptr, data);
				sum += data;         // sum of all data calculated over time 
				count++;             // no of times data reccorded 
			}
			read[i].avg = (float)sum/count; 
		}

		Entity_type arr;
		printf("Calcuating AQI for the date : \n");
		printf("Enter the date in dd-mm-yyyy\n");
		scanf("\n%d-",&arr.dt.dd);
		scanf("%d-",&arr.dt.mm);
		scanf("%d",&arr.dt.yyyy);
		printf("Enter sensor station\n");
		scanf("\n%c",&arr.station);
		printf("Enter the sensor ID\n");
		scanf("%d",&arr.sensor_id);
		double aqi = read[0].avg;
		for(i=0;i<n;i++)        // finding max of averages
		{
			if(read[i].avg > aqi)
			{
				aqi = read[i].avg;
			}
		}
		arr.aqi = aqi;
		lptr = insert_AQI(lptr, arr, arr.sensor_id);
		printf("Enter -1 to stop filling aqi data other number to continue \n");
		scanf("%d",&flag);
	}
    return lptr;
}

void max_aqi_month(AQI* lptr)  // 6 a
{
    AQI* nptr = lptr;
    float max = 0;
    int max_month = 0;
    while(nptr!=NULL)
	{
		for(i=0;i<nptr->u.data.dataCount;i++)
		{
			if(nptr->u.data.arr[i].aqi > max)
			{
				max = nptr->u.data.arr[i].aqi;
				max_month = nptr->u.data.arr[i].dt.mm;
			}
		}
        nptr = nptr->u.data.next;
    }
    printf("The month of max aqi %d", max_month);
}

void print_dates(AQI* lptr, int start,int end,int flag) // used for both 6b 
{
	AQI* nptr = lptr;
	while(nptr != NULL)
		{
			for(i=0;i<nptr->u.data.dataCount;i++)
			{
				if(flag==0) // for hazardous there is no upper limit, so this flag
				{
					if(nptr->u.data.arr[i].aqi >=start && nptr->u.data.arr[i].aqi <=end)
					{
						printf("%02d-%02d-%04d\n",nptr->u.data.arr[i].dt.dd,nptr->u.data.arr[i].dt.mm,nptr->u.data.arr[i].dt.yyyy);
					}
				}
				else
				{
					if(nptr->u.data.arr[i].aqi>=start )
					{
						printf("%02d-%02d-%04d\n",nptr->u.data.arr[i].dt.dd,nptr->u.data.arr[i].dt.mm,nptr->u.data.arr[i].dt.yyyy);
					}	
				}
			}
            nptr = nptr->u.data.next;
		}
}

void date_when_hazardous(AQI* lptr)  // 6 b
{
	printf("The AQ was hazrdous(including all stations) on these days:\n ");
	print_dates(lptr,501,0,1);
}

main()
{
	Node* root = NULL;
	RepoNode* head = NULL;
    
	create_sensor_list(&root);
	central_repository(root, &head);

	Install_new_sensor(root);
	Remove_old_sensors(head);

	Retrieve_info_all_stations(root, head);
	printf("Enter location to retreive info from\n");
	char ch;
	scanf("\n%c",&ch);
	Retrieve_info_one_station(root, head, ch);

    printf("Enter two key value to print details of range in betwen them\n");
    int k1,k2;
    scanf("%d %d",&k1,&k2);
	Sensors_in_Between(root, k1, k2);

	AQI* lptr;
	lptr = create_aqi_structure(lptr);

	max_aqi_month(lptr) ;; 
	date_when_hazardous(lptr);
}


