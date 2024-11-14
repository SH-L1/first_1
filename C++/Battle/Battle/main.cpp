#include "framework.h"

int main()
{
	srand(time(nullptr));


	shared_ptr<World> world = make_shared<World>();

	while (true)
	{
		world->Update();
		
		if (world->End())
			break;
	}

	return 0;
}
