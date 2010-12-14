#pragma once

namespace Engine
{
	class WorkData
	{
	public:
		WorkData();
		virtual ~WorkData();

		virtual void handle() = 0;
		virtual bool isHandled() = 0;
	};
}
