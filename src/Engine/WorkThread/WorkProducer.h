#pragma once

namespace Engine
{
	class WorkData;
	class WorkDoneData;
	class WorkProducer
	{
	public:
		WorkProducer();
		virtual ~WorkProducer();

		virtual void handle(WorkData *data) = 0;
		virtual void finished(WorkDoneData *data) = 0;
	};
}
