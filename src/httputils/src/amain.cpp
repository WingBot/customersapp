#include <stdio.h> 
#include <ros/ros.h>
#include <string>
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h> 
using namespace std;
 
int main()
{
 ros::init(argc,argv,"json_ros");  
Json::Value root;
Json::Reader reader;
std::ifstream ifs("/home/zech/http_ws/src/httputils/example.json");//open file example.json
if(ifs==NULL)
{
 
}
if(!reader.parse(ifs, root)){
   // fail to parse
}
else{
   // success
   std::cout<<root["filename"].asString()<<endl;
   std::cout<<root["string"].asString()<<endl;
   std::cout<<root["filesize"].asInt()<<endl;
   std::cout<<root["inttype"].asInt()<<endl;
   std::cout<<root["floattype"].asFloat()<<endl;
   std::cout<<root["doubletype"].asDouble()<<endl;
   Json::Value array = root["arrayint"];
   for(int i = 0;i < array.size();i++)
   {
	   std::cout<<array[i].asInt()<<endl;
   }
   Json::Value array = root["arraycahr"];
   for(int i = 0;i < array.size();i++)
   {
	   std::cout<<array[i].asString()<<endl;
   }
   /*
   Json::Value obj1 = root["arrayobj1"];
   for(int i = 0;i < obj1.size();i++)
   {
	   std::cout<<obj1[i][].asString()<<endl;
   }
   */
    Json::Value obj2 = root["arrayobj2"];
   for(int i = 0;i < obj2.size();i++)
   {
	   std::cout<<obj2[i]["name"].asString()<<endl;
	   std::cout<<obj2[i]["age"].asInt()<<endl;
	   std::cout<<obj2[i]["weight"].asDouble()<<endl;
   }
}
}