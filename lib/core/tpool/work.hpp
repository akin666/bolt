
#ifndef WORK_H_
#define WORK_H_

namespace bolt
{
	class Work
	{
	public:
		Work();
		virtual ~Work();

		virtual bool begin() = 0;
		virtual void run() = 0;
		virtual void end() = 0;
	};
} /* namespace ice */
#endif /* WORK_H_ */
