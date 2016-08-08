#include <config_file_reader.h>

int main()
{
	//E:\calm\src\build\calm\Debug\calm.exe
	ConfigFileReader config_file("E:\\calm\\src\\build\\calm\\Debug\\msgserver.conf");

	char* listen_ip = config_file.GetConfigName("ListenIP");
	char* str_listen_port = config_file.GetConfigName("ListenPort");
	char* ip_addr1 = config_file.GetConfigName("IpAddr1");	
	char* ip_addr2 = config_file.GetConfigName("IpAddr2");	
	char* str_max_conn_cnt = config_file.GetConfigName("MaxConnCnt");
	char* str_aes_key = config_file.GetConfigName("aesKey");
}