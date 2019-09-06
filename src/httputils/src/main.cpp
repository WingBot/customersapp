#include <stdio.h> 
#include <ros/ros.h>
#include <curl/curl.h> 
#include <jsoncpp/json/json.h> 
#include <string>
#include <iostream>
#include <fstream>
#define PATH_FILE "/home/zech/http_ws/src/httputils/example.json"

static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

void ReadJsonMsg()
{   
    using namespace std;
    Json::Reader reader;
    Json::Value root;
    ifstream ifs;
    ifs.open(PATH_FILE, ios::binary);
    if(reader.parse(ifs,root))
    {
        string message = root["message"].asString();
        int success = root["success"].asInt();
        cout << "Whether success :" << success << endl <<endl;
        cout << "The output of return message is :" << message << "" << endl <<endl;
        cout << "Reading Complete!" << endl;
    }
    ifs.close();
}

int main(int argc, char *argv[])   
{  
    using namespace std;
    ros::init(argc,argv,"json_ros");  
    ros::NodeHandle n;
    ros::Rate loop_rate(500);
    
    //define the json value 
    Json::Value root;
    Json::Reader reader;
    ifstream ifs;
    ifs.open(PATH_FILE, ios::binary);
    if(ifs==NULL)
      {
          ROS_INFO("ifs==NULL");
      }
      if(!reader.parse(ifs, root)){
	// fail to parse
	ROS_INFO("fail to parse");
      }
      else{
   // success
	  std::cout<<"filename:   "<<root["filename"].asString()<<endl;
	  std::cout<<"string:     "<<root["string"].asString()<<endl;
	  std::cout<<"filesize:   "<<root["filesize"].asInt()<<endl;
	  std::cout<<"inttype:    "<<root["inttype"].asInt()<<endl;
	  std::cout<<"floattypeg: "<<root["floattype"].asFloat()<<endl;
	  std::cout<<"doubletype: "<<root["doubletype"].asDouble()<<endl;
	  Json::Value array = root["arrayint"];
	  for(int i = 0;i < array.size();i++)
	  {
	      std::cout<<"arrayint:   "<<array[i].asInt()<<endl;
	  }
	      Json::Value arraycahr = root["arraycahr"];
	  for(int i = 0;i < arraycahr.size();i++)
	  {
	      std::cout<<"arraycahr:  "<<arraycahr[i].asString()<<endl;
	  }
	      Json::Value obj2 = root["arrayobj2"];
	  for(int i = 0;i < obj2.size();i++)
	  {
	      std::cout<<"obj2-name:   "<<obj2[i]["name"].asString()<<endl;
	      std::cout<<"obj2-age:    "<<obj2[i]["age"].asInt()<<endl;
	      std::cout<<"obj2-weight: "<<obj2[i]["weight"].asDouble()<<endl;
	  }
   	  ROS_INFO("===="); 
     
        //loop_rate.sleep();
}
}
