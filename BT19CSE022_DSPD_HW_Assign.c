// BT19CSE022, Divy Chheda
#include<stdio.h>
#define SIZE 100

struct sensor_network
{
	int sensor_ID;
	char sensor_type; //assuming its a single char code 
	char sensor_location; // assuming its a single char code 
	float time;
	int numOfNearby;
	struct nearby_sensors
	{
		int sensor_ID;
		float dist;
		
	}sens[SIZE];
};

struct date
{
	int dd;
	int mm;
	int yyyy;
};

struct central_repo
{
	int sensor_ID;
	char sensor_type;
	struct date dt;
	float time;
	float data;
};

struct entity
{
	char name[10];
	float data;
	float time;
	float std_time_int;
	
};

struct AQI
{
	char sensor_location;
	struct date dt;
	float data;	
};

void create_data_structure(struct central_repo databank[],struct sensor_network sensors[], int n) // 1
{
	int i,j;
	// taking input into the data structure as a way of supplying the data
	
	for(i=0;i<n;i++) 
	{	printf("Updating the database\n"); 
		printf("Input sensor ID\n");
		scanf("%d",&sensors[i].sensor_ID);
		printf("Input sensor TYPE\n");
		scanf("\n%c",&sensors[i].sensor_type);
		printf("Input sensor location or station\n");
		scanf("\n%c",&sensors[i].sensor_location);
		printf("Input time interval \n");
		scanf("\n%f",&sensors[i].time);
		databank[i].sensor_type=sensors[i].sensor_type;
		databank[i].sensor_ID=sensors[i].sensor_ID;
		databank[i].time=sensors[i].time;
		printf("Enter date in dd-mm-yyyy format\n");
		scanf("\n%d-",&databank[i].dt.dd);
    	scanf("%d-",&databank[i].dt.mm);
    	scanf("%d",&databank[i].dt.yyyy);
    	
    	printf("Data recorded : ");
    	scanf("\n%f",&databank[i].data);
		
		printf("How many sensors are nearby ? \n");
		scanf("\n%d",&sensors[i].numOfNearby);
		
		for(j=0;j<sensors[i].numOfNearby;j++)
		{
			printf("Storing nearby sensor number: %d\n",j+1);
			printf("Input its sensor ID\n");
			scanf("%d",&sensors[i].sens[j].sensor_ID);
			printf("Input the distance\n");
			scanf("\n%f",&sensors[i].sens[j].dist);
		}		
	}	
}

void Retrieve_info(struct central_repo databank[],int n)   // 2 
{
	char ch;  //menu driven 
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
				char type;
				int i;
				printf("Enter sensor type : ");
				scanf("\n%c",&type);
				for(i=0;i<n;i++)
				{
					if(type == databank[i].sensor_type)
					{
						printf("Data : %f on date %d-%d-%d\n",databank[i].data,databank[i].dt.dd,databank[i].dt.mm,databank[i].dt.yyyy);
					}
				}
				
			}
			break;
		
		case 'b':
			{
				char type;
				int i,dd1,mm1,yyyy1;
				printf("Enter specific sensor type : ");
				scanf("\n%c",&type);
				printf("Enter the date as dd-mm-yyyy\n ");
				scanf("\n%d-",&dd1);
    			scanf("%d-",&mm1);
    			scanf("%d",&yyyy1);
				
				for(i=0;i<n;i++)
				{
					if(type == databank[i].sensor_type && databank[i].dt.dd==dd1 && databank[i].dt.mm==mm1 && databank[i].dt.yyyy==yyyy1)
					{
						printf("Data : %f \n",databank[i].data);
					}
				}
			}
			break;
			
		case 'c':
			{
				char type;
				int i;
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
							printf("Enter the date as dd-mm-yyyy\n ");
							scanf("\n%d-",&dd1);
    						scanf("%d-",&mm1);
    						scanf("%d",&yyyy1);
    						
    						for(i=0;i<n;i++)
							{
								if(type == databank[i].sensor_type && databank[i].time == timeInt && databank[i].dt.dd==dd1 && databank[i].dt.mm==mm1 && databank[i].dt.yyyy==yyyy1)
								{
									printf("Data : %f \n",databank[i].data);
								}
							}
						}
						break;
					case 'b' :
						{
							printf("Enter the start date of range as dd-mm-yyyy\n ");
							scanf("\n%d-",&dd1);
    						scanf("%d-",&mm1);
    						scanf("%d",&yyyy1);
    						
    						printf("Enter the end date of range as dd-mm-yyyy\n ");
							scanf("\n%d-",&dd2);
    						scanf("%d-",&mm2);
    						scanf("%d",&yyyy2);
    						int j;
    						for(i=0;i<n;i++)
							{
								if(type == databank[i].sensor_type && databank[i].time == timeInt && databank[i].dt.dd==dd1 && databank[i].dt.mm==mm1 && databank[i].dt.yyyy==yyyy1)
								{
									for(j=i; databank[j].dt.dd<=dd2 && databank[j].dt.mm<=mm2 && databank[j].dt.yyyy<=yyyy2; j++)
									{
										printf("Data : %f \n",databank[j].data);	
									}
								}
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

void find_communicating_neighbours(struct sensor_network sensors[],int n,int ID,int count,int sameid[])   // 3
{	int i,j;
	printf("Finding Neighbours\n");
	for(j=0;j<n;j++)
	{
	
		if(ID==sensors[j].sensor_ID && sameid[j] != 1 )
		{
			sameid[j]=1;
			if(count == 1)
				printf("%d",ID);
			for(i=j;i<sensors[j].numOfNearby;i++)
			{
				if(sensors[j].sens[i].dist<=1000.0)
				{
					printf("->%d",sensors[j].sens[i].sensor_ID);
					find_communicating_neighbours(sensors,n,sensors[j].sens[i].sensor_ID,count++,sameid);
					printf("\n\n");
				}
			
			}
		}
	
	}

}
float averaging_entities(float dur, float std_int) 
{
	int i, n = (int)std_int*60/dur;
	float data,sum=0.0;
	for(i=0;i<n;i++)
	{
	//	printf("data : \n");
	//	scanf("\n%f",&data);                  // assuming they receive data from sensor after every time period (ex. 5 mins) throughout the std time interval
		                                    
		sum+=data;
	}
	return (float)sum/n;
}

float calculate_aqi(struct entity enti[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("Entity : ");
		scanf("\n%s",enti[i].name);
		printf("Standard Time Interval in hours : ");
		scanf("\n%f",&enti[i].std_time_int);
		printf("time duration in mins : ");
		scanf("\n%f",&enti[i].time);
		enti[i].data=averaging_entities(enti[i].time,enti[i].std_time_int);	
	}
	//aqi is the max of all the data values
	float max = enti[0].data;
	for(i=0;i<n;i++)
	{
		if(enti[i].data > max)
		{
			max = enti[i].data;
		}
	}
	return max;
}

void create_dataStruct_aqi(struct AQI reads[],int n) // 4
{
	printf("Creating aqi structure \n");
	struct entity aqi_ent[SIZE];
	int numOfEnti,i;
	printf("Enter number of entities to be accounted for?\n");
	scanf("%d",&numOfEnti);
	for(i=0;i<n;i++)
	{	printf("Receiving readings : \n");
		printf("Enter its location : ");
		scanf("\n%f",&reads[i].sensor_location);
		printf("Enter date in dd-mm-yyyy format\n");
		scanf("\n%d-",&reads[i].dt.dd);
    	scanf("%d-",&reads[i].dt.mm);
    	scanf("%d",&reads[i].dt.yyyy);
    	
    	reads[i].data = calculate_aqi(aqi_ent,numOfEnti);
	}
}

void month_max_aqi(struct AQI reads[],int n) // 4 a
{	
	int ind =0,i;
	float max = reads[0].data;
	for(i=0;i<n;i++)
	{
		if(reads[i].data > max)
		{
			max = reads[i].data;
			ind = i;
		}
	}
	printf("The month for which maximum aqi is recorded is %d\n",reads[ind].dt.mm);
}

void print_dates(struct AQI reads[],int n, int start,int end,char loc,int flag)
{
	int i;
	if(loc == '#') // to pint for all locations
	{
		for(i=0;i<n;i++)
		{
			if(flag==0) // for hazardous there is no upper limit, so this flag
			{
				if(reads[i].data>=start && reads[i].data<=end)
				{
					printf("%02d-%02d-%04d\n",reads[i].dt.dd,reads[i].dt.mm,reads[i].dt.yyyy);
				}
			}
			else
			{
				if(reads[i].data>=start )
				{
					printf("%02d-%02d-%04d\n",reads[i].dt.dd,reads[i].dt.mm,reads[i].dt.yyyy);
				}	
			}
		}
	}
	else
	{
		for(i=0;i<n;i++)
		{
			if(flag==0)
			{
				if(reads[i].data>=start && reads[i].data<=end && reads[i].sensor_location==loc)
				{
					printf("%02d-%02d-%04d\n",reads[i].dt.dd,reads[i].dt.mm,reads[i].dt.yyyy);
				}
			}
			else
			{
				if(reads[i].data>=start && reads[i].sensor_location==loc)
				{
					printf("%02d-%02d-%04d\n",reads[i].dt.dd,reads[i].dt.mm,reads[i].dt.yyyy);
				}
			}
		}
	}
}

void date_status(struct AQI reads[],int n) // 4 b
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
				print_dates(reads,n,1,50,loc,0);
			}
			break;
		case 2:
			{
				printf("Dates when AQ was satisfactory\n");
				print_dates(reads,n,51,100,loc,0);
			}
			break;
		case 3:
			{
				printf("Dates when AQ was Moderately polluted\n");
				print_dates(reads,n,101,200,loc,0);
			}
			break;
		case 4:
			{
				printf("Dates when AQ was Poor \n");
				print_dates(reads,n,201,300,loc,0);
			}
			break;
		case 5:
			{
				printf("Dates when AQ May cause respiratory illness \n");
				print_dates(reads,n,301,400,loc,0);
			}
			break;
		case 6:
			{
				printf("Dates when AQ was Severe \n");
				print_dates(reads,n,401,500,loc,0);
			}
			break;
		case 7:
			{
				printf("Dates when AQ was Hazardous \n");
				print_dates(reads,n,501,0,loc,1);
			}
			break;
		
		default :
			printf("Input must be in 1-7 \n");
			break;
	}
}

void date_when_hazardous(struct AQI reads[],int n)  // 4 c
{
	char ch ='#';
	printf("The AQ was hazrdous(including all stations) on these days:\n ");
	print_dates(reads,n,501,0,ch,1);
}

main()
{   
	struct sensor_network s[SIZE];
	struct central_repo s1[SIZE];
    int n,i;
	printf("Enter number of sensors to be formulated?\n");
	scanf("%d",&n);
	create_data_structure(s1,s,n);
	Retrieve_info(s1,n);
	int id;
	printf("Enter the sensor ID\n");
	scanf("%d",&id);
	int sameid[SIZE];
	for(i=0;i<n;i++)
	{
		sameid[i]==0;
	}
	find_communicating_neighbours(s,n,id,1,sameid);
	int n1;
	struct AQI aqidb[SIZE];
	printf("Enter number of readings for AQI\n");
	scanf("\n%d",&n1);
	create_dataStruct_aqi(aqidb,n1);
	month_max_aqi(aqidb,n1);
	date_status(aqidb,n1);
	date_when_hazardous(aqidb,n1);
}
