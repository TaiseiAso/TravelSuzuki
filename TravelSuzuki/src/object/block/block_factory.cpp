#include "block_factory.h"

namespace game::object::block
{
	std::unique_ptr<Block> BlockFactory::create(BLOCK_ID blockID)
	{
		std::unique_ptr<Block> createdBlock;
		switch (blockID)
		{
		case BLOCK_ID::test:
			createdBlock = std::make_unique<blockTest::BlockTest>();
			break;
		default:
			createdBlock = nullptr;
			break;
		}
		return createdBlock;
	}
}