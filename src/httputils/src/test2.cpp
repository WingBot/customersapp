#include <stdio.h> 
#include <ros/ros.h>
#include <curl/curl.h> 
#include <jsoncpp/json/json.h> 
#include <string>
#include <iostream>
#include <fstream>
#define PATH_RECE_FILE "/home/zech/http_ws/src/httputils/test.json"
#define PATH_SEND_FILE "/home/zech/http_ws/src/httputils/example.json"

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
    ifs.open(PATH_RECE_FILE, ios::binary);
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
    root["containerImg"] = Json::Value("33333");
    root["sealImg"] = Json::Value("2222");
    root["timestamps"] = Json::Value("112");
    root["eventId"] = Json::Value("1111");
    Json::FastWriter fw;
    Json::StyledWriter sw;
    std::string number=fw.write(root);
    std::cout<<sw.write(root)<<std::endl;
    int number_size = number.length();
    char JsonData[number_size];
    memset(JsonData, 0, sizeof(JsonData));
    strcpy(JsonData,number.c_str());  
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) 
    {
      
        //data exchanged
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/cloudwalk/robot/customers/dog");
        struct curl_slist *headers = NULL;
        //headers = curl_slist_append(headers, "Accept:application/json");
        headers = curl_slist_append(headers, "Content-Type:application/json");
       // headers = curl_slist_append(headers, "charset:utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, JsonData);
        FILE *pagefile;
	std::stringstream out;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);  
	ROS_INFO("=1=");
	
	string str_json = out.str();//返回值 例如:{"status":"ok"}  
        printf("%s",str_json.c_str()); 
	ROS_INFO("=1-2=");
	res = curl_easy_perform(curl);
	ROS_INFO("=2=");
	if (res != CURLE_OK)
            {
		ROS_INFO("=4=");
                fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
            }
            ROS_INFO("=3=");
        
        /*fopen(PATH_RECE_FILE, "wb+");
        if (pagefile) 
        {
	  //ROS_INFO("===pagefile="); 
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, pagefile);   
	    ROS_INFO("=12=");
            res = curl_easy_perform(curl);
	    ROS_INFO("=23=");
            if (res != CURLE_OK)
            {
		ROS_INFO("=4=");
                fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
            }
            fclose(pagefile);
	    ROS_INFO("=fclose(pagefile)=");
        }
        */
        curl_easy_cleanup(curl);
	ROS_INFO("=curl_easy_cleanup=");
    }
    curl_global_cleanup();
    ROS_INFO("=global_cleanup=");
    //ReadJsonMsg();
    
/*
       while (ros::ok())
       {
	  ros::spinOnce();
	}
	*/
}
