#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <thread>
#include <iostream>
#include <dirent.h>
#include <sys/syscall.h>
#include <fstream>
#include <linux/input.h>
#include <sys/mman.h>
#include <iconv.h>

#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>


using namespace std;

/**** 구성*****/
long int libAddress = 0;
long int MatrixAddress = 0;
long int GName = 0;
long int UWorld;
float fMatrix[16] = { 0 };


/************************/
/**       VM 읽기-쓰기    **/
int pid;
struct MAPS
{
	long int addr;
	long int taddr;
	int type;
	struct MAPS *next;
};
typedef struct MAPS *PMAPS;
#define LEN sizeof(struct MAPS)
#if defined(__arm__)
int process_vm_readv_syscall = 376;
int process_vm_writev_syscall = 377;
#elif defined(__aarch64__)
int process_vm_readv_syscall = 270;
int process_vm_writev_syscall = 271;
#elif defined(__i386__)
int process_vm_readv_syscall = 347;
int process_vm_writev_syscall = 348;
#else
int process_vm_readv_syscall = 310;
int process_vm_writev_syscall = 311;
#endif
ssize_t process_v(pid_t __pid, const struct iovec *__local_iov, unsigned long __local_iov_count,
				  const struct iovec *__remote_iov, unsigned long __remote_iov_count,
				  unsigned long __flags, bool iswrite)
{
	return syscall((iswrite ? process_vm_writev_syscall : process_vm_readv_syscall), __pid,
				   __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

bool pvm(void *address, void *buffer, size_t size, bool iswrite)
{
	struct iovec local[1];
	struct iovec remote[1];
	local[0].iov_base = buffer;
	local[0].iov_len = size;
	remote[0].iov_base = address;
	remote[0].iov_len = size;
	if (pid < 0)
	{
		return false;
	}
	ssize_t bytes = process_v(pid, local, 1, remote, 1, 0, iswrite);
	return bytes == size;
}

bool vm_readv(long int address, void *buffer, size_t size)
{
	return pvm(reinterpret_cast < void *>(address), buffer, size, false);
}

bool vm_writev(long int address, void *buffer, size_t size)
{
	return pvm(reinterpret_cast < void *>(address), buffer, size, true);
}

// //////////////////////////////////////////////////////////////

/************************/
/**       잡동사니 것들  **/

long int getdword(long int addr)
{
	if (addr < 0xFFFFFF)
	{
		return 0;
	}
	long int var[4] = { 0 };
	memset(var, 0, 4);
	vm_readv(addr, var, 4);
	return var[0];
}

long int getint(long int addr)
{
	if (addr < 0xFFFFFF)
	{
		return 0;
	}
	long int var[4] = { 0 };
	memset(var, 0, 4);
	vm_readv(addr, var, 4);
	return var[0];
}

void writeint(long int addr, long int data)
{
	vm_writev(addr, &data, 4);
}

void writefloat(long int addr, float data)
{
	vm_writev(addr, &data, 4);
}

int getPID(const char *packageName)
{
	int id = -1;
	DIR *dir;
	FILE *fp;
	char filename[32];
	char cmdline[256];
	struct dirent *entry;
	dir = opendir("/proc");
	while ((entry = readdir(dir)) != NULL)
	{
		id = atoi(entry->d_name);
		if (id != 0)
		{
			sprintf(filename, "/proc/%d/cmdline", id);
			fp = fopen(filename, "r");
			if (fp)
			{
				fgets(cmdline, sizeof(cmdline), fp);
				fclose(fp);

				if (strcmp(packageName, cmdline) == 0)
				{
					return id;
				}
			}
		}
	}
	closedir(dir);
	return -1;
}

long int get_module_base(int pid, const char *module_name)
{
	FILE *fp;
	long addr = 0;
	char *pch;
	char filename[32];
	char line[1024];
	snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			if (strstr(line, module_name))
			{
				pch = strtok(line, "-");
				addr = strtoul(pch, NULL, 16);
				if (addr == 0x8000)
					addr = 0;
				break;
			}
		}
		fclose(fp);
	}
	return addr;
}



void getname(int id, char *bbb, long int addr)
{
	int classname;
	int m = 0;
	if (id > 0 && id < 2000000)
	{
		int ye = id / 16384;
		int xu = id % 16384;
		long int ddz = getint(addr + ye * 4);
		long int namedz = getint(ddz + xu * 4);
		int i = 0;
		for (i; i < 8; i++)
		{
			classname = getint(namedz + 8 + i * 4);
			memcpy(&bbb[m], &classname, 4);
			m += 4;
		}
	}
}

// ////////////////////////////////////////////////////

#define MAX_MSG 100

#define LINE_ARRAY_SIZE (MAX_MSG+1)

char buf[256] = "recived";

int main()
{
	struct sCli
	{
		int scrX, scrY;
	};

	struct gameInf
	{
		int playerCount = 0;
	};
	gameInf gminf;
	int listenSocket, connectSocket, i;
	unsigned short int listenPort;
	socklen_t clientAddressLength;
	struct sockaddr_in clientAddress, serverAddress;
	char line[LINE_ARRAY_SIZE];

	listenPort = 6969;
	listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (listenSocket < 0)
	{
		cerr << "cannot create listen socket";
		exit(1);
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(listenPort);

	sCli scli
	{
	};


	int ret =::bind(listenSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

	if (ret < 0)
	{
		cerr << "cannot bind socket";
		exit(1);
	}

	listen(listenSocket, 5);



	pid = getPID("com.pubg.imobile");
	if (pid < 0)
	{
		printf("\n >> 게임이 시작되지 않았습니다 <<");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf(" >> 게임 PID 발견 :- %d << \n", pid);
		libAddress = get_module_base(pid, "libUE4.so");
		printf(" >> 게임 LibUE4 주소 :- %p << \n", libAddress);
	}
	GName = getint(libAddress + 0x742D894);
	UWorld = libAddress + 0x7172AFC;
	MatrixAddress = getint(getint(libAddress + 0x76085A0) + 0x68) + 0x6d0;

	printf("GName = %p\nUWorld = %p\nMatrix Address = %p\n", GName, UWorld, MatrixAddress);
	bool connect = false;
	long int UWorldPointer = getint(getint(UWorld) + 0x20);
	while (1)
	{

		cout << "Waiting for TCP connection on port " << listenPort << " ...\n";

		clientAddressLength = sizeof(clientAddress);

		connectSocket =
			accept(listenSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);

		if (connectSocket < 0)
		{

			cerr << "cannot accept connection ";

			exit(1);

		}
		cout << "  connected to " << inet_ntoa(clientAddress.sin_addr);
		cout << ":" << ntohs(clientAddress.sin_port) << "\n";
		memset(line, 0x0, LINE_ARRAY_SIZE);

		while (recv(connectSocket, &scli, sizeof(scli), 0) > 0)
		{

			while (1)
			{
				int PlayerCount = 0;
				int entityQuantity = getint(UWorldPointer + 0x74);
				long int AActorAddress = getint(UWorldPointer + 0x70);
				vm_readv(MatrixAddress, fMatrix, 4 * 16);
				for (int i = 0; i < entityQuantity; i++)
				{
					long int AActor = getint(AActorAddress + 4 * i);
					char name[256] = "";
					int tid = getint(AActor + 0x10);
					getname(tid, name, GName);
					long int team = getint(getint(getint(getint(getint(UWorld)+36)+100)+32)+0x324);
					int me = getint(AActor + 0xf8);

					if (me == 258){
						team = AActor;
						continue;
					}

					if (strstr(name, "Player"))
					{
						int teamM = getint(AActor + 0x660);
						int TeamID;
						if (AActor==team)
							TeamID = teamM;
						if (teamM = TeamID)
						{
							continue;
						}
						PlayerCount++;
					}
				}
				gminf.playerCount = PlayerCount;
				send(connectSocket, &gminf, sizeof(gminf), 0);
				printf("PlayerCount %d\n", gminf.playerCount);
			}

		}
		printf("got done");
	}
}
