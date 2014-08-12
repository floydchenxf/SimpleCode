#include "connection.h"

int main(int argc, char *argv[])
{
	Connection conn("127.0.0.1", 8080);
	conn.Run();
	return 0;
}
