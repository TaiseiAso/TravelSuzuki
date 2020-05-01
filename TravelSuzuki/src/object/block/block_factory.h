#ifndef block_factory_h
#define block_factory_h

#include <memory>
#include "blockTest/block_test.h"

namespace game::object::block
{
	enum class BLOCK_ID {
		test
	};

	class BlockFactory
	{
	public:
		std::unique_ptr<Block> create(BLOCK_ID blockID);
	};
}

#endif // !block_factory_h