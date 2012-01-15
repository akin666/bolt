
#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

namespace bolt
{

class EventHandler
{
public:
	EventHandler();
	virtual ~EventHandler();

	virtual void handleEvent( unsigned int event );
};

} /* namespace bolt */
#endif /* EVENTHANDLER_HPP_ */
