#include <stdio.h> 
#include <ros/ros.h>
#include <curl/curl.h> 
#include <jsoncpp/json/json.h> 
#include <string>
#include <iostream>
#include <fstream>
#include "base64.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    using namespace std;
    string data((const char*) ptr, (size_t) size * nmemb);

    *((stringstream*) stream) << data << endl;

    return size * nmemb;
}

int main(int argc, char *argv[])
{
    using namespace std;
        // 基于当前系统的当前日期/时间
        time_t now = time(0);
        char* dt = ctime(&now);
	Json::Value root;
	root["containerImg"] = Json::Value("33333");
	root["sealImg"] = Json::Value("2222");
	root["timestamps"] = Json::Value(dt);
	root["eventId"] = Json::Value("1111");
	Json::FastWriter fw;
	Json::StyledWriter sw;
	std::string number=fw.write(root);
	std::cout<<sw.write(root)<<std::endl;
	int number_size = number.length();
	char JsonData[number_size];
	memset(JsonData, 0, sizeof(JsonData));
	strcpy(JsonData,number.c_str()); 
        cout << dt << "-------------------------------------" << endl;
	const std::string s = 
	"René Nyffenegger\n"
	"http://www.renenyffenegger.ch\n"
	"passion for data\n";

	std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
	std::string decoded = base64_decode(encoded);

	std::cout << "encoded: " << std::endl << encoded << std::endl << std::endl;
	std::cout << "decoded: " << std::endl << decoded << std::endl;
        /*HTTP GET json data*/
        std::stringstream out;
        void* curl = curl_easy_init();
	struct curl_slist *headers = NULL;
        // 设置URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/cloudwalk/robot/customers/dog");
	headers = curl_slist_append(headers, "Content-Type:application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, JsonData);
        // 设置接收数据的处理函数和存放变量
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

        // 执行HTTP GET操作
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // 接受数据存放在out中，输出之
        //cout << out.str() << endl;
        string str_json = out.str();
        printf("%s",str_json.c_str());
        curl_easy_cleanup(curl);

    return 0;
}