// BT19CSE022
// Divy Chheda

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct date
{
	int dd;
	int mm;
	int yyyy;
};

int smaller(struct date a, struct date b)  // compares two dates  
{                                           // used in retreive info between date range
int flag = 0;
  if (a.yyyy < b.yyyy) 
    flag = 1; 
  else if (a.yyyy == b.yyyy && a.mm < b.mm) 
    flag = 1; 
  else if (a.yyyy == b.yyyy && a.mm == b.mm && a.dd < b.dd) 
    flag = 1; 
  return flag;
}

typedef struct sensor_node
{
    int sensor_id;
    char sensor_type;
    char sensor_station;
    float interval;
    float distance_btn_stations;
    struct sensor_node* next;
}SNode;

typedef struct sensor_repo
{
    int sensor_id;
    struct date dt;
    float time;
    float data;
    struct sensor_repo* next;
}RepoNode;

SNode* Insert_SNode_At_End(SNode**lpptr, int id, char type, char station, float interval, float distance) 
{ 
   
    SNode* new_node = (SNode*) malloc(sizeof(SNode)); 
    SNode *nptr = *lpptr;  
    new_node->sensor_id  = id;
    new_node->sensor_type = type;
    new_node->sensor_station = station;
    new_node->interval = interval;
    new_node->distance_btn_stations = distance;
    new_node->next = NULL;   
    if (*lpptr == NULL) 
    { 
       *lpptr = new_node; 
    } 
    else
    {       
        while (nptr->next != NULL) 
            nptr = nptr->next; 
    
        nptr->next = new_node; 
    }
    return *lpptr;
} 

RepoNode* Insert_RepoNode_At_End(RepoNode **lpptr, int id, float interval, float data, int dd, int mm, int yyyy) 
{ 
   
    RepoNode* new_node = (RepoNode*) malloc(sizeof(RepoNode)); 
    RepoNode *nptr = *lpptr;  
    new_node->sensor_id  = id;
    new_node->time = interval;
    new_node->data = data;
    new_node->dt.dd = dd;
    new_node->dt.mm = mm;
    new_node->dt.yyyy = yyyy;
    new_node->next = NULL;   
    if (*lpptr == NULL) 
    { 
       *lpptr = new_node; 
    } 
    else
    {       
        while (nptr->next != NULL) 
            nptr = nptr->next; 
    
        nptr->next = new_node; 
    }
    return *lpptr;
} 

void create_sensor_list(SNode** head) // 1
{
    int n;
    printf("Enter the number of SNodes\n");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("Storing the data for sensor %d\n",i+1);
        int id; 
        char type, station;
        float intl, dist;
        printf("Enter the ID\n");
        scanf("%d",&id);
        printf("Enter the sensor type\n");
        scanf("\n%c",&type);
        printf("Enter the sesnor's station\n");
        scanf("\n%c",&station);
        printf("Enter the time interval of recordings\n");
        scanf("%f",&intl);
        if(i==0)
        {
            dist = 0;
        }
        else 
        {
            printf("Enter the distance between this station and the previous one\n");
            scanf("%f",&dist);
        }
        *head = Insert_SNode_At_End(head,id,type,station,intl,dist);
    }
}

void central_repository(SNode* head_snodes, RepoNode **head_repo) // 1
{
    SNode *nptr = head_snodes;
    while(nptr != NULL)
    {
        int dd,mm,yyyy;
        float data;
        printf("iNCLUDING sensor with ID = %d to the repository\n",nptr->sensor_id);
        printf("Enter date in dd-mm-yyyy format\n");
        scanf("\n%d-",&dd);
        scanf("%d-",&mm);
        scanf("%d",&yyyy);
        printf("Enter data recorded\n");
        scanf("%f",&data);
        *head_repo = Insert_RepoNode_At_End(head_repo, nptr->sensor_id, nptr->interval, data, dd, mm, yyyy);
        nptr=nptr->next;
    }
}

void Insert_After_SNode(SNode* nptr, int id, char type, char station, float interval, float distance)
{
    if(nptr == NULL)
    {
        printf("Error\n");
    }
    else
    {
        SNode* new_node = (SNode*)malloc(sizeof(SNode));
        new_node->sensor_id  = id;
        new_node->sensor_type = type;
        new_node->sensor_station = station;
        new_node->interval = interval;
        new_node->distance_btn_stations = distance;
        new_node->next = nptr->next;
        nptr->next = new_node;
    }
}

void Insert_new_Sensor(SNode* lptr) // 2
{
    SNode* nptr = lptr;
    if(lptr == NULL)
    {
        return;
    }
    while(nptr->next != NULL)
    {
        char type;
        printf("Enter the sensor type\n");
        scanf("\n%c",&type);
        if(nptr->next->distance_btn_stations > 10)
        {
            printf("Inserting Sensor between id = %d and id = %d\n",nptr->sensor_id,nptr->next->sensor_id);
            int id; 
            char station;
            float intl, dist;
            printf("Enter the ID\n");
            scanf("%d",&id);

            printf("Enter the sesnor's station\n");
            scanf("\n%c",&station);
            printf("Enter the time interval of recordings\n");
            scanf("%f",&intl);
            printf("Enter the distance between this station and the previous one\n");
            scanf("%f",&dist);
            Insert_After_SNode(nptr, id, type, station, intl, dist);
            nptr->next->distance_btn_stations -= dist;     // the new sensor added in between so the distance that was > 10 will no be reduced somewhat
        }
        else if( nptr->sensor_type != type && nptr->next->sensor_type != type)
        {
            printf("Inserting Sensor between id = %d and id = %d\n",nptr->sensor_id,nptr->next->sensor_id);
            int id; 
            char station;
            float intl, dist;
            printf("Enter the ID\n");
            scanf("%d",&id);

            printf("Enter the sesnor's station\n");
            scanf("\n%c",&station);
            printf("Enter the time interval of recordings\n");
            scanf("%f",&intl);
            printf("Enter the distance between this station and the previous one\n");
            scanf("%f",&dist);
            Insert_After_SNode(nptr, id, type, station, intl, dist);
        }
        nptr = nptr->next;
    }
}

void Delete_Repo_Node(RepoNode** lpptr, RepoNode* p, RepoNode* q) // delete node q that is after p
{
    if(q==NULL)
        return;
    else if(p==NULL)
    {
        *lpptr = q->next;
        free(q);
    }
    else if(p->next != q)
        return;

    else
    {
        p->next = q->next;
        free(q);
    }
}

void Remove_old_sensors(RepoNode *head) // 3
{
    struct date curr_date;
    printf("Enter todays date in formate dd-mm-yyyy\n");
    scanf("\n%d-",&curr_date.dd);
    scanf("%d-",&curr_date.mm);
    scanf("%d",&curr_date.yyyy);

    RepoNode* nptr = head;
    while(nptr->next != NULL)
    {
        if(nptr->next->dt.yyyy < curr_date.yyyy)
        {
            Delete_Repo_Node(&head, nptr, nptr->next);
        }
        else if(nptr->next->dt.yyyy == curr_date.yyyy && (curr_date.mm - nptr->next->dt.mm)>2)
        {
            Delete_Repo_Node(&head, nptr, nptr->next);
        }
        else if(nptr->next->dt.yyyy == curr_date.yyyy && (curr_date.mm - nptr->next->dt.mm) == 2 && (curr_date.dd > nptr->next->dt.dd) )
        {
            Delete_Repo_Node(&head, nptr, nptr->next);
        }
        nptr=nptr->next;
    }
}

void Retrieve_info_all_stations(SNode* lptr, RepoNode* head) // 4 
{
    char ch; SNode* nptr = NULL; 
    RepoNode* dataptr = NULL;                                                        //menu driven 
	printf("\n Retrieving info\n");
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
                while(nptr != NULL)
                {
                    if(nptr->sensor_type == type)
                    {
                        printf("Data recorded : %f by sensor ID : %d at Date : %d-%d-%d \n",dataptr->data, nptr->sensor_id, dataptr->dt.dd, dataptr->dt.mm, dataptr->dt.yyyy);
                    }
                    nptr = nptr->next;
                    dataptr = dataptr->next;
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
                while(nptr != NULL)
                {
                    if(nptr->sensor_type == type && dataptr->dt.dd == dd1 && dataptr->dt.mm == mm1 && dataptr->dt.yyyy == yyyy1)
                    {
                        printf("Data recorded : %f by sensor ID : %d \n",dataptr->data, nptr->sensor_id);
                    }
                    nptr = nptr->next;
                    dataptr = dataptr->next;
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

                            while(nptr != NULL)
                            {
                                if(nptr->sensor_type == type && nptr->interval == timeInt && dataptr->dt.dd==dd1 && dataptr->dt.mm == mm1 && dataptr->dt.yyyy == yyyy1)
                                {
                                    printf("Data : %f of sensor ID : %d \n ",dataptr->data,nptr->sensor_id);
                                }
                                nptr=nptr->next;
                                dataptr=dataptr->next;
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
                            while(nptr != NULL)
                            {
                                if(smaller(d1, dataptr->dt) && smaller(dataptr->dt, d2)) 
                                    printf("Data : %f of sensor ID : %d \n ",dataptr->data,nptr->sensor_id);                   
                                nptr=nptr->next;
                                dataptr=dataptr->next;
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

void Retrieve_info_one_station(SNode* lptr, RepoNode* head, char station) // 4
{
    char ch; SNode* nptr = NULL; 
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
                while(nptr != NULL)
                {
                    if(nptr->sensor_type == type && nptr->sensor_station == station)
                    {
                        printf("Data recorded : %f by sensor ID : %d at Date : %d-%d-%d \n",dataptr->data, nptr->sensor_id, dataptr->dt.dd, dataptr->dt.mm, dataptr->dt.yyyy);
                    }
                    nptr = nptr->next;
                    dataptr = dataptr->next;
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
                while(nptr != NULL)
                {
                    if(nptr->sensor_type == type && nptr->sensor_station == station && dataptr->dt.dd == dd1 && dataptr->dt.mm == mm1 && dataptr->dt.yyyy == yyyy1)
                    {
                        printf("Data recorded : %f by sensor ID : %d \n",dataptr->data, nptr->sensor_id);
                    }
                    nptr = nptr->next;
                    dataptr = dataptr->next;
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

                            while(nptr != NULL)
                            {
                                if(nptr->sensor_type == type && nptr->sensor_station == station && nptr->interval == timeInt && dataptr->dt.dd==dd1 && dataptr->dt.mm == mm1 && dataptr->dt.yyyy == yyyy1)
                                {
                                    printf("Data : %f of sensor ID : %d \n ",dataptr->data,nptr->sensor_id);
                                }
                                nptr=nptr->next;
                                dataptr=dataptr->next;
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
                            while(nptr != NULL)
                            {
                                if(smaller(d1, dataptr->dt) && smaller(dataptr->dt, d2) && nptr->sensor_station == station) 
                                    printf("Data : %f of sensor ID : %d \n ",dataptr->data,nptr->sensor_id);                   
                                nptr=nptr->next;
                                dataptr=dataptr->next;
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

void find_communicating_neighbours(SNode *lptr) // 5 
{
    printf("Finding Neighbour groups\n");
    SNode* slow_ptr = lptr;
    SNode* fast_ptr = NULL;
    while(slow_ptr!=NULL)
    {
        printf("%d -> ",slow_ptr->sensor_id);
        fast_ptr = slow_ptr->next;
        int dist = 10;
        while(fast_ptr!=NULL && dist > 0)
        {
            if(fast_ptr->distance_btn_stations < dist)
            {
                printf("%d ->",fast_ptr->sensor_id);
                dist = dist - fast_ptr->distance_btn_stations;
            }
            fast_ptr=fast_ptr->next;
        }
        printf("\n");
        slow_ptr=slow_ptr->next; 
    }
}

// AQI struct 
typedef struct entity_node
{
    float data;                                                   //       PM2.5 -> PM10 -> etc 
    struct entity_node* down;                                     //         |        |
}Entity_data;                                                     //        data      data 
                                                                  //         |         | 
typedef struct entity_name                                        //        data      data ....... 
{                                                                 //    (calculated after each duration till standard time interval)
    char entity_type[5];
    int standard_interval; // in hours 
    int duration;              // in mins 
    Entity_data* down;
    struct entity_name* next;
    float avg;
}Entity_Type;

Entity_Type* Insert_Entity_types_to_Entity_list(Entity_Type **lpptr, char type[], int std_interval, int dur) 
{ 
   
    Entity_Type* new_node = (Entity_Type*) malloc(sizeof(Entity_Type)); 
    Entity_Type *nptr = *lpptr;  
    strcpy(new_node->entity_type,type);
    new_node->standard_interval=std_interval;
    new_node->duration=dur;
    new_node->next = NULL;   
    if (*lpptr == NULL) 
    { 
       *lpptr = new_node; 
    } 
    else
    {       
        while (nptr->next != NULL) 
            nptr = nptr->next; 
    
        nptr->next = new_node; 
    }
    return *lpptr;
} 

Entity_data* Insert_Entity_data(Entity_data **lpptr, float data) 
{ 
   
    Entity_data* new_node = (Entity_data*) malloc(sizeof(Entity_data)); 
    Entity_data *nptr = *lpptr;  
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

Entity_Type* create_aqi_structure(Entity_Type* lptr)
{
    int n;
    printf("Enter the number of entities\n");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        char type[5]; int std_intl, dur;
        printf("Enter entity name \n");
        scanf("\n%s",type);
        printf("Enter standard interval in hours \n");
        scanf("%d",&std_intl);
        printf("Enter the interval duration in mins\n");
        scanf("%d",&dur);
        lptr = Insert_Entity_types_to_Entity_list(&lptr,type,std_intl,dur);
    }

    Entity_Type* nptr  = lptr;
    while(nptr != NULL)
    {
        printf("Fill in data for Entitiy type : %s", nptr->entity_type);
        int std_intl = nptr->standard_interval;
        std_intl = std_intl*60;    // converting to mins
        float sum=0; int count=0;
        while(std_intl > 0)        // take readings of entity till standard interval
        {
            float data;
            printf("Enter data \n");
            scanf("%f",&data);
            std_intl = std_intl - nptr->duration;
            nptr->down = Insert_Entity_data(&nptr->down, data);
            sum += data;         // sum of all data calculated over time 
            count++;             // no of times data reccorded 
        }
        nptr->avg = (float)sum/count;     // average for each entitity
        nptr = nptr->next;
    }
    return lptr;
}

typedef struct AQI_node // stores aqi of different dates, so aqi struct uses entity structs to calculate aqi value
{
    float aqi; //will contain the max of avg of all entities
    struct date dt;
    char station;
    struct AQI_node* next;
}AQI;

AQI* Insert_AQI(AQI **lpptr, float aqi, char station, int dd, int mm, int yyyy) 
{ 
   
    AQI* new_node = (AQI*) malloc(sizeof(AQI)); 
    AQI *nptr = *lpptr;  
    new_node->aqi = aqi;
    new_node->dt.dd = dd;
    new_node->dt.mm =mm;
    new_node->dt.yyyy=yyyy;
    new_node->station = station;
    new_node->next = NULL;
    if (*lpptr == NULL) 
    { 
       *lpptr = new_node; 
    } 
    else
    {       
        while (nptr->next != NULL) 
            nptr = nptr->next; 
    
        nptr->next= new_node; 
    }
    return *lpptr;
}

void calulate_aqi(AQI *lptr)      // this creates the aqi data structure with help of create_aqi_structure and calculates aqi
{
    int flag = 0;
    while(flag != -1)
    {
        int dd,mm,yyyy; float aqi; char station;
        printf("Calcuating AQI for the date : \n");
        printf("Enter the date in dd-mm-yyyy\n");
        scanf("\n%d-",&dd);
        scanf("%d-",&mm);
        scanf("%d",&yyyy);
        printf("Enter sensor station\n");
        scanf("\n%c",&station);
        Entity_Type* head = NULL;
        head = create_aqi_structure(head);
        Entity_Type *ptr = head;
        aqi = ptr->avg;
        while (ptr != NULL)          // finding max of averages
        {
            if(ptr->avg > aqi)
            {
                aqi = ptr->avg;
            }
            ptr = ptr->next;
        }
        lptr = Insert_AQI(&lptr,aqi,station,dd,mm,yyyy);
        printf("Enter -1 to stop filling data other number to continue \n");
        scanf("%d",&flag);
    }
}

void max_aqi_month(AQI* lptr)  // 6 a
{
    AQI* nptr = lptr;
    float max = 0;
    int max_month = 0;
    while(nptr != NULL)
    {
        if(nptr->aqi > max)
        {
            max = nptr->aqi;
            max_month = nptr->dt.mm;
        }
        nptr = nptr->next;
    }
    printf("The month of max aqi %d", max_month);
}


void print_dates(AQI* lptr, int start,int end,char loc,int flag) // used for both 6b and 6c 
{
    AQI* nptr = lptr;
	if(loc == '#') // to pint for all locations
	{
		while(nptr != NULL)
		{
			if(flag==0) // for hazardous there is no upper limit, so this flag
			{
				if(nptr->aqi >=start && nptr->aqi <=end)
				{
					printf("%02d-%02d-%04d\n",nptr->dt.dd,nptr->dt.mm,nptr->dt.yyyy);
				}
			}
			else
			{
				if(nptr->aqi>=start )
				{
					printf("%02d-%02d-%04d\n",nptr->dt.dd,nptr->dt.mm,nptr->dt.yyyy);
				}	
			}
            nptr = nptr->next;
		}
	}
	else
	{
		while(nptr != NULL)
		{
			if(flag==0)
			{
				if(nptr->aqi>=start && nptr->aqi<=end && nptr->station==loc)
				{
					printf("%02d-%02d-%04d\n",nptr->dt.dd,nptr->dt.mm,nptr->dt.yyyy);
				}
			}
			else
			{
				if(nptr->aqi>=start && nptr->station==loc)
				{
					printf("%02d-%02d-%04d\n",nptr->dt.dd,nptr->dt.mm,nptr->dt.yyyy);
				}
			}
            nptr = nptr->next;
		}
	}
}

void date_health_status(AQI *lptr) // 6 b
{
    char ch,loc;
	printf("1) 1-50    Good \n");
	printf("2) 51-100  Satisfactory");	
	printf("3) 101-200 Moderately polluted \n");	
	printf("4) 201-300 Poor 	\n");
	printf("5) 301-400 May cause respiratory illness \n");
	printf("6) 401-500 Severe 	\n");
	printf("7) 501 onward  Hazardous \n");
	printf("Choose an option of health status\n");
	scanf("\n%c",&ch);
	printf("Input the station location code \n");
	scanf("\n%c",&loc);
    switch(ch)
	{
		case 1:
			{
				printf("Dates when AQ was Good\n");
				print_dates(lptr,1,50,loc,0);
			}
			break;
		case 2:
			{
				printf("Dates when AQ was satisfactory\n");
				print_dates(lptr,51,100,loc,0);
			}
			break;
		case 3:
			{
				printf("Dates when AQ was Moderately polluted\n");
				print_dates(lptr,101,200,loc,0);
			}
			break;
		case 4:
			{
				printf("Dates when AQ was Poor \n");
				print_dates(lptr,201,300,loc,0);
			}
			break;
		case 5:
			{
				printf("Dates when AQ May cause respiratory illness \n");
				print_dates(lptr,301,400,loc,0);
			}
			break;
		case 6:
			{
				printf("Dates when AQ was Severe \n");
				print_dates(lptr,401,500,loc,0);
			}
			break;
		case 7:
			{
				printf("Dates when AQ was Hazardous \n");
				print_dates(lptr,501,0,loc,1);
			}
			break;
		
		default :
			printf("Input must be in 1-7 \n");
			break;
	}

}

void date_when_hazardous(AQI* lptr)  // 6 c
{
	char ch ='#';
	printf("The AQ was hazrdous(including all stations) on these days:\n ");
	print_dates(lptr,501,0,ch,1);
}

main()
{
    SNode* lptr = NULL;
    RepoNode* head = NULL;

    create_sensor_list(&lptr);
    
    central_repository(lptr, &head);

    Insert_new_Sensor(lptr);
    
    Remove_old_sensors(head);
    
    Retrieve_info_all_stations(lptr, head);
    
    char station;
    printf("Enter the station to retreive its info\n");
    scanf("\n%c",&station);
    Retrieve_info_one_station(lptr,head,station);
    
    find_communicating_neighbours(lptr);

    AQI* ptr = NULL;
    calulate_aqi(ptr);
    max_aqi_month(ptr);
    date_health_status(ptr);
    date_when_hazardous(ptr);
}
