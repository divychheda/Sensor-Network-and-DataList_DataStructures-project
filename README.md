# Sensor-Network-and-DataList_DataStructures-project

This was a project assigned to me at the end of each Data Structures course 


### Problem Statement

>It was similar everytime, with difference of the prefered data structure used for storage. 
>Used arrays for the first one, linked lists for the second and b+ trees for the last. 

```
A sensor network consists of spatially dispersed and dedicated sensors for monitoring and
recording physical conditions of environment like temperature, sound, humidity, wind, and so
on for multiple stations (you can consider different areas in city). The data from all sensors is
collected at central location. Each sensor records the corresponding data at continuous time
interval daily. Each sensor is represented by sensor ID (integer), sensor type, data it senses,
time interval during which it senses the conditions continuously.
Write function for the following assuming that sensor database is stored either in AVL tree
or B-tree or B+ tree data structure.
1. Write a function create_sensor_network(struct sensor_node* new_node) which
will formulate the above mentioned sensor network in software. Data fields for every
sensor node in the linked list should have following attributes -
a. sensor_ID(integer)
b. sensor_type (char)
c. sensor_location(charater)(or sensor station)
d. duration(time interval ex. 5 min- it means that a sensor senses the
temperature , humidity etc. after every 5 min.)

Central repository is the location where data from all sensors is collected and it should include following things-
a. sensor_ID
b. Date
c. Time
d. data(integer or float)

Write a function central_repository (struct record* new_record) which will create
a database of information collected from all sensors.

2. Implement a function Install_new_Sensor() to add sensor to the existing sensor
network at specified station.
Note: New sensor will be added only if the type of sensor to be added is not
present at specified station.

3. Idle sensors are those which are not sending any information to central repository for
more than 2months. Identify such idle sensors and remove them from database.
(remove means permanently delete them from database)

4. Retrieve_info() functions retrieves the data for sensors specified by following
conditions
A. Depending on sensor type (retrieves till date data)
B. Depending on specified date range (multiple dates) for specific sensor type

5. Write function sensors_in_between() to print information of all sensors located in
between any stations specified by sensor_ID range. (EX. if sensor ID range is 100-
200. Expected output is the information of all sensors with ID>=100 and ID<=200)

6. Adapt the existing data structure for sensor type which records multiple quantities.
Ex. Air quality index (AQI) sensor which records entities like PM10, PM 2.5,
nitrogen dioxide, sulphur dioxide, carbon monoxide, ground level ozone etc. and tries
to find out Air quality level and pollution level. AQI is measures based on the average
quantity of a particular entity measured over a standard time interval. Standard time
interval for measuring averages is different for different entities (24 hours for most of
the entities, 8 hrs. For PM 2.5). There should be provision for storing standard time
interval for each independent entity in existing data structure. Final AQI is the highest
of the AQI values calculated separately for each entity. AQI value for finding health
status is as follows

AQI Status
1-50 Good
51-100 Satisfactory
101-200 Moderately polluted
201-300 Poor
301-400 May cause respiratory illness
401-500 Severe
501 onwards Hazardous

a. Write a function to report or display the month during which maximum
AQI is reported for all years for all stations.
b. Write a function to display the dates on which hazardous health status is
recorded for all stations.
```
