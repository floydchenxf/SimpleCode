#include "connection.h"

int main(int argc, char *argv[])
{
	Connection conn("127.0.0.1", 6020);
	conn.Run();
	return 0;
}
